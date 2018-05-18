
vector<vector<long> > res; //adj
vector<vi> edgeflows; //edge flow
 
long mf, f, s, t; // global variables
vi p; // p stores the BFS spanning tree from s

void augment(long v, long minEdge) 
{ // traverse BFS spanning tree from s->t
	if (v == s) { f = minEdge; return; } // record minEdge in a global var f
	else if (p[v] != -1) 
	{
	 	augment(p[v], min(minEdge,edgeflows[p[v]][v]));
		edgeflows[p[v]][v] -= f; edgeflows[v][p[v]] += f; 
	}
}

int main()// inside int main(): set up ‘res’, ‘s’, and ‘t’ with appropriate values
{

	while (1)
	{
		f = 0;
 
		vi dist(MAX_V, INF); dist[s] = 0; queue<long> q; q.push(s);
		p.assign(MAX_V, -1); // record the BFS spanning tree, from s to t!
		while (!q.empty()) 
		{
 
			long u = q.front(); q.pop();
			if (u == t) break; // immediately stop BFS if we already reach sink t
			for (long v:res[u]) // note: this part is slow
				if (edgeflows[u][v] > 0 && dist[v] == INF)
					dist[v] = dist[u] + 1, q.push(v), p[v] = u; // 3 lines in 1!
		}
 
		augment(t, INF); // find the min edge weight ‘f’ in this path, if any
		if (f == 0) break; // we cannot send any more flow (‘f’ = 0), terminate
		mf += f; // we can still send a flow, increase the max flow!
	}
	printf("%ld\n", mf);
}