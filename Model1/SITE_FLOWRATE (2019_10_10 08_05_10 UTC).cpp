#include <iostream>
#include <vector>
#include<list>
#include <iterator>
#include <algorithm>
#include <queue>
#include <ctime>
#include <fstream>
#include <string>  
#include <iomanip> 
#include <cmath>  
#include <cstdlib> 
using namespace std;

#define F first
#define S second

typedef pair<double, int> iPair;

const double INFINITE = 1000000.0;
const int SIZEE=100;
const int NoOfLines = 10;

//----------------------------------------------------------
float roundme(float var) 
{ 
    float value = (int)(var * 1000 + .5); 
    return (float)value / 1000; 
} 


struct mindist
{
    bool operator() (iPair const &a, iPair const &b) { return a.F > b.F; }
};
class Graph 
{ 
    int V;   

  
public: 
    Graph(int V);  
    int shortestPath(double copy[][SIZEE]); 
	void printPath(int j);
	int Path(int j);
	double distend;
	vector <int> parent;
	vector <double> pressure;
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
	distend = INFINITE;
	for (int why=0;why<V*V;why++){
		pressure.push_back(INFINITE);
		parent.push_back(-1);
	}
} 

int Graph::shortestPath(double copy[SIZEE][SIZEE])
{
	//iPair= <pressure, node number>
	priority_queue< iPair, vector <iPair> , mindist> pq; 
	pq.push(make_pair(0.0, SIZEE*((SIZEE+1)/2-1)));
	int i;
	for (i = 0; i < SIZEE*SIZEE; i++)
	{
		pressure[i] = INFINITE;

	}
	parent[SIZEE*((SIZEE+1)/2-1)] = -1;
	pressure[SIZEE*((SIZEE+1)/2-1)]=0.0;

	while (!pq.empty())
	{
		int u = pq.top().S;
		pq.pop();
		if ((u/SIZEE)-1 >=0)
		 if (copy[(u/SIZEE)-1][u-(u/SIZEE)*SIZEE]!=INFINITE)
			if ( pressure[u-SIZEE]>pressure[u]+copy[(u/SIZEE)-1][u-(u/SIZEE)*SIZEE])
			{ 
				pressure[u-SIZEE]=pressure[u]+copy[(u/SIZEE)-1][u-(u/SIZEE)*SIZEE]; 
				pq.push(make_pair(pressure[u-SIZEE], u-SIZEE)); 
				parent[u-SIZEE] = u;
			}
		if (u-(u/SIZEE)*SIZEE+1>=0)
		 if (copy[(u/SIZEE)][u-(u/SIZEE)*SIZEE+1]!=INFINITE)
			if ( pressure[u+1]>pressure[u]+copy[(u/SIZEE)][u-(u/SIZEE)*SIZEE+1])
			{ 
				pressure[u+1]=pressure[u] + copy[(u/SIZEE)][u-(u/SIZEE)*SIZEE+1]; 
				pq.push(make_pair(pressure[u+1], u+1)); 
				parent[u+1] = u;
			}
		if ((u/SIZEE)+1 >=0)
		 if (copy[(u/SIZEE)+1][u-(u/SIZEE)*SIZEE]!=INFINITE)
			if ( pressure[u+SIZEE]>pressure[u]+copy[(u/SIZEE)+1][u-(u/SIZEE)*SIZEE])
			{ 
				pressure[u+SIZEE]=pressure[u] + copy[(u/SIZEE)+1][u-(u/SIZEE)*SIZEE]; 
				pq.push(make_pair(pressure[u+SIZEE], u+SIZEE)); 
				parent[u+SIZEE] = u;
			}
		if (u-(u/SIZEE)*SIZEE-1>=0)
		 if (copy[(u/SIZEE)][u-(u/SIZEE)*SIZEE-1]!=INFINITE)
			if ( pressure[u-1]>pressure[u]+copy[(u/SIZEE)][u-(u/SIZEE)*SIZEE-1])
			{  
				pressure[u-1]=pressure[u] + copy[(u/SIZEE)][u-(u/SIZEE)*SIZEE-1]; 
				pq.push(make_pair(pressure[u-1], u-1)); 
				parent[u-1] = u;
			}
		
	}	
	/*for (i=0; i<V*V; i++)
	{
		if (pressure[i]==INFINITE)
			printf("inff ");
		else
			printf("%.2f ",pressure[i]);
		if (i+1-((i+1)/SIZEE)*SIZEE==0)
			cout<<endl;
	}
	for (i=0; i<V*V; i++)
	{
		cout<<parent[i]<<" ";
		if (i+1-((i+1)/SIZEE)*SIZEE==0)
			cout<<endl;
	} */
	int endindex=-1 ;
	distend=INFINITE;
	for (int ff = V-1; ff <SIZEE*SIZEE ; ff+=SIZEE)
	{
		cout<<"heya "<<Path(ff);
		if (Path(ff)==1)
			if(pressure[ff] < distend)
			{
				endindex = ff;
				distend = pressure[endindex];
			}
	}
	if (endindex==-1)
		{cout<<"NO PATH"<<endl; return 0;}
	else {
	int src = 0;
	printf("Vertex\t Distance\tPath");
	printf("\n%d -> %d \t\t %f\t\t%d ",src, endindex, distend, src);
	printPath(endindex);
	cout<<endl;
	return 1;}
}

int Graph::Path(int j)
{
	if (j==-1)
		 return 0;
	else if (j==SIZEE*((SIZEE+1)/2-1))
		 return 1;
	else 
		return Path(parent[j]);
}
void Graph::printPath(int j)
{
	// Base Case : If j is source 
	if (parent[j] == -1)
		return;

	printPath(parent[j]);

	printf("%d ", j);
}



int main(int argc, char* argv[])
{
	vector<float> px1avg;
	vector<float> flowyavg;
	int count = 0;
	int n=SIZEE;
	//int n = 20, count = 0;
	float interval = atof(argv[1]);
	float margin = atof(argv[2]);
	int threshold=NoOfLines;
	//float interval = 0.005;
	for(float ix = 0; ix <=100 ;ix += interval)
	{
			px1avg.push_back(ix);
			flowyavg.push_back(0.0);
	}
	for (int k = 0; k < NoOfLines; k++) 
	{
		srand(time(NULL));
		int count = 0;
	    double arr[SIZEE][SIZEE];
	    for (int i = 0; i < n; i++)
	    {
			for (int j = 0; j < n; j++)
			{
				arr[i][j] = roundme(((double)rand() / (RAND_MAX)));
				if (arr[i][j] > margin || arr[i][j]==0.0) 
				{
					arr[i][j] = INFINITE;
					count++;
				}
			}
		}
		arr[((SIZEE+1)/2-1)][0]=0.0;
		/*
		for (int index1=0; index1<SIZEE; index1++)
			{for(int index2=0;index2<SIZEE;index2++)
				if(arr[index1][ index2]>1)
					printf("inff ");
				else
					printf("%.2f ",arr[index1][index2]);
			cout<<endl;}
		*/
		float blockage = (float)(count*100) / (float)(n * n);
		cout<<"Blockage= "<<blockage<<endl;
		Graph g(n);
		if(g.shortestPath(arr)==0)
			threshold-=1;
		double fin_p = g.distend;
		double maxpress=0;
		for (int i=1; i<n*n; i++)
			if (g.pressure[i]>maxpress && g.pressure[i]<INFINITE)
				maxpress=g.pressure[i];
		cout<<"MAX PRESSURE="<<maxpress<<endl;
		
	

//FLOW RATE
		vector<float> px1;
		vector<float> flowy;
		for(float i = 0; i <= 100;i += interval)
		{
			px1.push_back(i);
			if (i<=fin_p)
			{
				flowy.push_back( 0.0);
			}
			else
			{
				float var=0.0;
				for (int ff = n-1; ff <n*n ; ff+=n)
					if (i>g.pressure[ff])
						var=var-(i/g.pressure[ff])+1;
				flowy.push_back(-var);
			}
			int countt=float(i/interval);
			flowyavg[countt]=((flowyavg[countt]*(k))+flowy.back())/float(k+1);
		}
		ofstream X;
		X.open("result1/flowx" + to_string(k) + ".txt");
		for (int i = 0; i < px1.size(); i++)
			X << px1[i] << " ";
		X << endl;
		X.close();
		ofstream Y;
		Y.open("result1/flowy" + to_string(k) + ".txt");
		for (int i = 0; i < flowy.size(); i++)
			Y << flowy[i] << " ";
		Y << endl;
		Y.close();
		system("python3 plot_flowrate1.py");
	}
	ofstream X;
	X.open("result1/flowxavg.txt");
	for (int i = 0; i < px1avg.size(); i++)
		X << px1avg[i] << " ";
	X << endl;
	X.close();
	ofstream Y;
	Y.open("result1/flowyavg.txt");
	for (int i = 0; i < flowyavg.size(); i++)
		Y << flowyavg[i] << " ";
	Y << endl;
	Y.close();
	system("python3 plot_flowrate1.py");
	cout<<"No. of solutions out of "<<NoOfLines<<" is "<<threshold<<endl;
}
