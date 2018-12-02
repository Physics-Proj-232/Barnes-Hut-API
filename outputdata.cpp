#include "barneshut.h"
#include <iostream>
#include <fstream>
using namespace std;

//This function writes the data stored in the array "children" to a test file
BarnesHutNode::void OutputData()
{
    ofstream outputdata;
    outputdata.open("outputdata.txt");
    if(outputdata)
    {    for(int i=0; i < 8; i++)
            {outputdata << this->children[i];
             outputdata << " ";}
    outputdata.close();}
    else
    {
        cout << "Error opening file."
        outputdata.clear();
    }

}
