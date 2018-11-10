#ifndef BARNESHUT
# define BARNESHUT

class BarnesHutNode
{
	BarnesHutNode	*children[8];
	BarnesHutNode	*parent;
	
	//stars
	Body		*bodies;
};

#endif
