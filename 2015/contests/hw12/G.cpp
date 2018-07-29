
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 5500;
int n;
int g[N];
bool mex[N];


int main()
{
	freopen("cruel.in", "r", stdin);
	freopen("cruel.out", "w", stdout);

	g[0] = g[1] = 0;
	for (int x = 2; x < N; x++)
	{
		for (int i = 0; i < N; i++)
			mex[i] = 0;
		for (int i = 0; i < x; i++)
		{
			int l = i;
			int r = x - i - 1;
			mex[ g[l] ^ g[r] ] = 1;
		}
		g[x] = 0;
		while(mex[g[x]]) g[x]++;
	}

	scanf("%d", &n);
	if (g[n] == 0)
	{
		printf("Mueller\n");
		return 0;
	}
	printf("Schtirlitz\n");
	for (int i = 0; i < n; i++)
	{
		int l = i, r = n - i - 1;
		if (g[l] == g[r])
			printf("%d\n", i + 1);
	}

	return 0;
}