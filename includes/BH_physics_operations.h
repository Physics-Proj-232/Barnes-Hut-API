#ifndef PHYSICS
# define PHYSICS

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
	void add_force(Body*, const double, const double);
	void update_position(const double);
	void	set_x(int x);
	void	set_y(int y);
	void	set_z(int z);
};

// @param softening prevents divergence (going to infinity)
// @param b pointer to Body object that enacts force on object calling function
void Body::add_force(Body *obj, const double softening, const double timestep) {
	double	fx;
	double	fy;
	double	fz;

	double dx = copysign(obj->x - this->x, 1);
	double dy = copysign(obj->y - this->y, 1);
	double dz = copysign(obj->z - this->z, 1);
	double dmass = copysign(1, this->mass);

	double dist_squared = dx * dx + dy * dy + dz * dz + softening;
	double inv_dist_cube = inv_rsqrt(dist_squared) * inv_rsqrt(dist_squared) * inv_rsqrt(dist_squared);
	double s = G * this->mass * obj->mass * inv_dist_cube;

	fx += s * dx / sqrt(dist_squared);
	fy += s * dy / sqrt(dist_squared);
	fz += s * dz / sqrt(dist_squared);
	
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
double Body::inv_rsqrt(double n) {
	const double threehalves = 1.5F;
	double x2 = n * 0.5F;
	double y = n;
	long i = *(long *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(double *)&i;
	y = y * (threehalves - (x2 * y * y));

	return y;
}

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
#endif