#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "classes.hpp" 

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

void Node::readNodes(ifstream &dataFile)
{
    string jumpPropertyName;
    for (int i = 1; i < 10; i++)
    {
        switch (i)
        {
        case 1:
            dataFile >> Id;
            break;
        case 2:
            dataFile >> Latitude;
            break;
        case 3:
            dataFile >> Longitude;
            break;
        case 4:
            dataFile >> Demand;
            break;
        case 5:
            dataFile >> EarlyTimeWindow;
            break;
        case 6:
            dataFile >> LastTimeWindow;
            break;
        case 7:
            dataFile >> Duration;
            break;
        case 8:
            dataFile >> CollectPair;
            break;
        case 9:
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
