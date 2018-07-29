
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 111;
const int M = 3 * N;
int n, m, s;
int g[N][N];
bool mex[M];

int getG(int x, int y)
{
	if (x > y) swap(x, y);
	return g[x][y];
}

int main()
{
	freopen("choco.in", "r", stdin);
	freopen("choco.out", "w", stdout);

	scanf("%d%d%d", &n, &m, &s);
	for (int x = 1; x < N; x++)
		for (int y = x; y < N; y++)
		{
			if (x == 1 && y <= s)
			{
				g[x][y] = g[y][x] = 0;
				continue;
			}
			for (int i = 0; i < M; i++)
				mex[i] = 0;
			for (int nx = 1; nx < x; nx++)
			{
				int val = getG(nx, y) ^ getG(x - nx, y);
				mex[val] = 1;
			}
			for (int ny = 1; ny < y; ny++)
			{
				int val = getG(x, ny) ^ getG(x, y - ny);
				mex[val] = 1;
			}
			g[x][y] = 0;
			while(mex[g[x][y]]) g[x][y]++;
			g[y][x] = g[x][y];
		}
	/*
	for (int x = 1; x <= 5; x++)
	{
		for (int y = 1; y <= 5; y++)
			printf("%d ", g[x][y]);
		printf("\n");
	}*/
	if (n > m) swap(n, m);
	printf("%d\n", (g[n][m] == 0 ? 2 : 1));

	return 0;
}