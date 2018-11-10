#include <cmath> // copysign(), sqrtf()

// gravitational constant
const float G = 6.673e-11;

// template for n-bodies
class Float4 {
private:
	float mass;
	float x, y, z;    // position
	float vx, vy, vz; // velocity
	float fx, fy, fz; // force

public:
	Float4(float x,  float y,  float z, 
		   float vx, float vy, float vz, float mass) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->vx = vx;
		this->vy = vy;
		this->vz = vz;
		this->mass = mass;
	}
	void add_force(Float4*, const float);
	void update_force(const float);
};

// @param softening prevents divergence (going to infinity)
// @param b pointer to Float4 object that enacts force on object calling function
void Float4::add_force(Float4 *obj, const float softening) {

	float dx = obj->x - this->x;
	float dy = obj->y - this->y;
	float dz = obj->z - this->z;
	float dmass = copysign(1, this->mass);

	float dist_squared = dx * dx + dy * dy + dz * dz + softening;
	float inv_dist = inv_rsqrt(dist_squared);
	float inv_dist_cube = inv_dist * inv_dist * inv_dist;
	float s = G * this->mass * obj->mass * inv_dist_cube;

	this->fx += s * dx / sqrtf(dist_squared);
	this->fy += s * dy / sqrtf(dist_squared);
	this->fz += s * dz / sqrtf(dist_squared);
}

// update velocity and position using a timestep
// @param timestep	
void Float4::update_force(const float timestep) {
	this->vx += (timestep * this->fx) / this->mass;
	this->vy += (timestep * this->fy) / this->mass;
	this->vz += (timestep * this->fz) / this->mass;

	this->x += timestep * this->vx;
	this->y += timestep * this->vy;
	this->z += timestep * this->vz;
}

// fast inverse square-root algorithm
float inv_rsqrt(float n) {
	const float threehalves = 1.5F;
	float x2 = n * 0.5F;
	float y = n;
	long i = *(long *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (threehalves - (x2 * y * y));

	return y;
}
