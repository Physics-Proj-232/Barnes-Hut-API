#ifndef SPACEBODY_H
#define SPACEBODY_H

#include <fstream>
#include <iostream>
using namespace std;

//temporary class to test input function
class SpaceBody
{
    private:
    float xpos, ypos, zpos;
    float velx, vely ,velz;
    float mass;

    public:
    SpaceBody ()
    {
        xpos = 0;
        ypos = 0;
        zpos = 0;
        velx = 0;
        vely = 0;
        velz = 0;
        mass = 0;
    }

    SpaceBody(float x, float y, float z, float vx, float vy, float vz, float m)
    {
        xpos = x;
        ypos = y;
        zpos = z;
        velx = vx;
        vely = vy;
        velz = vz;
        mass = m;
    }

    //print function to test input function
    void printBody()
    {
        cout << xpos << " " << ypos << " " << zpos << " " << velx << " " << vely << " " << velz << " " << mass << " ";
    }

    void inputdata(string filename){
        float tmpx, tmpy, tmpz; //temporary position variables
        float tmpvx, tmpvy, tmpvz; //temporary velocity variables
        float tmpmass; //temporary mass variable

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
