using System.Collections;

using System.Collections.Generic;

using UnityEngine;

public class Sphere

{

public

//Create a sphere object
void Func()
{
GameObject obj = GameObject.CreatePrimitive(PrimitiveType.Sphere);
}

//Function should retrieve the variables for mass, and x, y, z position and velocity from an input file
void retrieveData()
{
    float tmpx, tmpy, tmpz;
    float tmpvx, tmpvy, tmpvz;
    float tmpmass;

    ifstream inputfile;
    inputfile.open("sample.txt");
    if(inputfile){
        while(!inputfile.eof()){
            inputfile >> tmpx;
            inputfile >> tmpy;
            inputfile >> tmpz;
            inputfile >> tmpvx;
            inputfile >> tmpvy;
            inputfile >> tmpvz;
            inputfile >> tmpmass;
        }
    }
    else{
        cout << " Error opening file!";
        inputfile.clear();
    }
}

public class Makebody : MonoBehaviour {

// Use this for initialization
void Start ()
    {
        Sphere sawyer = new Sphere();
        sawyer.Func();

    }

// Update is called once per frame
void Update (float x, float y, float z, float vx, float vy, float vz, float mass ) {

//calculates velocity per frame(VPF) to increment the movement of the body
void findVPF(float vx, float vy, float vz)
    {
    float vxpf, vxypf, vzpf;
    vxpf = vx/8;
    vypf = vy/8;
    vzpf = vz/8;
    }

//change the position of the body based off the VPF and starting position
void updatePosition(float x, float y, float z, float vxpf, float vypf, float vzpf)
    {
        obj.transform.localPosition = new Vector3(x + vxpf, y + vypf, z);
    }

//set the scale of the body by from mass
void updateScale(float mass)
    {
    if( mass > 0 && mass <= 10 )
        obj.transform.localScale = new Vector3(0.1f, 0.1f, 0.1f);
    if( mass > 10 && mass <= 20 )
        obj.transform.localScale = new Vector3(0.2f, 0.2f, 0.2f);
    if( mass > 20 && mass <= 30 )
        obj.transform.localScale = new Vector3(0.3f, 0.3f, 0.3f);
    if( mass > 30 && mass <= 40 )
        obj.transform.localScale = new Vector3(0.4f, 0.4f, 0.4f);
    if( mass > 40 && mass <= 50 )
        obj.transform.localScale = new Vector3(0.5f, 0.5f, 0.5f);
    if( mass > 50 && mass <= 60 )
        obj.transform.localScale = new Vector3(0.6f, 0.6f, 0.6f);
    if( mass > 60 && mass <= 70 )
        obj.transform.localScale = new Vector3(0.7f, 0.7f, 0.7f);
    if( mass > 70 && mass <= 80 )
        obj.transform.localScale = new Vector3(0.8f, 0.8f, 0.8f);
    if( mass > 80 && mass <= 90 )
        obj.transform.localScale = new Vector3(0.9f, 0.9f, 0.9f);
    if( mass > 90 && mass <= 100 )
        obj.transform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
    }

};


}
