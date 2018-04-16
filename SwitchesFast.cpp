#include <stdio.h>
char input[3][3005];
bool existClause[52][52][52];
int n, clauses[3][17000];
int switchStatus[26];
int charToNum(char c)
{
	if(c >= 'a') // a = 1, b = 3, c = 5, ...
		return ((c - 'a') << 1) + 1;
	else // A = 0, B = 2, C = 4, ...
		return (c - 'A') << 1;
}
bool isFloor(int num)
{
	int switchNum = num >> 1;
	return num % 2 == switchStatus[switchNum];
}
void tryPass(int s, bool &canPass)
{
	while(s < n)
	{
		if(isFloor(clauses[0][s]) || isFloor(clauses[1][s]) || isFloor(clauses[2][s])) s++;
		else break;
	}
	if(s == n)
	{
		canPass = true;
		return;
	}
	int currentStatus[3];
	for(int i = 0; i < 3; ++i) currentStatus[i] = switchStatus[clauses[i][s] >> 1];
	for(int i = 0; i < 3; ++i)
	{
		int currentCompliant = clauses[i][s] % 2; // Make clause[i][s] = floor (0 if even, 1 if odd)
		if(currentStatus[i] == 2 || currentStatus[i] == currentCompliant) // Switch not yet determined or no need to change switch status
		{
			int switchNum = clauses[i][s] >> 1;
			switchStatus[switchNum] = currentCompliant;
			tryPass(s + 1, canPass);
			if(canPass)
				return;
			switchStatus[switchNum] = 1 - currentCompliant;
		}
	}
	for(int i = 0; i < 3; ++i) switchStatus[clauses[i][s] >> 1] = currentStatus[i];
}
int main()
{
	int t;
	scanf("%d", &t);
	for(int c = 0; c < t; ++c)
	{
		int m;
		scanf("%d", &m);
		for(int i = 0; i < 3; i++) scanf("%s", input[i]);
		for(int i = 0; i < m; i++)
		{
			for(int p = 1; p <= 2; p++) for(int q = 1; q <= 2; q++) for(int r = 1; r <= 2; r++)
			{
				// .ab. -> (a & b) v
				// .cd. -> (c & d) v
				// .ef. -> (e & f) 
				// (a & b) v (c & d) v (e & f) == 
				// (a v c v e) & (a v c v f) & (a v d v e) & (a v d v f) & (b v c v e) & (b v c v f) & (b v d v e) & (b v d v f)
				int x = charToNum(input[0][3 * i + p]), y = charToNum(input[1][3 * i + q]), z = charToNum(input[2][3 * i + r]);
				int temp;
				if(x > y) temp = x, x = y, y = temp;
				if(x > z) temp = x, x = z, z = temp;
				if(y > z) temp = y, y = z, z = temp;
				existClause[x][y][z] = true;
			}
		}
		n = 0;
		for(int i = 0; i < 52; i++) for(int j = i; j < 52; j++) for(int k = j; k < 52; k++) if(existClause[i][j][k] == 1)
		{
			clauses[0][n] = i;
			clauses[1][n] = j;
			clauses[2][n] = k;
			n++;
			existClause[i][j][k] = 0;
		}
		for(int i = 0; i < 26; i++) switchStatus[i] = 2;
		bool canPass = false;
		tryPass(0, canPass);
		if(canPass)
		{
			int turnedSwitch = 0;
			for(int i = 0; i < 26; i++) 
				if(switchStatus[i] == 1) turnedSwitch++;
			printf("%d", turnedSwitch);
			for(int i = 0; i < 26; i++)
			{ 
				if(switchStatus[i] == 1) 
				{
					printf(" %c", i + 'A');
					switchStatus[i] = 2;
				}
			}
			printf("\n");
		}
		else puts("-1");
	}
	return 0;
}