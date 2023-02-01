#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Data
{
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

Data* data = new Data();

void Data::readDataLines(ifstream& dataFile)
{
    string jumpPropertyName;

    try{
        for (int line = 1; line < 11; line++)
            {
                //Skips the properties names
                getline(dataFile, jumpPropertyName, ' ');
                switch (line)
                {
                case 1:
                    getline(dataFile, Name);
                    Name = Name;
                    break;
                case 2:
                    getline(dataFile, Location);
                    Location = Location;
                    break;
                case 3:
                    getline(dataFile, Comment);
                    Comment = Comment;
                    break;    
                case 4:
                    getline(dataFile, Type);
                    Type = Type;
                    break;   
                case 5:
                    getline(dataFile, SizeString);
                    Size = stoi(SizeString);
                    break;
                case 6:
                    getline(dataFile, Distribution);
                    Distribution = Distribution;
                    break;
                case 7:
                    getline(dataFile, Depot);
                    Depot = Depot;
                    break;
                case 8:
                    getline(dataFile, RouteTimeString);
                    RouteTime = stoi(RouteTimeString);
                    break;
                case 9:
                    getline(dataFile, TimeWindowString);
                    TimeWindow = stoi(TimeWindowString);
                    break;
                case 10:
                    getline(dataFile, CapacityString);
                    Capacity = stoi(CapacityString);
                    break;
                }
            }
    }
    catch (exception &e){
        cout << "Error: " << e.what();
    }
    
    getline(dataFile, jumpPropertyName);
}

void Data::printData(){
    
    cout << Name << endl
         << Location << endl
         << Comment << endl
         << Type << endl
         << Size << endl
         << Distribution << endl
         << Depot << endl
         << RouteTime << endl
         << TimeWindow << endl
         << Capacity << endl;
}

int Data::getSize(Data *data){
    return data->Size;
}

class Node
{
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

void Node::readNodes(ifstream &dataFile)
{
    string jumpPropertyName;
    for (int i = 0; i < 9; i++)
    {
        switch (i)
        {
        case 0:
            dataFile >> Id;
            break;
        case 1:
            dataFile >> Latitude;
            break;
        case 2:
            dataFile >> Longitude;
            break;
        case 3:
            dataFile >> Demand;
            break;
        case 4:
            dataFile >> EarlyTimeWindow;
            break;
        case 5:
            dataFile >> LastTimeWindow;
            break;
        case 6:
            dataFile >> Duration;
            break;
        case 7:
            dataFile >> CollectPair;
            break;
        case 8:
            dataFile >> DeliveryPair;
            break;
        }
    }
    getline(dataFile, jumpPropertyName);
}

void Node::printNodes(){
    
    cout << Id << " "
         << Latitude << " "
         << Longitude << " "
         << Demand << " "
         << EarlyTimeWindow << " "
         << LastTimeWindow << " "
         << Duration << " "
         << CollectPair << " "
         << DeliveryPair << " "
         << endl;
}

/*
class Edge
{
private:
     vector<int> Value;
public:
    Edge();
    void readEdges(ifstream dataFile);
};

Edge::Edge()
{
    vector<int> Value;
}

void Edge::readEdges(ifstream dataFile){
}
*/


