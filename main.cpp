#include "class.h"
#include <vector>

int main()
{
    Data* data = new Data();

    string fileName;
    cout << "Enter the file name without (.txt): ";
    cin >> fileName;

    ifstream dataFile("instances/" + fileName + ".txt");

    if (dataFile)
    {
        data->readDataLines(dataFile);
        int numberVertex = data->getSize(data);
        data->printData();

        Node* node = new Node[numberVertex];
        for (int i = 0; i < numberVertex; i++)
        {
            node[i].readNodes(dataFile);
        }

        for (int i = 0; i < numberVertex; i++)
        {
            node[i].printNodes();
        }
        
        // Edge* edge = new Edge();
        // edge->readEdges(dataFile);
    }
    else
    {
        cout << "Error: Invalid File Name!";
    }
    


}