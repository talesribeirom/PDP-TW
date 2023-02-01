#include "functions.hpp"
#include <vector>

int main()
{
    Data* data = new Data();

    string fileName;
    cout << "Enter the file name without (.txt): ";
    cin >> fileName;

    ifstream dataFile(fileName + ".txt");

    if (dataFile)
    {
        data->readDataLines(dataFile);
        int numberVertex = data->getSize(data);
        
        cout << "===== Properties found in the file =====" << endl;
        data->printData();

        Node* node = new Node[numberVertex];
        for (int i = 0; i < numberVertex; i++)
        {
            node[i].readNodes(dataFile);
        }

        cout << "===== Nodes found in the file =====" << endl;
        for (int i = 0; i < numberVertex; i++)
        {
            node[i].printNodes();
        }
        
        // Edge* edge = new Edge();
        // edge->readEdges(dataFile);
    }
    else
    {
        cout << "Error: Invalid File Name or File Format!";
    }
    


}