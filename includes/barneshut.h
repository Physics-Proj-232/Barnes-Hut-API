#ifndef BARNESHUT
# define BARNESHUT


class Body
{
	//position;
	double	x;
	double	y;
	double	z;

	double	mass;

	//velocity
	double	vx;
	double	vy;
	double	vz;
}

class BarnesHutNode
{
	BarnesHutNode	*children[8];
	BarnesHutNode	*parent;
	
	//stars
	Body		*bodies;
};

#endif
