#include "barneshut.h"
#include "BH_physics_operations.h"
#include <iostream>
#include <fstream>
#include <cmath> //copysign()

using namespace std;

BarnesHutNode::BarnesHutNode()
{
	this->parent = 0;
	
	for (int x = 0; x < 8; x++)
	{
		this->children[x] = 0;
	}
}

BarnesHutNode::BarnesHutNode(size_t lower, size_t upper, BarnesHutNode *parent, int octant)
{
	this->parent = parent;
	this->bodystart = lower;
	this->bodyend = upper;
	this->bodies = parent->bodies;
	this->octant = octant;
	for (int x = 0; x < 8; x++)
	{
		this->children[x] = 0;
	}
}

size_t	BarnesHutNode::getdepth()
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

void BarnesHutNode::create_children(BarnesHutNode *cursor, size_t limit)
{
		for (int l = 0; l < 8; l++)
		{
			cursor->children[l] = new BarnesHutNode(this->bodystart, this->bodyend, cursor, l + 1);
		}
		this->sort_bodies();
		if (cursor->children[0]->getdepth() < limit)
		{
			for (int l = 0; l < 8; l++)
			{
				create_children(cursor->children[l], limit);
			}
		}
}

BarnesHutNode*	BarnesHutNode::create_octree(size_t limit, std::vector<Body*> *masses)
{
	
	this->bodies = masses;
	this->create_children(this, limit);

	return (this);
}

void	BarnesHutNode::center_of_gravity()
{
	size_t sumx = 0;
	size_t sumy = 0;
	size_t sumz = 0;
	totalmass = 0;

	//sums of position * mass of each respective body
	for (size_t i = this->bodystart; i < this->bodyend; i++)
	{
		sumx += ((*bodies)[i]->x * (*bodies)[i]->mass);
		sumy += ((*bodies)[i]->y * (*bodies)[i]->mass);
		sumz += ((*bodies)[i]->z * (*bodies)[i]->mass);
		totalmass += (*bodies)[i]->mass;
	}
	
	this->cx = sumx / totalmass;
	this->cy = sumy / totalmass;
	this->cz = sumz / totalmass;
}

void	BarnesHutNode::adjust_velocity_node(size_t i, const double softening, const double timestep, BarnesHutNode *suboctant)
{
	double	nodefx;
	double	nodefy;
	double	nodefz;

	double dx = copysign(suboctant->cx - (*bodies)[i]->x, 1);
	double dy = copysign(suboctant->cy - (*bodies)[i]->y, 1);
	double dz = copysign(suboctant->cz - (*bodies)[i]->z, 1);

	double dist_squared = dx * dx + dy * dy + dz * dz + softening;
	double inv_dist_cube = Body::inv_rsqrt(dist_squared) * Body::inv_rsqrt(dist_squared) * Body::inv_rsqrt(dist_squared);
	double s = G * totalmass * (*bodies)[i]->mass * inv_dist_cube;

	nodefx += s * dx / sqrt(dist_squared);
	nodefy += s * dy / sqrt(dist_squared);
	nodefz += s * dz / sqrt(dist_squared);

	(*bodies)[i]->vx += (timestep * nodefx) / (*bodies)[i]->mass;
	(*bodies)[i]->vy += (timestep * nodefy) / (*bodies)[i]->mass;
	(*bodies)[i]->vz += (timestep * nodefz) / (*bodies)[i]->mass;
}

void	BarnesHutNode::adjust_velocity(size_t i, const double softening, const double timestep)
{
	BarnesHutNode	*cursor;
	//adjust velocity based on all particles within the same node
	for (size_t j = this->bodystart; j < this->bodyend; j++)
	{
		if (i != j)
		{
			(*this->bodies)[i]->add_force((*this->bodies)[j], 0.01, timestep);
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
				cursor->adjust_velocity_node(i, softening, timestep, cursor->parent->children[j]); //compare the suboctant that contains i to all other suboctants within the same octant
			}
		}
		cursor = parent; //change our suboctant to the octant that contained the suboctant
	}
}

BarnesHutNode*	BarnesHutNode::endtree(size_t i)
{
	BarnesHutNode	*cursor = this;
	
	int l = 0;
	while (cursor->children[0] && l < 8)
	{
		if (i == cursor->children[l]->octant)
		{
			cursor = cursor->children[l];
			l = 0;
			continue;
		}
		l++;
	}
	return (cursor);
}

void	BarnesHutNode::iterate(double timestep)
{
	timestep *= SCALING; //scaling, change as necessary
	
	for (size_t i = this->bodystart; i < this->bodyend; i++)
	{
		this->endtree(i)->adjust_velocity(i, timestep, timestep);
	}
	this->update(timestep);
}

void	BarnesHutNode::update(const double timestep)
{
	//update the position of all our particles
	for (size_t i = this->bodystart; i < this->bodyend; i++)
	{
		(*this->bodies)[i]->update_position(timestep);
	}
	this->sort_bodies();
}

Body	BarnesHutNode::get_physical_center()
{
	Body	ret = Body(0, 0, 0, 0, 0, 0, 0);
	
	size_t	i = this->bodystart;
	
	while (i <= this->bodyend)
	{
		ret.x += (*this->bodies)[i]->x;
		ret.y += (*this->bodies)[i]->y;
		ret.z += (*this->bodies)[i]->z;
		i++;
	}
	
	ret.x /= (this->bodyend - this->bodystart + 1);
	ret.y /= (this->bodyend - this->bodystart + 1);
	ret.z /= (this->bodyend - this->bodystart + 1);
	
	return (ret);
}

size_t	BarnesHutNode::find_end(size_t start, size_t octant)
{
	while (start <= this->bodyend)
	{
		if ((*this->bodies)[start]->octant != octant)
			break ;
		start++;
	}
	
	return (start - 1);
}

void	BarnesHutNode::sort_bodies()
{
	double	x;
	double	y;
	double	z;
	
	Body	center = this->get_physical_center();
	
	size_t	i = this->bodystart;
	
	while (i <= this->bodyend)
	{
		x = (*this->bodies)[i]->x - center.x;
		y = (*this->bodies)[i]->y - center.y;
		z = (*this->bodies)[i]->z - center.z;
		
		if (x >= 0.0 && y >= 0.0 && z >= 0.0)
			(*this->bodies)[i]->octant = 1;
        else if (x < 0.0 && y >= 0.0 && z >= 0.0)
			(*this->bodies)[i]->octant = 2;
        else if (x < 0.0 && y < 0.0 && z >= 0.0)
			(*this->bodies)[i]->octant = 3;
        else if (x >= 0.0 && y < 0.0 && z >= 0.0)
			(*this->bodies)[i]->octant = 4;
        else if (x >= 0.0 && y >= 0.0 && z < 0.0)
			(*this->bodies)[i]->octant = 5;
        else if (x < 0.0 && y >= 0.0 && z < 0.0)
			(*this->bodies)[i]->octant = 6;
        else if (x < 0.0 && y < 0.0 && z < 0.0)
			(*this->bodies)[i]->octant = 7;
        else if (x >= 0.0 && y < 0.0 && z < 0.0)
			(*this->bodies)[i]->octant = 8;
		i++;
	}
	
	//quicksort here
	
	i = 0;
	while (i < 8)
	{
		for (size_t j = 0; j < this->bodyend; j++)
		{
			if ((*this->bodies)[j]->octant == i + 1)
			{
				this->children[i]->bodystart = j;
				this->children[i]->bodyend = find_end(j, i + 1);
				break ;
			}
		}
		i++;
	}
}

//This function writes the variables stored in a body object as it itterates through a node of bodies
void BarnesHutNode::OutputData()
{
	ofstream outputdata;
	outputdata.open("outputdata.txt");
	if (outputdata)
	{
		for (int j = this->bodystart; j <= this->bodyend; j++)
		{
			outputdata << (*this->bodies)[j]->x;
			outputdata << (*this->bodies)[j]->y;
			outputdata << (*this->bodies)[j]->z;
			outputdata << (*this->bodies)[j]->vx;
			outputdata << (*this->bodies)[j]->vy;
			outputdata << (*this->bodies)[j]->vz;
			outputdata << (*this->bodies)[j]->mass;
		}
		outputdata.close();
	}
	else
	{
		cout << "Error opening file.";
			outputdata.clear();
	}

}

