#include <iostream>
#include <vector>
using namespace std;

//map implementation, requires c++11

class UnionFind 
{
	private: unordered_map<int,int> p, rank; // remember: vi is vector<int>
	public:
		UnionFind(int N) 
		{ 
			//rank.assign(N, 0);
			//p.assign(N, 0); 
			//for (int i = 0; i < N; i++) p[i] = i; 
		}
		int findSet(int i) { if(p.count(i)==0)p[i]=i; return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
		bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
		void unionSet(int i, int j) 
		{
			if (!isSameSet(i, j)) 
			{ // if from different set
				int x = findSet(i), y = findSet(j);
				if (rank[x] > rank[y]) p[y] = x; // rank keeps the tree short
				else 
				{ 
					p[x] = y;
					if (rank[x] == rank[y]) rank[y] = rank[y]+1; 
				}
			} 
		} 
};
