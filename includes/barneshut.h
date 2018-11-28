#ifndef BARNESHUT
# define BARNESHUT

#define SCALING 1.0 //decrease this to improve the accuracy of the simulation, it represents how many simulation seconds correspond to seconds

#include <BH_physics_operations.h>
#include <vector>
#include <cstdlib>

class BarnesHutNode
{
	public:
	
	BarnesHutNode();
	BarnesHutNode(size_t lower, size_t upper, BarnesHutNode *parent);
	
	void	iterate(double timestep);
	
	size_t	getdepth();
	
	static BarnesHutNode	*create_octree(size_t limit, std::vector<Body*> *masses);
	
	protected:
	
	BarnesHutNode	*children[8];
	BarnesHutNode	*parent;
	
	//stars
	std::vector<Body*>		*bodies;
	
	size_t			bodystart;
	size_t			bodyend;
	
	void	create_children(BarnesHutNode *cursor, size_t limit);
	void	adjust_velocity(size_t i, const double timestep);
	void	adjust_velocity_node(size_t i, const double timestep, BarnesHutNode suboctant);
	void	update(const double timestep);
	
	BarnesHutNode	*endtree(size_t i);

};

#endif
