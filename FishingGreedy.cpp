#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>
#include <utility>
#include <map>
using namespace std;
typedef unsigned long ul;
typedef unsigned long long ull;
struct State
{
	long fish;
	int pond;
};
int main()
{
	int t;
	scanf("%d", &t);
	for(int c = 0; c < t; ++c)
	{
		int n;
		int k;
		scanf("%d %d", &n, &k);
		long f[n + 1];
		long d[n + 1];
		for(int i = 1; i <= n; ++i)
			scanf("%ld %ld", &f[i], &d[i]);
		int fishingTime = k;
		ull maxFish = 0;
		vector<int> maxMovement(n + 1);
		maxMovement[1] = fishingTime;
		vector<State> bestStates(k + 1);
		int maxPonds = 1;
		for(int u = 1; u <= fishingTime; ++u)
		{
			long fish_u1 = max(f[1] - (u - 1)*d[1], (long) 0);
			maxFish += fish_u1;
			bestStates[u].fish = fish_u1;
			bestStates[u].pond = 1;
		}
		for(int i = 2; i <= n; ++i)
		{
			fishingTime--;
			ull currentFish = 0;
			vector<int> currentMovement(k + 1);
			vector<State> temp(k + 1);
			int a = 1, b = 1, j = 1;
			while(j <= fishingTime)
			{
				long fish_bi = max(f[i] - (b - 1)*d[i], (long) 0);
				if(bestStates[a].fish < fish_bi)
				{
					temp[j].fish = fish_bi;
					temp[j].pond = i;
					currentFish += fish_bi;
					currentMovement[i]++;
					j++;
					b++;
		 		}
		 		else
		 		{
		 			temp[j] = bestStates[a];
		 			currentFish += bestStates[a].fish;
		 			currentMovement[bestStates[a].pond]++;
		 			a++;
		 			j++;
		 		}
			}
			bestStates = temp;
			if(currentFish > maxFish)
			{
				maxFish = currentFish;
				maxMovement = currentMovement;
				maxPonds = i;
			}
		}
		int operations = 0;
		for(int i = 1; i <= n; ++i)
		{
			if(maxMovement[i] != 0)
				operations += 2;
		}
		if(maxMovement[1] != 0)
			operations--;
		printf("%llu %d\n", maxFish, operations);
		if(maxMovement[1] != 0)
			printf("%s %d\n", "fish", maxMovement[1]);
		for(int i = 2; i <= maxPonds; ++i)
		{
			if(maxMovement[i] != 0)
			{
				printf("%s %d\n", "move", i);
				printf("%s %d\n", "fish", maxMovement[i]);
			}
		}
	}
	return 0;
}