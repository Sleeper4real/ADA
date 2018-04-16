#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdint>
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>
#include <utility>
using namespace std;
typedef unsigned long ul;
typedef unsigned long long ull;
int main()
{
	string s;
	cin >> s;
	long qMark = 0;
	for(long i = 0; i < s.length(); ++i)
	{
		if(s[i] == '?')
			qMark++;
	}
	long l[qMark], r[qMark];
	ull cost = 0;
	for(long k = 0; k < qMark; ++k)
	{
		scanf("%ld %ld", &l[k], &r[k]);
		cost += r[k];
	}
	priority_queue<long> changes;
	long diff = 0;
	long k = 0;
	for(long i = 0; i < s.length(); ++i)
	{
		switch(s[i])
		{
			case '(':
				diff++;
				break;
			case ')':
				diff--;
				break;
			default:
				changes.push(r[k] - l[k]);
				diff--;
				k++;
				break;
		}
		if(diff < 0 && !changes.empty())
		{
			cost -= changes.top();
			changes.pop();
			diff += 2;
		}
		else if(diff < 0 && !changes.empty() == 0)
		{
			cout << "Impossible" << endl;
			return 0;
		}
	}
	if(diff == 0)
		cout << cost << endl;
	else
		cout << "Impossible" << endl;
	return 0;
}