#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <limits>
#include <queue>
#include <iterator>
using namespace std;
typedef unsigned long ul;
typedef unsigned long long ull;
struct vertex
{
	long no;
	ull dist;
	char color;
	bool operator<(const vertex& rhs) const
	{
		return dist > rhs.dist;
	}
};
struct edge
{
	long next;
	ul w;
};
int main()
{
	long n, m, s, t;
	scanf("%ld %ld %ld %ld", &n, &m, &s, &t);
	vector<vector<edge> > adj(n + 1);
	vector<vertex> vertices(n + 1);
	ull wSum = 0;
	for(long e = 0; e < m; ++e)
	{
		long i, j, w;
		scanf("%ld %ld %lu", &i, &j, &w);
		edge temp1, temp2;
		temp1.next = j;
		temp1.w = w;
		temp2.next = i;
		temp2.w = w;
		adj[i].push_back(temp1);
		adj[j].push_back(temp2);
		wSum += w;
	}
	for(long v = 1; v <= n; ++v)
	{
		vertices[v].no = v;
		vertices[v].dist = numeric_limits<ull>::max();
		vertices[v].color = 'w';
	}
	vertices[s].dist = 0;
//	vertices[s].color = 'g';
	priority_queue<vertex> h;
	h.push(vertices[s]);
	while(h.empty() == false)
	{
		vertex current = h.top();
		if(current.dist == vertices[current.no].dist)
		{
			vertices[current.no].color = 'b';
			if(current.no == t)
			{
				printf("%llu\n", wSum - current.dist);
				return 0;
			}
			for(vector<edge>::iterator i = adj[current.no].begin(); i != adj[current.no].end(); ++i)
			{
				if(vertices[(*i).next].color != 'b')
				{
					ull temp = current.dist + (*i).w;
					if(vertices[(*i).next].dist > temp)
					{
						vertices[(*i).next].dist = temp;
//						vertices[(*i).next].color = 'g';
						h.push(vertices[(*i).next]);
					}
				}
			}
		}
		h.pop();
	}
	printf("%d\n", -1);
	return 0;
}