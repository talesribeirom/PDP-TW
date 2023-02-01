#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "classes.hpp" 

Data* data = new Data();
Util* util = new Util();

void Data::readDataLines(ifstream& dataFile)
{
    try{
        string jumpPropertyName;

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
        getline(dataFile, jumpPropertyName);
    }
    catch (exception &e){
        cout << "Error on read Property Lines (First 10): " << e.what();
    }
    
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
    try{
        string jumpNodeName;
        int currentLine;

        for (int lines = 1; lines < 10; lines++)
        {
            switch (lines)
            {
            case 1:
                dataFile >> Id;
                if(Id < 0){
                    currentLine = util->getCurrentLine(dataFile);
                    cout << endl << "##### Node Error: Invalid Id at line" << " " << currentLine << " #####"<< endl;
                    exit(0);
                }
                break;
            case 2:
                dataFile >> Latitude;
                if(Latitude < -90.0 || Latitude > 90.0){
                    currentLine = util->getCurrentLine(dataFile);
                    cout << endl << "##### Node Error: Invalid Latitude at line" << " " << currentLine << " #####"<< endl;
                    exit(0);
                }
                break;
            case 3:
                dataFile >> Longitude;
                if( Longitude < -180.0 || Longitude > 180.0){
                    currentLine = util->getCurrentLine(dataFile);
                    cout << endl << "##### Node Error: Invalid Latitude at line" << " " << currentLine << " #####"<< endl;
                    exit(0);
                }
                break;
            case 4:
                dataFile >> Demand;
                if(Demand == -1){
                    currentLine = util->getCurrentLine(dataFile);
                    cout << endl << "##### Node Error: Invalid Demand at line" << " " << currentLine << " #####"<< endl;
                    exit(0);
                }
                break;
            case 5:
                dataFile >> EarlyTimeWindow;
                if(EarlyTimeWindow < 0){
                    currentLine = util->getCurrentLine(dataFile);
                    cout << endl << "##### Node Error: Invalid EarlyTimeWindow at line" << " " << currentLine << " #####"<< endl;
                    exit(0);
                }
                break;
            case 6:
                dataFile >> LastTimeWindow;
                if(LastTimeWindow < 0){
                    currentLine = util->getCurrentLine(dataFile);
                    cout << endl << "##### Node Error: Invalid LastTimeWindow at line" << " " << currentLine << " #####"<< endl;
                    exit(0);
                }
                break;
            case 7:
                dataFile >> Duration;
                if(Duration < 0){
                    currentLine = util->getCurrentLine(dataFile);
                    cout << endl << "##### Node Error: Invalid Duration at line" << " " << currentLine << " #####"<< endl;
                    exit(0);
                }
                break;
            case 8:
                dataFile >> CollectPair;
                if(CollectPair < 0){
                    currentLine = util->getCurrentLine(dataFile);
                    cout << endl << "##### Node Error: Invalid CollectPair at line" << " " << currentLine << " #####"<< endl;
                    exit(0);
                }
                break;
            case 9:
                dataFile >> DeliveryPair;
                if(DeliveryPair < 0){
                    currentLine = util->getCurrentLine(dataFile);
                    cout << endl << "##### Node Error: Invalid DeliveryPair at line" << " " << currentLine << " #####"<< endl;
                    exit(0);
                }
                break;
            }
        }
        getline(dataFile, jumpNodeName);
    }
    catch(exception &e){
        cout << "Error on reading Nodes Lines: " << e.what();
    }
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

int Util::getCurrentLine(std::istream& is)
{
    int lineCount = 1;
    is.clear();     // need to clear error bits otherwise tellg returns -1.
    auto originalPos = is.tellg();
    if (originalPos < 0) 
        return -1;
    is.seekg(0);
    char c;
    while ((is.tellg() < originalPos) && is.get(c))
    {
        if (c == '\n') ++lineCount;
    }
    return lineCount;
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
