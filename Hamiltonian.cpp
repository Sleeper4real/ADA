#include <vector>
#include <stdio.h>
#include <cstdint>
#include <iterator>
#define maxN 100001
using namespace std;
typedef unsigned long ul;
ul n, m, k, hamCycle[maxN], previous[maxN];
int inDeg[maxN];
vector<vector<ul> > adj(maxN);
bool unexplored[maxN], found;
//int loops;
//bool end;
void DFS(ul v)
{
//	if(end) return;
//	loops++;
//	if(loops > 200) end = true;
//	printf("%lu ", v);
	hamCycle[++k] = v;
	unexplored[v] = false;
	if(v == 1)
	{
		if(k == n) found = true;
		else
		{ 
//			printf(" k != n+1(k = %lu)", k);
			k--;
			unexplored[v] = true;
		}
	//	if(found) printf(" re0 ");
	//	else printf(" re1(k = %lu) ", k);
		return;
	}
	for(vector<ul>::iterator i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if(inDeg[*i] == 1)
		{
			if(unexplored[*i]) DFS(*i);
			else
			{
				k--;
				unexplored[v] = true;
	//			printf(" re2(k = %lu) ", k);
				return;
			}
			if(!found)
			{
				k--;
				unexplored[v] = true;
			}
	//		printf(" re3(k = %lu) ", k);
			return;
		}
	}
//	puts("\nUnexplored status: ");
//	for(int i = 1; i <= n; ++i) printf("#%d: %d   ", i, unexplored[i]);
//	puts("");
	for(vector<ul>::iterator i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if(unexplored[*i]) DFS(*i);
		if(found)
		{
	//		printf(" re4(k = %lu) ", k);
			return;
		}
	}
	unexplored[v] = true;
	k--;
//	printf(" re5(k = %lu) ", k);
	return;
}
int main()
{
	scanf("%lu %lu", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		inDeg[i] = 0;
		unexplored[i] = true;
	}
	for(int j = 0; j < m; ++j)
	{
		ul temp1, temp2;
		scanf("%lu %lu", &temp1, &temp2);
		if(temp1 != temp2)
		{
			adj[temp1].push_back(temp2);
			inDeg[temp2]++;
			previous[temp2] = temp1;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		if(inDeg[i] == 0 || adj[i].size() == 0)
		{
			puts("-1");
			return 0;
		}
		else if(inDeg[i] == 1)
		{
			vector<ul> temp;
			temp.push_back(i);
			adj[previous[i]] = temp;
		}
	}
	ul u = 1;
	k = 0;
	found = false;
	hamCycle[0] = 1;
	for(vector<ul>::iterator i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		if(inDeg[*i] == 1)
		{
			DFS(*i);
			if(found)
			{
				for(int i = 0; i <= n; ++i) printf("%lu ", hamCycle[i]);
				puts("");
				return 0;
			}
			else
			{
				puts("-1");
				return 0;
			}
		}
	}
	for(vector<ul>::iterator i = adj[u].begin(); i != adj[u].end(); ++i)
	{
//		loops = 0;
//		end = false;
//		printf("%lu: ", *i);
		DFS(*i);
//		puts("");
//		for(int i = 1; i <= n; ++i) printf("#%d: %d   ", i, unexplored[i]);
//		puts("");
		if(found)
		{
			for(int i = 0; i <= n; ++i) printf("%lu ", hamCycle[i]);
			puts("");
			return 0;
		}
		k = 0;
	}
	puts("-1");
//	for(int i = 1; i <= n; ++i) printf("#%d: %d", i, unexplored[i]);
	return 0;
}