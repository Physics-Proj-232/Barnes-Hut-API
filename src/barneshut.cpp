#include <barneshut.h>

BarnesHutNode::BarnesHutNode()
{
	this->parent = 0;
	
	for (int x = 0; x < 8; x++)
	{
		this->children[x] = 0;
	}
}

BarnesHutNode::BarnesHutNode(size_t lower, size_t upper, BarnesHutNode *parent)
{
	this->parent = parent;
	this->bodystart = lower;
	this->bodyend = upper;
	this->bodies = parent->bodies;
	
	for (int x = 0; x < 8; x++)
	{
		this->children[x] = 0;
	}
}

BarnesHutNode::size_t	getdepth()
{
	size_t			depth = 0;
	BarnesHutNode	*node = this;
	
	while(node->parent)
	{
		node = node->parent;
		depth++;
	}
	
	return (depth);
}

BarnesHutNode::void		create_children(BarnesHutNode *cursor, size_t limit)
{
		size_t	lower;
		size_t	upper;
		lower = cursor->bodystart;
		for (int l = 0; l < 8; l++)
		{
			if (l != 7)
			{
				upper = ((l + 1) * (cursor->bodyend - cursor->bodystart))/8 //our upper bound is l/8th of the parent
			}
			else
			{
				upper = cursor->bodyend; //the last child should have an upper limit of the end of the parent
			}
			cursor->children[l] = new BarnesHutNode(lower, upper, cursor);
			lower = upper + 1;
		}
		if (cursor->children[0]->getdepth() < limit)
		{
			for (int l = 0; l < 8; l++)
			{
				create_children(cursor->children[l], limit);
			}
		}
}

BarnesHutNode::BarnesHutNode	*create_octree(size_t limit, std::vector<Body*> *masses)
{
	BarnesHutNode	*root = new BarnesHutNode();
	
	root->bodies = masses;
	create_children(root);
	
	return (root);
}

BarnesHutNode::void			adjust_velocity(size_t i, const double timestep)
{
	//adjust velocity based on all particles within the same node
	for (size_t j = this->bodystart; j < this->bodyend; j++)
	{
		if (i != j)
		{
			this->bodies[i]->add_force(this->bodies[j], 0.01, timestep);
		}
	}
	
	//adjust velocity based on other nodes.
	cursor = this;
	while (cursor->parent) //stop once we've reached the root
	{
		for (int j = 0; j < 8; j++)
		{
			if (cursor->parent->children[j] != cursor)
			{
				cursor->adjust_velocity_node(i, timestep, cursor->parent->children[j]); //compare the suboctant that contains i to all other suboctants within the same octant
			}
		}
		cursor = parent; //change our suboctant to the octant that contained the suboctant
	}
}

BarnesHutNode::BarnesHutNode	*endtree(size_t i)
{
	BarnesHutNode	cursor = this;
	
	int l = 0;
	while (cursor->children[0] && l < 8)
	{
		if (i >= cursor->children[l]->bodystart && i <= cursor->children[l]->bodyend)
		{
			cursor = cursor->children[l];
			l = 0;
			continue ;
		}
		l++;
	}
	return (cursor);
}

BarnesHutNode::void				iterate(double timestep)
{
	timestep *= SCALING; //scaling, change as necessary
	
	for (size_t i = this->bodystart; i < this->bodyend; i++)
	{
		this->endtree(i)->adjust_velocity(i);
	}
	this->update(timestep);
}

BarnesHutNode::void				update(const double timestep)
{
	//update the position of all our particles
	for (size_t i = this->bodystart; i < this->bodyend; i++)
	{
		this->bodies[i]->update_position(timestep);
	}
}