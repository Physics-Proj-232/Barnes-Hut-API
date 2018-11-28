#ifndef SPACEBODY_H
#define SPACEBODY_H

#include <fstream>
#include <iostream>
using namespace std;

//temporary class to test input function
class SpaceBody
{
    private:
    double x, y, z;
    double vx, vy ,vz;
    double mass;

    public:
    SpaceBody ()
    {
        x = 0;
        y = 0;
        z = 0;
        vx = 0;
        vy = 0;
        vz = 0;
        mass = 0;
    }

    SpaceBody(double x, double y, double z, double vx, double vy, double vz, double m)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->vx = vx;
        this->vy = vy;
        this->vz = vz;
        this->mass = m;
    }

    //print function to test input function
    void printBody()
    {
        cout << x << " " << y << " " << z << " " << vx << " " << vy << " " << vz << " " << mass << " ";
    }

    void inputdata(string filename){
        double tmpx, tmpy, tmpz; //temporary position variables
        double tmpvx, tmpvy, tmpvz; //temporary velocity variables
        double tmpmass; //temporary mass variable

        ifstream inputfile;  //name input file
        inputfile.open(filename.c_str());  //open file
        if(inputfile){  //confirm input file is open
            while(!inputfile.eof()){ //loop while not end of file
                inputfile >> tmpx; //send first piece of data in file to temp variable
                inputfile >> tmpy; //send second piece of data in file to temp variable
                inputfile >> tmpz; //send third piece of data in file to temp variable
                inputfile >> tmpvx; //send fourth piece of data in file to temp variable
                inputfile >> tmpvy; //send fifth piece of data in file to temp variable
                inputfile >> tmpvz; //send sixth piece of data in file to temp variable
                inputfile >> tmpmass; //send seventh piece of data in file to temp variable
            }
        }
        else{ //file did not open correctly
            cout << " Error opening file!";
            inputfile.clear(); // clear input stream
        }
        inputfile.close(); //close file

        //this should pass the temporary variables to the class object but its not working
        SpaceBody TempBody(tmpx, tmpy, tmpz, tmpvx, tmpvy, tmpvz, tmpmass);
    }

};
#endif
