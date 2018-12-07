#ifndef BARNESHUT
# define BARNESHUT

#define SCALING 1.0 //decrease this to improve the accuracy of the simulation, it represents how many simulation seconds correspond to seconds
#include "BH_physics_operations.h"
#include <vector>
#include <cstdlib>

// gravitational constant

class BarnesHutNode
{
	public:
	
	BarnesHutNode();
	BarnesHutNode(size_t lower, size_t upper, BarnesHutNode *parent, int octant);
	
	void	iterate(double timestep);
	
	size_t	getdepth();
	
	BarnesHutNode	*create_octree(size_t limit, std::vector<Body*> *masses);
	void OutputData();
	
	protected:
	
	BarnesHutNode	*children[8];
	BarnesHutNode	*parent;
	
	//stars
	std::vector<Body*>		*bodies;
	//center of gravity coordinates
	double					totalmass;
	double					cx;
	double					cy;
	double					cz;
	int						octant;
	
	size_t			bodystart;
	size_t			bodyend;
	
	void	center_of_gravity();
	void	create_children(BarnesHutNode *cursor, size_t limit);
	void	adjust_velocity(size_t i, const double softening, const double timestep);
	void	adjust_velocity_node(size_t i, const double softening, const double timestep, BarnesHutNode *suboctant);
	void	update(const double timestep);
	void	sort_bodies();
	
	size_t	find_end(size_t start, size_t octant);
	Body	get_physical_center(void);
	
	BarnesHutNode	*endtree(size_t i);

};

#endif
