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
    {   for()
            for(int j = this->bodystart; j <= this->bodyend; j++)
            {
                outputdata << this->bodies[j]->x;
                outputdata << this->bodies[j]->y;
                outputdata << this->bodies[j]->z;
                outputdata << this->bodies[j]->vx;
                outputdata << this->bodies[j]->vy;
                outputdata << this->bodies[j]->vz;
                outputdata << this->bodies[j]->m;
            }
    outputdata.close();}
    else
    {
        cout << "Error opening file."
        outputdata.clear();
    }

}
