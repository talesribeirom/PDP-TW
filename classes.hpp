#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#define INVALID -1

class Util
{
    public:
        int getCurrentLine(istream& is);
};

class Data
{
    friend class Util;
    friend class Node;
    friend class Validator;
    public:
        string Name;
        string Location;
        string Comment;
        string Type;
        string Distribution;
        string Depot;
        int RouteTime;
        int TimeWindow;
        int Capacity;
        int Size;
        string SizeString;
        string RouteTimeString;
        string TimeWindowString;
        string CapacityString;

        Data();
        int readDataLines(ifstream& dataFile);
        void printData();
        int getSize(Data *data);
};

Data::Data()
{
    Size = -1;
    RouteTime = -1;
    TimeWindow = -1;
    Capacity = -1;
}

class Node : public Data
{
    friend class Util;
    public:
        int *Id;
        double *Latitude;
        double *Longitude;
        int *Demand;
        int *EarlyTimeWindow;
        int *LastTimeWindow;
        int *Duration;
        int *CollectPair;
        int *DeliveryPair;
        bool *Visited;
    
        int **Distance;
        Node(Data *data);
        ~Node();
        void readNodes(ifstream &dataFile);
        void validateData();
        void nodeDistance(ifstream &dataFile);
        void printNodes();
};

class Validator : public Node
{
    public:
        bool validateRoute(const vector<int>& newRoute);
        int calculateRoute(vector<int> newRoute);
        bool someRoute(const std::vector<int>& route, int& priority) const;
        int calculateDistance(int fromVertex, int toVertex) const;
        int updateTotalTime(int vertex, int totalTime, int& priority) const;
        Validator(Node *node) : Node(*node) {};
        void setVisited(vector<pair<int,int>> &request, pair<int,int> package);
        pair<int,int> returnPackage(vector<int> newRoute);
        vector<int> opt(const vector<int>& newRoute);
};

class Vehicles : public Validator
{   
    private:
        vector<int> *route;

    public:
        Vehicles(Validator *validator, int vehicleNumbers);
        ~Vehicles();
        bool emptyRoute(int vehicleId);
        void showRoute(int vehicleId);
        int calculateTime(int vehicleId);
        void updateRoute(vector<int> newRoute, int vehicleId);
        vector<int> getRoute(int vehicleId);
        void setRequest(vector<pair<int,int>> &request, int vehicleId);
        vector<int> insertRoute(const vector<int>& otherRoute, int vehicleId);
        void resizeRoute(int &routeNumbers);
        void generateFile(int vehicleNumbers);
};


