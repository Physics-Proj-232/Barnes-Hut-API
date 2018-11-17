//
//  octree.hpp
//  octree
//
//  Created by Odysseas Fourakis on 11/11/18.
//  Copyright © 2018 Odysseas Fourakis. All rights reserved.
//

#ifndef checker_h
#define checker_h

#include <stdio.h>
#include "big_num_checker.h"
#include <math.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TIMESTEP 1.0

//#define G (1.327 * pow(10, 13) //kilometers, solar masses, (km/s)^2

#define ABS(x) (x < 0 ? -x : x)
#define UNITVECTOR(X1, X2) (X2 - X1)/ABS(X2 - X1)

//class t_vector
//{
//    double x, y, z;
//};
//
//class t_floatvector
//{
//    float x, y, z;
//};
//
//class t_invector
//{
//    float x, y, z;
//    float mass, xvel, yvel, zvel, empty;
//};
//
//class t_body
//{
//    size_t id;
//    double mass;
//    t_vector position;
//    t_vector velocity;
//    char octant;
//};

class t_node
{
    t_body *bodies;
    class s_node **children;
    class s_node *parent;
    size_t start;
    size_t end;
};

//class t_bharg
//{
//    size_t prtc;
//    t_octant *node;
//    t_octant *universe;
//};

void octree_divide(t_octant *root);
void print_tree(t_octant *root);
void re_tree(t_octant *root);

size_t array_len(void *ptr, size_t datasize);
int64_t parsenbodies(char *buf);

//double finddist(t_vector pos);
//double vectordist(t_vector p1, t_vector p2);

#define DIST(X, Y) vectordist(X, Y)

int compare_position(const void *b1, const void *b2);
t_body *sortbodies(t_body *bodies);
t_body *getbodies(int fd, int64_t nbodies);

t_octant *barnes_hut(t_octant *root);
t_octant *brute_force(t_octant *root);

void adjustposition(t_octant **newuniverse, size_t index);
void adjustvelocity(t_octant **newuniverse, size_t index, t_body body);
void adjustvelocity_nodes(t_octant **newuniverse, size_t index, const t_octant *node);
//double findtotalmass(const t_octant *node);
t_vector findcenterofgravity(const t_octant *node, double combinedmass);

double sr_relativistic_mass(double m, double p);
double sr_mass_increase(double m, double v);
double sr_velocity_addition(double u_prime, double v);
double sr_length_contraction(double l, double v);
double sr_time_dilation(double t, double v);
double sr_momentum(double m, double v);
double sr_lorentz_boost_direction(double d, double dvel, double*t);

#endif /* checker_h */
