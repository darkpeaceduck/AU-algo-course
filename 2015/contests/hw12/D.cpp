
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

const int N = 200100;
int n[2], m1, m2;
int t;
vector<int> g[2][N];
bool used[2][N];
int val[2][N];

void scan()
{
	scanf("%d%d", &n[0], &m1);
	for (int i = 0; i < m1; i++)
	{
		int v, u;
		scanf("%d%d", &v, &u);
		v--;
		u--;
		g[0][v].push_back(u);
	}
	scanf("%d%d", &n[1], &m2);
	for (int i = 0; i < m2; i++)
	{
		int v, u;
		scanf("%d%d", &v, &u);
		v--;
		u--;
		g[1][v].push_back(u);
	}
	return;
}

int getMax(int x, int y)
{
	if (x & 1)
	{
		if ((y & 1) == 0) return x;
		return min(x, y);
	}
	else
	{
		if (y & 1) return y;
		return max(x, y);
	}
}

void dfs(int k, int v)
{
	if (used[k][v]) return;
	used[k][v] = 1;
	val[k][v] = 0;
	for (int i = 0; i < (int)g[k][v].size(); i++)
	{
		int to = g[k][v][i];
		dfs(k, to);
		val[k][v] = getMax(val[k][v], val[k][to] + 1);
	}
	return;
}

void solve()
{
	for (int k = 0; k < 2; k++)
	{
		for (int v = 0; v < n[k]; v++)
			dfs(k, v);
	}
	return;
}

bool check(int x, int y)
{
	if (x & 1)
	{
		if (y & 1)
			return true;
		return (x < y);
	}
	else
	{
		if (y & 1)
			return (y < x);
		return false;
	}
}

void query()
{
	int v, u;
	scanf("%d%d", &v, &u);
	v--;
	v = val[0][v];
	u--;
	u = val[1][u];
	bool f = check(v, u);
	if (f)
		printf("first\n");
	else
		printf("second\n");
	return;
}

int main()
{
	freopen("graphprod.in", "r", stdin);
	freopen("graphprod.out", "w", stdout);

	scan();
	solve();

	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		query();

	return 0;
}