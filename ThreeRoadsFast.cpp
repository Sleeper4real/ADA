#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <algorithm>
#include <iterator>
using namespace std;
void checkBipartite(long v, char type, long &count, long &connected, bool &bipartite, vector<char> &vertices, vector<vector<long> > &adj)
{
	vertices[v] = type;
	if(type == 'a')
		count++;
	for(vector<long>::iterator i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if(vertices[*i] == '?')
		{
			if(type == 'a')
				checkBipartite(*i, 'b', count, ++connected, bipartite, vertices, adj);
			else
				checkBipartite(*i, 'a', count, ++connected, bipartite, vertices, adj);
		}
		else if(vertices[*i] == vertices[v])
			bipartite = false;
	}
}
int main()
{
	int t;
	scanf("%d", &t);
	for(int c = 0; c < t; ++c)
	{
		long n, m;
		long totalRoads = 0;
		scanf("%ld%ld", &n, &m);
		vector<char> vertices(n + 1);
		vector<vector<long> > adj(n + 1);
		for(long v = 1; v <= n; ++v)
		{
			vertices[v] = '?';
		}
		for(long e = 1; e <= m; ++e)
		{
			long temp1, temp2;
			scanf("%ld %ld", &temp1, &temp2);
			adj[temp1].push_back(temp2);
			adj[temp2].push_back(temp1);
		}
		for(long v = 1; v <= n; ++v)
		{
			if(vertices[v] == '?')
			{
//				printf("Vertice %ld\n", v);
				long connected = 1;
				bool bipartite = true;
				long aSize = 0;
				checkBipartite(v, 'a', aSize, connected, bipartite, vertices, adj);
				if(bipartite == false)
				{
					long completeEdges = ((connected*(connected - 1)) >> 1);
					totalRoads += completeEdges;
//					printf("%s\t%ld\n", "Complete", completeEdges);
//					printf("Connected: %ld\n", connected);
				}
				else
				{
					long completeBipartiteEdges = aSize*(connected - aSize);
					totalRoads += completeBipartiteEdges;
//					printf("%s\t%ld\n", "Bipartite", completeBipartiteEdges);
//					printf("Connected: %ld, Set a Size: %ld\n", connected, aSize);
				}
			}
		}
		printf("%ld\n", totalRoads - m);
	}
	return 0;
}