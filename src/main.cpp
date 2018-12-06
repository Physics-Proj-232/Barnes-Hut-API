#include <barneshut.h>
#include <spacebody.h>

int		main(void)
{
	BarnesHutNode	universe = create_octree(20, input);
	
	for (int i = 0; i < 100; i++)
	{
		universe.iterate(1);
	}
	return (0);
}