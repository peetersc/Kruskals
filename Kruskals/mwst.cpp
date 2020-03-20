#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;

#define SIZE 10000
int base[SIZE], vertices, edges;
pair <pair<double, int>, pair<int, int> > mwst[SIZE];

int root(int x);
void init();
void set_union(int, int);
void kruskal(pair<pair<double, int>, pair<int, int> >[], string&);

int main(int argc, char** argv)
{	
	//check for files
	if(argc != 3){
		cout << "Usage: <input file> <output file>" << endl;
		exit(1);
	}

	string IN = argv[1];
	string OUT = argv[2];
	ifstream infile (IN);

    int x, y;
    double weight, cost;

    //Initialize to all zeros
    init();

    //File Success
    if (infile.is_open()){
    	infile >> vertices >> edges;

    	for(int i = 0;i < edges;++i)
    	{
        	infile >> x >> y >> weight;
        	mwst[i] = make_pair(make_pair(weight, i), make_pair(x, y));
    	}

    	// Sort the edges
    	sort(mwst, mwst + edges);
    	kruskal(mwst, OUT);
    }

    //File Fail
    else if (infile.fail()){
       cerr << "Error Opening: " << IN
            << ": " << endl;
    }

    infile.close(); 
    return 0;
}

void init()
{
    for(int i = 0; i < SIZE; ++i)
        base[i] = i;
}

int root(int x){
    while(base[x] != x){
        base[x] = base[base[x]];
        x = base[x];
    }

    return x;
}

void set_union(int x, int y){
    int u = root(x);
    int v = root(y);
    base[u] = base[v];
}

void kruskal(pair<pair<double, int>, pair<int, int> > mwst[], string& OUT)
{
    int x, y, pos;
    double cost, minCost = 0;
    ofstream outfile;

    outfile.open(OUT);
    if (outfile.fail()){
        cerr << "Error Opening: " << OUT
             << ": " << endl;
    }

    for(int i = 0; i < edges; ++i){

        // Select edges
        x = mwst[i].second.first;
        y = mwst[i].second.second;
        cost = mwst[i].first.first;
        pos = mwst[i].first.second + 1;

        // Check for cycles
        if(root(x) != root(y)){
            minCost += cost;
            set_union(x, y);

            if (outfile.is_open()){
                outfile << setw(4) << pos << ": ";
                outfile << "(" << x << ", " << y << ") " << fixed << setprecision(1) << cost << "\n";
            }
        }    
    }
    if (outfile.is_open()){
        outfile << "Total Weight = " << fixed << setprecision(2) << minCost;
    }

    outfile.close();
    return;
}