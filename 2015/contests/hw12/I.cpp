
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

const int N = 300100;
int n, m;
vector<int> g[N];
int used[N];
int col[N];
int s;
int ed[N][2];

void clearG()
{
	col[s] = -1;
	used[s] = 0;
	g[s].clear();
	for (int i = 0; i < m; i++)
		for (int k = 0; k < 2; k++)
		{
			int v = ed[i][k];
			g[v].clear();
			used[v] = 0;
			col[v] = -1;
		}
	return;
}

bool dfs1(int v)
{
	used[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++)
	{
		int to = g[v][i];
		if (used[to] == 1) return true;
		if (used[to] == 2) continue;
		if (dfs1(to)) return true;
	}
	used[v] = 2;
	return false;
}

bool dfs2(int v)
{
	if ((int)g[v].size() == 0)
		return (col[v] == 0);
	for (int i = 0; i < (int)g[v].size(); i++)
	{
		int to = g[v][i];
		if (col[to] != -1)
		{
			if (col[to] == col[v])
				return true;
			continue;
		}
		col[to] = col[v] ^ 1;
		if (dfs2(to)) return true;
	}
	return false;
}

bool solve()
{
	scanf("%d%d%d", &n, &m, &s);
	if (n == 0) exit(0);
	for (int i = 0; i < m; i++)
	{
		int v, u;
		scanf("%d%d", &v, &u);
		ed[i][0] = v;
		ed[i][1] = u;
		g[v].push_back(u);
	}
	if (dfs1(s))
		return true;
	col[s] = 0;
	return dfs2(s);
}

void printAns(int idx, bool res)
{
	clearG();
	if (res)
		printf("Players can avoid first player winning in game %d.\n", idx);
	else
		printf("First player always wins in game %d.\n", idx);
	return;
}

void init()
{
	for (int i = 0; i < N; i++)
		col[i] = -1;
}

int main()
{
	freopen("gg.in", "r", stdin);
	freopen("gg.out", "w", stdout);

	init();

	for (int t = 1;; t++)
		printAns(t, solve());

	return 0;
}