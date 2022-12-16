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
const int SIZEE=5;
const int NoOfLines = 10;
const int MaxPressure=50;

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
	pq.push(make_pair(0.0, (SIZEE+1)*((SIZEE-1)/2)));
	int i;
	for (i = 0; i < SIZEE*SIZEE; i++)
	{
		pressure[i] = INFINITE;

	}
	parent[(SIZEE+1)*((SIZEE-1)/2)] = -1;
	pressure[(SIZEE+1)*((SIZEE-1)/2)]=0.0;

	while (!pq.empty())
	{
		int u = pq.top().S;
		pq.pop();
		int quo=(u/SIZEE);
		if (quo-1 >=0)
		 if (copy[quo-1][u-quo*SIZEE]!=INFINITE)
			if ( pressure[u-SIZEE]>pressure[u]+copy[quo-1][u-quo*SIZEE])
			{ 
				pressure[u-SIZEE]=pressure[u]+copy[quo-1][u-quo*SIZEE]; 
				pq.push(make_pair(pressure[u-SIZEE], u-SIZEE)); 
				parent[u-SIZEE] = u;
			}
		if (u-quo*SIZEE+1<SIZEE)
		 if (copy[quo][u-quo*SIZEE+1]!=INFINITE)
			if ( pressure[u+1]>pressure[u]+copy[quo][u-quo*SIZEE+1])
			{ 
				pressure[u+1]=pressure[u] + copy[quo][u-quo*SIZEE+1]; 
				pq.push(make_pair(pressure[u+1], u+1)); 
				parent[u+1] = u;
			}
		if (quo+1 <SIZEE)
		 if (copy[quo+1][u-quo*SIZEE]!=INFINITE)
			if ( pressure[u+SIZEE]>pressure[u]+copy[quo+1][u-quo*SIZEE])
			{ 
				pressure[u+SIZEE]=pressure[u] + copy[quo+1][u-quo*SIZEE]; 
				pq.push(make_pair(pressure[u+SIZEE], u+SIZEE)); 
				parent[u+SIZEE] = u;
			}
		if (u-quo*SIZEE-1>=0)
		 if (copy[quo][u-quo*SIZEE-1]!=INFINITE)
			if ( pressure[u-1]>pressure[u]+copy[quo][u-quo*SIZEE-1])
			{  
				pressure[u-1]=pressure[u] + copy[quo][u-quo*SIZEE-1]; 
				pq.push(make_pair(pressure[u-1], u-1)); 
				parent[u-1] = u;
			}
		//cout<<"at node number "<<quo<<" "<<u-quo*SIZEE<<endl;
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
		//cout<<"heya "<<Path(ff);
		if (Path(ff)==1)
			if(pressure[ff] < distend)
			{
				endindex = ff;
				distend = pressure[endindex];
			}
	}
	for (int ff = 0; ff <SIZEE*SIZEE ; ff+=SIZEE)
	{
		//cout<<"heya "<<Path(ff);
		if (Path(ff)==1)
			if(pressure[ff] < distend)
			{
				endindex = ff;
				distend = pressure[endindex];
			}
	}
	for (int ff = 1; ff <SIZEE-1 ; ff+=1)
	{
		//cout<<"heya "<<Path(ff);
		if (Path(ff)==1)
			if(pressure[ff] < distend)
			{
				endindex = ff;
				distend = pressure[endindex];
			}
	}
	for (int ff = V*(V-1)+1; ff <V*V-1 ; ff+=1)
	{
		//cout<<"heya "<<Path(ff);
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
	//printPath(endindex);
	cout<<endl;
	return 1;}
}

int Graph::Path(int j)
{
	if (j==-1)
		 return 0;
	else if (j==(SIZEE+1)*((SIZEE-1)/2))
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

	vector<float> pxavg;
	vector<float> fracyavg;
	vector<float> flowyavg;
	int count = 0;
	int n=SIZEE;
	//int n = 20, count = 0;
	float interval = atof(argv[1]);
	float margin = atof(argv[2]);
	int threshold=NoOfLines;
	float maxpressavg=0;
	float minpressavg=0;	
	//float interval = 0.005;
	for(float ix = 0; ix <=MaxPressure ;ix += interval)
	{
			pxavg.push_back(ix);
			fracyavg.push_back(0.0);
			flowyavg.push_back(0.0);
	}
	ofstream X;
	X.open("result/x"+to_string(SIZEE)+".txt");
	for (int i = 0; i < pxavg.size(); i++)
		X << pxavg[i] << " ";
	X << endl;
	X.close();
	srand(time(NULL));
	for (int k = 0; k < NoOfLines; k++) 
	{

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
		arr[((SIZEE-1)/2)][((SIZEE-1)/2)]=0.0;
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
		int temp=g.shortestPath(arr);
		if(temp==0)
			threshold-=1;
		double fin_p = g.distend;
		double maxpress=0;
		for (int i=1; i<n*n; i++)
			if (g.pressure[i]>maxpress && g.pressure[i]<INFINITE)
				maxpress=g.pressure[i];
		cout<<"MAX PRESSURE for line "<<k+1<<" = "<<maxpress<<endl;
		//maxpressavg+=maxpress;
		//minpressavg+=fin_p;
		if (temp==1){
		maxpressavg+=maxpress;
		minpressavg+=fin_p;}
		//FRACTION
		vector<float> fracy;
		for(float i = 0; i <= MaxPressure;i += interval)
		{
			int countt = 0;
			//cout<<i<<endl;
			for (int j=0; j<n*n; j++)
			{ if (g.pressure[j]<=i)
				if ( g.Path(j)==1)
					countt=countt+1;
			}
			fracy.push_back( (float) countt / (float)(SIZEE*SIZEE));
			if (temp==1){
				countt=float(i/interval);
				fracyavg[countt]+=fracy.back();}
		}
		
		ofstream Y;
		Y.open("result/fracy" + to_string(k) + ".txt");
		for (int i = 0; i < fracy.size(); i++)
			Y << fracy[i] << " ";
		Y << endl;
		Y.close();


		//FLOW RATE
		vector<float> flowy;
		for(float i = 0; i <= MaxPressure;i += interval)
		{
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
				for (int ff = 0; ff <n*n ; ff+=n)
					if (i>g.pressure[ff])
						var=var-(i/g.pressure[ff])+1;
				for (int ff = 1; ff <n-1 ; ff+=1)
					if (i>g.pressure[ff])
						var=var-(i/g.pressure[ff])+1;
				for (int ff = n*(n-1)+1; ff <n*n-1 ; ff+=1)
					if (i>g.pressure[ff])
						var=var-(i/g.pressure[ff])+1;
				flowy.push_back(-var);
			}
			if (temp==1){
				int countt=float(i/interval);
				//flowyavg[countt]=((flowyavg[countt]*flowyavg.size()+flowy.back())/(flowyavg.size()+1));}
				flowyavg[countt]+=flowy.back();}
		}
		Y.open("result/flowy" + to_string(k) + ".txt");
		for (int i = 0; i < flowy.size(); i++)
			Y << flowy[i] << " ";
		Y << endl;
		Y.close();
	}
	ofstream Y;
	Y.open("result/fracyavg"+to_string(SIZEE)+".txt");
	for (int i = 0; i < fracyavg.size(); i++)
		Y << fracyavg[i] /threshold<< " ";
	Y << endl;
	Y.close();
	Y.open("result/flowyavg"+to_string(SIZEE)+".txt");
	for (int i = 0; i < flowyavg.size(); i++)
		Y << flowyavg[i]/threshold << " ";
	Y << endl;
	Y.close();
	system("python3 plot_2.py");

	cout<<"No. of solutions out of "<<NoOfLines<<" is "<<threshold<<endl;
	//Y.open("size.txt");
	Y.open("size.txt", ios::app);
	Y <<SIZEE<<" ";
	Y.close();
	//Y.open("MaxPress.txt");
	Y.open("MaxPress.txt", std::ios::app);
	Y<<maxpressavg/threshold<<" ";
	Y.close();
	//Y.open("MinPress.txt");
	Y.open("MinPress.txt", std::ios::app);
	Y<<minpressavg/threshold<<" ";
	Y.close();

}
