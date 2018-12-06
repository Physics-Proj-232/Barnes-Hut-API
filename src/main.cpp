#include <barneshut.h>
#include <spacebody.h>

int		main(void)
{
	//input
	BarnesHutNode	universe = create_octree(20, inputdata("dataset"));
	
	for (int i = 0; i < 100; i++)
	{
		universe.iterate(1);
	}
	
	//output
	universe.OutputData();
	return (0);
}