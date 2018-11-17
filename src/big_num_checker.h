//
//  big_num_checker.h
//  octree
//
//  Created by Odysseas Fourakis on 11/13/18.
//  Copyright © 2018 Odysseas Fourakis. All rights reserved.
//

#ifndef big_num_checker_h
#define big_num_checker_h

#include <math.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <gmp.h>

# define TIMESTEP 1.0
#define G 0.000000000066742

# define ABS(x) (x < 0 ? -x : x)
#define UNITVECTOR(X1, X2) (X2 - X1)/ABS(X2 - X1)
#define FORCE3D(S, C2, C1) ((G * body.mass * M) / (pow(DIST(C1, C2), 3))) * UNITVECTOR(C1.S, C2.S)
//FORCE3D is in the form vector component, body being acted upon, source body

class t_vector
{
    float x, y, z;
};

class t_floatvector
{
    float x, y, z;
};

class t_invector
{
    float x, y, z, mass;
};

class t_body
{
    float mass;
    t_vector position;
    t_vector velocity;
    t_vector force;
    char octant;
};

class t_octant
{
    t_body *bodies;
    t_body **children:
    sbb_node *parent;
    size_t start;
    size_t end;
};

class t_bharg
{
    size_t prtc;
    t_octant *node;
    t_octant *universe;
};

void octree_divide(t_octant *root);
void print_tree(t_octant *root);

size_t array_len(void *ptr, size_t datasize);
int64_t parsenbodies(char *buf);

float finddist(t_vector pos);
float vectordist(t_vector p1, t_vector pt);

#define DIST(X, Y) vectordist(X, Y)

int compare_positions(const void *b1, const void *b2);
t_body *sortBodies(t_body *bodies);
t_body *(int fd, int64_t nbodies);

t_octant *barns_hut(t_octant *root);

void adjustpostion(t_octant **newuniverse, size_t index);
void adjustvelocity(t_octant ** newuniverse, size_t index, t_body body);
void adjustvelocity_nodes(t_octant **newuniverse, size_t index, const t_octant *node);

float findtotalmass(const t_octant *node);

t_vector findcenterofgravity(const t_octant *node, double combinedmass);

#endif /* big_num_checker_h */
