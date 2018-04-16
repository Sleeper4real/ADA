#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <algorithm>
#include <queue>
using namespace std;
typedef unsigned long long ull;
const long max_people = 100000;
const long max_exit = 8999999;
struct location
{
	int row;
	int col;
};
location pList[max_people + 1];
location eList[max_exit + 1];
int main()
{
	int r, c;
	scanf("%d%d\n", &r, &c);
	int status[r][c];
	long people = 0;
	long exits = 0;
	queue<location> q;
	for(int i = 0; i < r; ++i)
	{
		for(int j = 0; j < c; ++j)
		{
			char a;
			scanf("%c", &a);
			if(a == 'P')
			{
				people++;
				pList[people].row = i;
				pList[people].col = j;
				status[i][j] = -2;
			}
			else if(a == 'E')
			{
				exits++;
				eList[exits].row = i;
				eList[exits].col = j;
				status[i][j] = 0;
				q.push(eList[exits]);
			}
			else if(a == 'F')
				status[i][j] = -1;
			else
				status[i][j] = -2;
		}
		char temp;
		scanf("%c", &temp);
	}
	while(q.empty() == false)
	{
		location current = q.front();
		q.pop();
		int nextTime = status[current.row][current.col] + 1;
		location temp;
		if(current.row > 0 && status[current.row - 1][current.col] == -2)
		{
			status[current.row - 1][current.col] = nextTime;
			temp.row = current.row - 1;
			temp.col = current.col;
			q.push(temp);
		}
		if(current.row < r - 1 && status[current.row + 1][current.col] == -2)
		{
			status[current.row + 1][current.col] = nextTime;
			temp.row = current.row + 1;
			temp.col = current.col;
			q.push(temp);
		}
		if(current.col > 0 && status[current.row][current.col - 1] == -2)
		{
			status[current.row][current.col - 1] = nextTime;
			temp.row = current.row;
			temp.col = current.col - 1;
			q.push(temp);
		}
		if(current.col < c - 1 && status[current.row][current.col + 1] == -2)
		{
			status[current.row][current.col + 1] = nextTime;
			temp.row = current.row;
			temp.col = current.col + 1;
			q.push(temp);
		}
	}
	for(int p = 1; p <= people; ++p)
	{
		if(status[pList[p].row][pList[p].col] == -2)
			printf("%s\n", "Died");
		else
			printf("%d\n", status[pList[p].row][pList[p].col]);
	}
	return 0;
}