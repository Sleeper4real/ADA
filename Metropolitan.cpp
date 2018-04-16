#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <algorithm>
#include <queue>
#include <iterator>
#include <unordered_set>
using namespace std;
typedef unsigned long long ull;
struct vertex
{
	long no;
	long deg;
	bool operator<(const vertex& rhs) const
	{
		return deg > rhs.deg;
	}
};
int main()
{
	long n, m;
	scanf("%ld %ld", &n, &m);
	vector<unordered_set<long> > adj(n);
	for(long e = 0; e < m; ++e)
	{
		long temp1, temp2;
		scanf("%ld %ld", &temp1, &temp2);
		adj[temp1].insert(temp2);
		adj[temp2].insert(temp1);
	}
	if(m == 0)
	{
		printf("%d\n", 1);
		return 0;
	}
	int maxCities = 2;
	priority_queue<vertex> h;
	for(long v = 0; v < n; ++v)
	{
		if(adj[v].size() > 1)
		{
			vertex temp;
			temp.no = v;
			temp.deg = adj[v].size();
			h.push(temp);
		}
		else
		{
			auto it = adj[v].begin();
			if(it != adj[v].end())
			{
				adj[*it].erase(v);
			}
		}
	}
	while(h.size() > 1)
	{
		vertex current = h.top();
		unordered_set<long> temp;
		for(auto i = adj[current.no].begin(); i != adj[current.no].end(); ++i)
		{
			if(adj[*i].size() < maxCities)
			{
				adj[*i].erase(current.no);
			}
			else
				temp.insert(*i);
		}
		adj[current.no] = temp;
		for(auto i = adj[current.no].begin(); i != adj[current.no].end(); ++i)
		{
			for(auto j = next(i); j != adj[current.no].end(); ++j)
			{
				auto it = adj[*i].find(*j);
				if(it != adj[*i].end())
				{
					if(maxCities == 2)
						maxCities++;
					if(maxCities == 3)
					{
						for(auto k = next(j); k != adj[current.no].end(); ++k)
						{
							auto it1 = adj[*k].find(*i);
							auto it2 = adj[*k].find(*j);
							if(it1 != adj[*k].end() && it1 != adj[*k].end())
							{
								printf("%d\n", 4);
								return 0;
							}
						}
					}
				}
			}
			adj[*i].erase(current.no);
		}
		adj[current.no].clear();
		h.pop();
	}
	printf("%d\n", maxCities);
	return 0;
}