#include "functions.hpp"

using namespace std;
int main()
{
    string fileName;
    cout << "Enter the file name without the extension (.txt): ";
    cin >> fileName;

    ifstream dataFile("instances/" + fileName + ".txt");

    if (dataFile)
    {
        Data *data = new Data;
        int vertexNumbers = data->readDataLines(dataFile);    
        Node *node = new Node(data);
        int vehicleNumbers;
        cout << "Numbers of vehicles available? ";
        cin >> vehicleNumbers;

        node->readNodes(dataFile);
        node->validateData();
        node->nodeDistance(dataFile); 
        
        //segmentation fault
        auto validators = make_unique<Validator>(node);

        auto vehicles = make_unique<Vehicles>(validators.get(), vehicleNumbers);

        vector<pair<int, int>> requests;

        const int requestNumbers = (vertexNumbers - 1) / 2;

        cout << "RequestNumbers: " << requestNumbers << endl << "VertexNumbers: " << vertexNumbers << endl;

        for (int i = 0; i < requestNumbers; ++i)
        {
            requests.emplace_back(i + 1, (i + 1) + requestNumbers);
        }

        int vehicleId = 0;

        while (true)
        {
            vector<int> newRoute;

            for (const auto& request : requests)
            {
                if (vehicles->emptyRoute(vehicleId))
                {
                    vehicles->setRequest(requests, vehicleId);
                    newRoute = vehicles->getRoute(vehicleId);
                }

                vector<int> tempRoute = newRoute;

                newRoute = vehicles->insertRoute(newRoute, vehicleId);

                if (!newRoute.empty())
                {
                    newRoute = validators->opt(newRoute);
                    const auto package = validators->returnPackage(newRoute);
                    vehicles->updateRoute(newRoute, vehicleId);
                    validators->setVisited(requests, package);
                }
                else
                {
                    vehicles->resizeRoute(vehicleNumbers);
                    vehicles->updateRoute(tempRoute, vehicleId);
                    ++vehicleId;
                }

                if (requests.empty())
                {
                    break;
                }
            }
        }
        vehicles->generateFile(vehicleNumbers);
        dataFile.close();
    }
    else
    {
        cout << "Error: Invalid File Name or File Format!";
    }
    

   

}