#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "classes.hpp" 

Data* data = new Data();
Util* util = new Util();
 

int Data::readDataLines(ifstream& dataFile)
{
    try{
        string jumpPropertyName;

        for (int line = 0; line < 10; line++)
            {
                //Skips the properties names
                getline(dataFile, jumpPropertyName, ' ');
                
                switch (line)
                {
                case 0:
                    getline(dataFile, Name);
                    break;
                case 1:
                    getline(dataFile, Location);
                    break;
                case 2:
                    getline(dataFile, Comment);
                    break;    
                case 3:
                    getline(dataFile, Type);
                    break;   
                case 4:
                    getline(dataFile, SizeString);
                    Size = stoi(SizeString);
                    break;
                case 5:
                    getline(dataFile, Distribution);
                    break;
                case 6:
                    getline(dataFile, Depot);
                    break;
                case 7:
                    getline(dataFile, RouteTimeString);
                    RouteTime = stoi(RouteTimeString);
                    break;
                case 8:
                    getline(dataFile, TimeWindowString);
                    TimeWindow = stoi(TimeWindowString);
                    break;
                case 9:
                    getline(dataFile, CapacityString);
                    Capacity = stoi(CapacityString);
                    break;
                }
            }
    }
    catch (exception &e){
        cout << "Error on read Property Lines (First 10): " << e.what();
    }
    return Size;
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

Node::Node(Data *data) : Data(*data)
{
    Id = new int[Size];
    Latitude = new double[Size];
    Longitude = new double[Size];
    Demand = new int[Size];
    EarlyTimeWindow = new int[Size];
    LastTimeWindow = new int[Size];
    Duration = new int[Size];
    CollectPair = new int[Size];
    DeliveryPair = new int[Size];
    Visited = new bool[Size];
    Distance = new int*[Size];
    for (int i = 0; i < Size; i++)
    {
        Distance[i] = new int[Size];
    }

    for (int i = 0; i < Size; i++)
    {
        Id[i] = -1;
        Latitude[i] = -1;
        Longitude[i] = -1;
        Demand[i] = 0;
        EarlyTimeWindow[i] = -1;
        LastTimeWindow[i] = -1;
        Duration[i] = -1;
        CollectPair[i] = -1;
        DeliveryPair[i] = -1;
        Visited[i] = false;
        for (int j = 0; j < Size; j++)
        {
            Distance[i][j] = -1;
        }
    }
}

Node::~Node(){
    delete[] Id;
    delete[] Latitude;
    delete[] Longitude;
    delete[] Demand;
    delete[] EarlyTimeWindow;
    delete[] LastTimeWindow;
    delete[] Duration;
    delete[] CollectPair;
    delete[] DeliveryPair;
    for (int i = 0; i < Size; i++)
    {
        delete Distance[i];
    }
    delete[] Distance;
    delete[] Visited;
}

void Node::readNodes(ifstream &dataFile)
{
    try{
        string jumpNodeName;
        dataFile >> jumpNodeName;
        for (int i = 0; i < Size; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                switch(j){
                    case 0:
                        dataFile >> Id[i];
                        break;
                    case 1:
                        dataFile >> Latitude[i];
                        break;
                    case 2:
                        dataFile >> Longitude[i];
                        break;
                    case 3:
                        dataFile >> Demand[i];
                        break;
                    case 4:
                        dataFile >> EarlyTimeWindow[i];
                        break;
                    case 5:
                        dataFile >> LastTimeWindow[i];
                        break;
                    case 6:
                        dataFile >> Duration[i];
                        break;
                    case 7:
                        dataFile >> CollectPair[i];
                        break;
                    case 8:
                        dataFile >> DeliveryPair[i];
                        break;
                }
            }     
        }    
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


void Node::validateData(){
    
    int collectAux = 0;
    int deliveryAux = 0;  
    for (int i = 0; i < Size; i++)
    {
        if (Demand[i] == 0)
        {
            if (CollectPair[i] != 0 || DeliveryPair[i] != 0)
            {
                cout << CollectPair[i] << "  " << DeliveryPair[i] << endl;
                cout << "Precedence error for CollectPair or DeliveryPair";
                exit(0);
            }
            
        }

        if (Demand[i] > 0)
        {
            deliveryAux = Id[i] + ((Size - 1)/2);
            collectAux = 0;
            if(CollectPair[i] == 0 && DeliveryPair[i] != 0)
            {
                if (DeliveryPair[i] != deliveryAux)
                {
                    cout << "Precedence error for vertex " << Id[i] << endl;
                    exit(0);
                }
            }
        }

        if (Demand[i] < 0)
        {
            deliveryAux = 0;
            collectAux = Id[i] - ((Size - 1)/2);
            if (CollectPair[i] != 0 && DeliveryPair[i] == 0)
            {
                if (CollectPair[i] != collectAux)
                {
                    cout << "Precedence error for vertex " << Id[i] << endl;
                    exit(0);
                }
            }  
        }

        if (Demand[i] > Capacity)
        {
            cout << "Error for Demand/Capacity, valeu is greater than expected: " << Demand[i] << "-->" << Capacity;
            exit(0); 
        }

        if (LastTimeWindow[i] > RouteTime)
        {
            cout << "Error for LastTimeWindow/RouteTime, value is greater than expected: " << LastTimeWindow[i] << "-->" << RouteTime;
        }
    }
}

void Node::nodeDistance(ifstream &dataFile)
{
    string line;
    dataFile >> line;
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            dataFile >> Distance[i][j];
        }
    }
}

void Validator::setVisited(vector<pair<int,int>> &request, pair<int,int> package)
{
    Visited[package.first] = true;
    Visited[package.second] = true;

    for (unsigned int i = 0; i < request.size(); i++)
    {
        if(package.first == request.at(i).first)
        {
            request.erase(request.begin() + i);
            break;
        }
    }
    
}

pair<int,int> Validator::returnPackage(vector<int> newRoute)
{
    int collect = -1;
    int delivery = -1;

    for(auto it = newRoute.begin(); it != newRoute.end(); it++)
    {
        if(!Visited[*it])
        {
            if (collect != -1 && delivery == -1)
            {
                delivery = *it;
            }
            if (collect == -1)
            {
                collect = *it;
            }
        }
    }
    pair<int,int> deliveryPair = make_pair(collect, delivery);
    return deliveryPair;
}

bool Validator::validateRoute(const vector<int>& newRoute)
{
    int totalTime = 0;
    int totalDemand = 0;
    int prevVertex = 0;

    for (int i = 1; i < newRoute.size(); i++)
    {
        int vertex = newRoute[i];
        int nextVertex = (i + 1 < newRoute.size()) ? newRoute[i + 1] : 0;

        // Check demand
        totalDemand += Demand[vertex];
        if (totalDemand > Capacity)
        {
            return false; 
        }
        if (Demand[vertex] < 0 && find(newRoute.begin(), newRoute.begin() + i, vertex - ((Size - 1) / 2)) == newRoute.begin() + i)
        {
            return false;
        }

        // Update total time
        totalTime += Distance[prevVertex][vertex];
        if (totalTime < EarlyTimeWindow[nextVertex])
        {
            totalTime = EarlyTimeWindow[nextVertex] + Duration[nextVertex];
        }
        else
        {
            totalTime += Duration[nextVertex];
        }

        // Check time windows
        if (totalTime > LastTimeWindow[nextVertex])
        {
            return false;
        }

        prevVertex = vertex;
    }

    // Check route time
    return (totalTime <= RouteTime);
}

bool Validator::someRoute(const std::vector<int>& route, int& priority) const
{
    int currentVertex = 0;
    int nextVertex = 0;
    int totalTime = 0;
    int totalDemand = 0;
    bool depot = false;

    for (const auto& vertex : route)
    {
        nextVertex = vertex;
        totalTime += calculateDistance(currentVertex, nextVertex);
        totalDemand += Demand[nextVertex];

        if (totalDemand > Capacity)
        {
            return false;
        }

        totalTime = updateTotalTime(nextVertex, totalTime, priority);

        if (totalTime > LastTimeWindow[nextVertex])
        {
            return false;
        }

        currentVertex = nextVertex;
        if (nextVertex == 0)
        {
            depot = true;
        }
    }

    if (!depot)
    {
        return false;
    }

    if (totalTime > RouteTime)
    {
        return false;
    }

    return true;
}

int Validator::calculateDistance(int fromVertex, int toVertex) const
{
    return Distance[fromVertex][toVertex];
}

int Validator::updateTotalTime(int vertex, int totalTime, int& priority) const
{
    int newTotalTime = totalTime;
    if (newTotalTime < EarlyTimeWindow[vertex])
    {
        newTotalTime = EarlyTimeWindow[vertex] + Duration[vertex];
        priority++;
    }
    else
    {
        newTotalTime += Duration[vertex];
        priority += 2;
    }
    return newTotalTime;
}

int Validator::calculateRoute(vector<int> newRoute)
{
    int vertex = 0;
    int nextVertex = 0;
    int routeTime = 0;
    bool depot = false;

    for(auto it = newRoute.begin(); !depot && it != newRoute.end() ; it++)
    {
        vertex = *it;
        nextVertex = *(it + 1);
        routeTime += Distance[vertex][nextVertex];

        if (routeTime < EarlyTimeWindow[nextVertex])
        {
            routeTime = EarlyTimeWindow[nextVertex] + Duration[nextVertex];
        }else{
            routeTime += Duration[nextVertex];
        }
        
        if(nextVertex == 0)
            depot = true;
    }
    return routeTime;
}

vector<int> Validator::opt(const vector<int>& newRoute)
{
    const int originalTime = calculateRoute(newRoute);
    int solutionTime = 0;
    int numRestrictionViolations = 0;
    const vector<int> originalRoute = newRoute;
    vector<int> solutionRoute;

    const auto routeSize = newRoute.size();

    for (auto it = newRoute.begin() + 1; it != newRoute.end() - 2; ++it)
    {
        for (auto jt = it + 1; jt != newRoute.end() - 1; ++jt)
        {
            auto modifiedRoute = originalRoute;

            iter_swap(modifiedRoute.begin() + distance(originalRoute.begin(), it),
                      modifiedRoute.begin() + distance(originalRoute.begin(), jt));

            if (!validateRoute(modifiedRoute))
            {
                ++numRestrictionViolations;
                continue;
            }

            const auto newRouteTime = calculateRoute(modifiedRoute);
        }
    }
}

Vehicles::Vehicles(Validator *validators, int vehicleNumbers) : Validator (*validators)
{
    route = new vector<int>[vehicleNumbers];
}

Vehicles::~Vehicles()
{
    delete[] route;
}

void Vehicles::updateRoute(vector<int> newRoute, int vehicleId)
{
    route[vehicleId] = newRoute;
}

vector<int> Vehicles::getRoute(int vehicleId)
{
    return route[vehicleId];
}


bool Vehicles::emptyRoute(int vehicleId)
{
    bool result = route[vehicleId].empty() ? true : false;
    return result;
}

void Vehicles::showRoute(int vehicleId)
{
    for(auto it = route[vehicleId].begin(); it != route[vehicleId].end(); it++)
    {
        if (it + 1 == route[vehicleId].end())
        {
            cout << *it;
        }else
        {
            cout << *it << " -> ";
        }
        cout << endl;
    }
}

int Vehicles::calculateTime(int vehicleId)
{
    bool depot = false;
    int nextVertex = 0;
    int routeTime = 0;
    int currentVertex = 0;

    for (auto it = route[vehicleId].begin(); !depot && it != route[vehicleId].end(); it++)
    {
        currentVertex = *it;
        nextVertex = *(it + 1);
        routeTime += Distance[currentVertex][nextVertex];

        if (routeTime < EarlyTimeWindow[nextVertex])
        {
            routeTime = EarlyTimeWindow[nextVertex] + Duration[nextVertex];
        }
        else
        {
            routeTime += Duration[nextVertex];
        }

        if(nextVertex == 0)
        {
            depot = true;
        }
    }
    return routeTime;
}

void Vehicles::setRequest(vector<pair<int,int>> &request, int vehicleId)
{
    route[vehicleId].push_back(request.begin()->first);
    route[vehicleId].push_back(request.begin()->second);
    route[vehicleId].insert(route[vehicleId].begin(), 0);
    route[vehicleId].push_back(0);

    Visited[request.begin()->first] = true;
    Visited[request.begin()->second] = true;
    Visited[0] = true;

    request.erase(request.begin());
}

vector<int> Vehicles::insertRoute(const vector<int>& otherRoute, int vehicleId)
{
    int cheapestCost = 0;
    int bestPriority = 0;
    int requestNumbers = (Size - 1) / 2;
    vector<int> routeWithCollect;
    vector<int> newestRoute;
    int before = -1;
    int inserted = -1;
    int after = -1;
    int priority = 0;
    for (const auto& elem : otherRoute) {
        for (int j = 1; j <= requestNumbers; j++) {
            int cost = 0;
            int priority = 0;

            if (!Visited[j]) {
                vector<int> tempRoute = otherRoute;
                tempRoute.insert(tempRoute.begin() + elem, j);
                if (!someRoute(tempRoute, priority)) {
                    continue;
                }
                before = tempRoute[elem - 1];
                inserted = tempRoute[elem];
                after = tempRoute[elem + 1];
                cost = Distance[before][inserted] + Distance[inserted][after] - Distance[before][after];

                routeWithCollect = tempRoute;

                int k = j + requestNumbers;

                for (auto& tempElem : tempRoute) {
                    priority = 0;

                    tempRoute.insert(tempRoute.begin() + elem, k);

                    if (!someRoute(tempRoute, priority)) {
                        tempRoute = routeWithCollect;
                        continue;
                    }

                    before = tempRoute[elem - 1];
                    inserted = tempRoute[elem];
                    after = tempRoute[elem + 1];
                    cost = Distance[before][inserted] + Distance[inserted][after] - Distance[before][after];

                    if (newestRoute.empty() || priority >= bestPriority && cost < cheapestCost) {
                        newestRoute = tempRoute;
                        cheapestCost = cost;
                        bestPriority = priority;
                    }

                    tempRoute = routeWithCollect;
                }
            }
        }
    }
    return newestRoute;
}

void Vehicles::resizeRoute(int &routeNumbers)
{
    int newSize = routeNumbers + 1;
    vector<int> *newestRoutes = new vector<int>[newSize];

    for (int i = 0; i < routeNumbers; i++)
    {
        newestRoutes[i] = route[i];
    }
    delete[] route;

    route = new vector<int>[routeNumbers];
    for (int i = 0; i < routeNumbers; i++)
    {
        route[i] = newestRoutes[i];
    }
    delete[] newestRoutes;
}

void Vehicles::generateFile(int vehicleNumbers)
{
    cout << "Chegou solucao";
    // todo
    ofstream solutionFile("Solution.txt");
}


int Util::getCurrentLine(std::istream& is)
{
    int lineCount = 1;
    is.clear();  
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
