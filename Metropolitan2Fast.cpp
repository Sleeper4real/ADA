#include <stdio.h>
#include <cstdint>
int n, m, g[100][100], maxSize, currentMax[100], path[100], adj[100];
bool DFS(int *adj, int total, int current)
{
	int nextAdj[n];
	if(total == 0)
	{
		if(maxSize < current)
		{
			maxSize = current;
			return true;
		}
		return false;
	}
	for(int i = 0; i < total; ++i)
	{
		if(current + total - i <= maxSize || current + currentMax[adj[i]] <= maxSize) return false;
		int k = 0;
		for(int j = i + 1; j < total; ++j) if(g[adj[i]][adj[j]]) nextAdj[k++] = adj[j];
		if(DFS(nextAdj, k, current + 1)) return true;
	}
	return false;
}
int main()
{
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) g[i][j] = 0;
	for(int i = 0; i < m; ++i)
	{
		int temp1, temp2;
		scanf("%d %d", &temp1, &temp2);
		g[temp1][temp2] = 1;
		g[temp2][temp1] = 1;
	}
	maxSize = 0;
	for(int i = n - 1; i >= 0; --i)
	{
		int k = 0;
		for(int j = i+1; j < n; j++ ) if(g[i][j]) adj[k++] = j;
		DFS( adj, k, 1 );
		currentMax[i] = maxSize;
	}
	printf("%d\n", maxSize);
}