#include <barneshut.h>
#include <spacebody.h>
#include <BH_physics_operations.h>

int		main(void)
{
	//input
	SpaceBody	spacebody = SpaceBody();
	BarnesHutNode	*universe = new BarnesHutNode();
	universe->create_octree(20, spacebody.inputdata("dataset"));
	
	for (int i = 0; i < 100; i++)
	{
		universe->iterate(1);
	}
	
	//output
	universe->OutputData();
	return (0);
}