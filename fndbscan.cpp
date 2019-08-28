
#include "fndbscan.hpp"


array2dfloat readFromFile(int *N,int *dim,const char *path )
{
	FILE* ptr = fopen(path,"r"); 
	bool flag=false;	
	fscanf(ptr,"%d %d",N,dim);
	array2dfloat data(extents[*N][*dim]);
  	for(int i=0;i<*N;i++)
  	{
		for(int j=0;j<*dim;j++)
		{
			fscanf(ptr,"%f",&data[i][j]);
		}
		
	}
	return data;
}
float** findSupremums(array2dfloat realdata,int N,int d)
{
	float **sups = (float**)malloc(d*sizeof(float*));
	for(int i=0;i<d;i++)
	{
		sups[i] = (float*)malloc(2*sizeof(float));
		sups[i][0] = numeric_limits<float>::max();
		sups[i][1] = numeric_limits<float>::min();
	}	
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<d;j++)
		{
			if(realdata[i][j]<sups[j][0]) sups[j][0] = realdata[i][j];
			if(realdata[i][j]>sups[j][1]) sups[j][1] = realdata[i][j];		
		}
	}
	return sups;	
}

float calcDmax(float** sups,int d)
{
	float dist=0; 
	for(int i=0;i<d;i++)
	{
		dist+=pow(sups[i][1]-sups[i][0],2);
	}
	dist=sqrt(dist);
	return dist;
}

float calcDeps(float dmax,float eps1, float k,enum membershipfunctype t)
{
	if (t == EXP)
		return dmax*((sqrt(log(1/eps1)))/k);
	else if (t == LIN)
		return (dmax*(1-eps1))/k;
}

float neighborhoodDegree(float dis,float k,float dmax,enum membershipfunctype t)
{
	if (t == EXP)
		return exp(-pow(k*(dis/dmax),2.f));
	else if (t == LIN)
		return max((1-(k*(dis/dmax))),0.f);
}

