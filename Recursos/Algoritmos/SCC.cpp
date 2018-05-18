#define INF INT_MAX;

vector<vii> AdjList;
vi dfs_num, dfs_low, S, visited;
int dfsNumberCounter,numSCC,UNVISITED=-1,VISITED=1;

void tarjanSCC(int u) 
{
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
	S.push_back(u);
	// stores u in a vector based on order of visitation
	visited[u] = 1;
	for (int j = 0; j < (int)AdjList[u].size(); j++) 
	{
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == UNVISITED)
		tarjanSCC(v.first);
		if (visited[v.first])
		// condition for update
		dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
	}
	if (dfs_low[u] == dfs_num[u])
	{
		bool agg = false;
		while (1) 
		{
			int v = S.back(); S.pop_back(); visited[v] = 0;
			//aca se ouede imprimir la visita si es necesario
			if (u == v) break; 
		}
	} 
}