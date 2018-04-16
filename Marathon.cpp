#include <iostream>
#include <stdio.h>
#include <cstdint>
#include <vector>
#include <bitset>
using namespace std;
// http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
// https://katyscode.wordpress.com/2012/05/12/printing-numbers-in-binary-format-in-c/
#define maxN 42
typedef long long ll;
int n, m, volunteers[maxN], minCost = 5000;
ll adjBits[maxN], route;
vector<vector<int> > adj(maxN);
bool visited[maxN];
void setBit(ll &a, int k)
{
	a |= (1LL << (k - 1));
}
void clearBit(ll &a, int k)
{
	a &= ~(1LL << (k - 1));
}
bool testBit(ll a, int k)
{
	if((a & (1LL << (k - 1))) != 0) return true;
	return false;
}
int routeCost(int routeSet[], int num)
{
	ll temp = 0;
	int cost = 0;
	for(int i = 0; i < num; ++i) temp |= adjBits[routeSet[i]];
	for(int i = 1; i <= n; ++i) if(testBit(temp, i)) cost += volunteers[i];
	return cost;
}
bool adjToRoute(int vertex, int current)
{
	ll temp = route;
	clearBit(temp, current);
	if(temp & adjBits[vertex]) return true;
	return false;
}
void DFS(int v, int routeSet[], int num)
{
	visited[v] = true;
	int cost = routeCost(routeSet, num);
	if(cost >= minCost) return;
	if(v == n)
	{
		minCost = cost;
		return;
	}
	int len = adj[v].size();
	for(int i = 0; i < len; ++i)
	{
		int temp = adj[v][i];
		if(!visited[temp] && !adjToRoute(temp, v))
		{
			visited[temp] = true;
			routeSet[num++] = temp;
			setBit(route, temp);
			DFS(temp, routeSet, num);
			visited[temp] = false;
			num--;
			clearBit(route, temp);
		}
	}
	return;
}
int main()
{
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &volunteers[i]);
		adjBits[i] = 0LL;
	}
	for(int j = 0; j < m; ++j)
	{
		int temp1, temp2;
		scanf("%d %d", &temp1, &temp2);
		setBit(adjBits[temp1], temp2);
		setBit(adjBits[temp2], temp1);
		adj[temp1].push_back(temp2);
		adj[temp2].push_back(temp1);
	}
	int routeSet[maxN];
	routeSet[0] = 1;
	route = 1;
	DFS(1, routeSet, 1);
	printf("%d\n", minCost);
	return 0;
}