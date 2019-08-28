#include "fndbscan.hpp"
//g++ test.cpp  fndbscan.cpp kdtree2.cpp -o3 -o fndbscan
int main() 
{
	
	
	int N,d,rn;
	//Dosyadan okuyup array2dfloat içine veriyi aktarma. (Normal array gibi kullanılabiliniyor).
	array2dfloat realdata=readFromFile(&N,&d,"test3.txt");
	float **sups=findSupremums(realdata,N, d); //Supremumları buluyor.
	float dmax=calcDmax(sups,d); //Dmax hesaplama.
	float deps = calcDeps(dmax,0.995,1,EXP); //Deps hesaplama Exp
	cout<< deps <<endl;
	deps = calcDeps(dmax,0.995,1,LIN); //Deps hesaplama Lin
	cout<< deps <<endl;
	KDTree* tree;
	KDTreeResultVector results;
	tree = new KDTree(realdata,true);
  	tree->sort_results = true;
	/*tree->n_nearest_around_point(100,0,20,results); 
	rn = results.size();
	cout<< rn <<endl;
	for(KDTreeResult ii : results) 
	{
        	cout << ii.idx << " " << ii.dis << '\n';
   	}*/
	tree->r_nearest_around_point(100,0,deps,results); //Deps komşuluğundaki noktaları getir.
	rn = results.size();
	cout<< rn <<endl;
	
	for(KDTreeResult ii : results) 
	{
        	cout << ii.idx << " " << ii.dis << "->";
		for(int j=0;j<d;j++)
		{
			cout << realdata[ii.idx][j] <<" ";
		}
		cout << neighborhoodDegree(ii.dis,1,dmax,LIN) << " ";
		cout<< endl;
   	}
	

}
