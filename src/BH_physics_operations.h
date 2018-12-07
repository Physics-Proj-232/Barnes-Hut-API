#ifndef PHYSICS_H
# define PHYSICS_H

#include <cmath> // copysign(), sqrt()

// gravitational constant
const double G = 6.673e-11;

// template for n-bodies
class Body {
private:
	

public:

	double mass;
	double x, y, z;    // position
	double vx, vy, vz; // velocity
	char	octant = 0;
	
	Body(double x,  double y,  double z, 
		   double vx, double vy, double vz, double mass) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->vx = vx;
		this->vy = vy;
		this->vz = vz;
		this->mass = mass;
	}

	static double inv_rsqrt(double n);
	void add_force(Body* body, const double d1, const double d2);
	void update_position(const double d1);
	/*void	set_x(int x);
	void	set_y(int y);
	void	set_z(int z);*/
};


/*
void	Body::set_x(int x)
{
	this->x = x;
}

void	Body::set_y(int x)
{
	this->y = x;
}

void	Body::set_z(int x)
{
	this->z = x;
}
*/
#endif