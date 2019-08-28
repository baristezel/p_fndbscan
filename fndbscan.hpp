
#ifndef __FNDBSCAN_HPP
#define __FNDBSCAN_HPP

#include <iostream>
#include <limits>
#include "kdtree2.hpp"

using namespace std;
using namespace boost;
using namespace kdtree2;
typedef multi_array<float,2> array2dfloat;
enum membershipfunctype{LIN, EXP,};
array2dfloat readFromFile(int *N,int *dim,const char *path );
float** findSupremums(array2dfloat realdata,int N,int d);
float neighborhoodDegree(float dis,float k,float dmax,enum membershipfunctype);
float calcDmax(float** sups,int d);
float calcDeps(float dmax,float eps1, float k,enum membershipfunctype a);
#endif
