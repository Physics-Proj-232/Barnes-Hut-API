#ifndef PHYSICS
# define PHYSICS

#include <cmath> // copysign(), sqrtf()

// gravitational constant
const double G = 6.673e-11;

// template for n-bodies
class Body {
private:
	double mass;
	double x, y, z;    // position
	double vx, vy, vz; // velocity

public:
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
	void add_force(Body*, const double);
	void update_force(const double);
};

// @param softening prevents divergence (going to infinity)
// @param b pointer to Body object that enacts force on object calling function
void Body::add_force(Body *obj, const double softening, const double timestep) {
	double	fx;
	double	fy;
	double	fz;

	double dx = obj->x - this->x;
	double dy = obj->y - this->y;
	double dz = obj->z - this->z;
	double dmass = copysign(1, this->mass);

	double dist_squared = dx * dx + dy * dy + dz * dz + softening;
	double inv_dist = inv_rsqrt(dist_squared);
	double inv_dist_cube = inv_dist * inv_dist * inv_dist;
	double s = G * this->mass * obj->mass * inv_dist_cube;

	fx += s * dx / sqrtf(dist_squared);
	fy += s * dy / sqrtf(dist_squared);
	fz += s * dz / sqrtf(dist_squared);
	
	this->vx += (timestep * fx) / this->mass;
	this->vy += (timestep * fy) / this->mass;
	this->vz += (timestep * fz) / this->mass;
}

// update velocity and position using a timestep
// @param timestep	
void Body::update_position(const double timestep) {
	this->x += timestep * this->vx;
	this->y += timestep * this->vy;
	this->z += timestep * this->vz;
}

// fast inverse square-root algorithm
double inv_rsqrt(double n) {
	const double threehalves = 1.5F;
	double x2 = n * 0.5F;
	double y = n;
	long i = *(long *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(double *)&i;
	y = y * (threehalves - (x2 * y * y));

	return y;
}

#endif