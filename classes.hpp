#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Util
{
    public:
        int getCurrentLine(istream& is);

};

class Data
{
    friend class Util;
    private:
        string Name;
        string Location;
        string Comment;
        string Type;
        int Size;
        string Distribution;
        string Depot;
        int RouteTime;
        int TimeWindow;
        int Capacity;

        // Aux for getline() function - convert to int
        string SizeString;
        string RouteTimeString;
        string TimeWindowString;
        string CapacityString;
        
    public:
        Data();
        void readDataLines(ifstream& dataFile);
        void printData();
        int getSize(Data *data);
};

Data::Data(){
    Name = ' ';
    Location = ' ';
    Comment = ' ';
    Type = ' ';
    Size = -1;
    Distribution = ' ';
    Depot = ' ';
    RouteTime = -1;
    TimeWindow = -1;
    Capacity = -1;
    SizeString = ' ';
    RouteTimeString = ' ';
    TimeWindowString = ' ';
    CapacityString = ' ';
}

class Node
{
    friend class Util;
    private:
        int Id;
        float Latitude;
        float Longitude;
        int Demand;
        int EarlyTimeWindow;
        int LastTimeWindow;
        int Duration;
        int CollectPair;
        int DeliveryPair;

    public:
        Node();
        void readNodes(ifstream &dataFile);
        void printNodes();
};

Node::Node()
{
    Id = -1;
    Latitude = -1;
    Longitude = -1;
    Demand = -1;
    EarlyTimeWindow = -1;
    LastTimeWindow = -1;
    Duration = -1;
    CollectPair = -1;
    DeliveryPair = -1;
}



