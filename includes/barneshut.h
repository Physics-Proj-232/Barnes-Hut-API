#ifndef BARNESHUT
# define BARNESHUT

class BarnesHutNode
{
	BarnesHutNode	*children[8];
	BarnesHutNode	*parent;
	
	//position
	double		x;
	double		y;
	double		z;

	double		mass;

	//velocity
	double		vx;
	double		vy;
	double		vz;
};

#endif
