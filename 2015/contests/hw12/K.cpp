
#include <iostream>
#include <stdio.h>
#include <vector>
#include <assert.h>
#include <map>
using namespace std;
#define pb push_back

const int N = 1 << 17;
vector<int> v[N];
vector<int> u[N];
bool used[N];
int q[N];
int res[N];
int gotowin[N];


const int inf = (int)1e7;
int lose[N];
int win[N];
int colorl[N];
int colorf[N];

int printtext(int s)
{
	assert(s >= -1);
	if (s >= inf || s == -1)
		printf(" INF\n");
	else
		printf(" %d\n", s);
}

void print(int num, int *dp)
{
	int x = res[num];
	assert(x >= -1 && x <= 1);
	if (x == -1)
		printf("LOSE"), printtext(dp[num]);
	else if (x == 0)
		printf("DRAW\n");
	else if (x == 1)
		printf("WIN"), printtext(dp[num]);
}

int main()
{
	freopen("labyrinth.in" , "rt", stdin);
	freopen("labyrinth.out", "w", stdout);
//	freopen("input.txt", "rt", stdin);

	int n, m;
	int i, j;

	int x, y;
	int cnt = 0;

	while (scanf(" %d %d", &n, &m) == 2)
	{
		cnt++;
		#ifdef ONLINE_JUDGE
		assert(cnt < 2);
		#endif
		
		for (i = 1; i <= n; i++)
		{
			v[i].clear();
			u[i].clear();
		}

		for (i = 1; i <= n ;i++)
		{
			used[i] = false;
			res[i] = 0;
			gotowin[i] = 0;
			colorl[i] = 0;
			colorf[i] = 0;
		}

		for (i = 1; i <= m; i++)
		{
			scanf(" %d %d", &x, &y);
			v[x].pb(y);
			u[y].pb(x);
		}

		int l = 0;
		int r = 0;

        for (i = 1; i <= n; i++)
        {
        	if ((int)v[i].size() == 0)
        	{
        		q[r++] = i;
        		res[i] = -1;
        	}
        }

		while (l < r)
		{
			int cur = q[l];
			l++;
			used[cur] = true;

			if (res[cur] == 1)
				for (i = 0; i < (int)u[cur].size(); i++)
				{
					int dest = u[cur][i];
					if (!used[dest])
					{
						gotowin[dest]++;
						if (gotowin[dest] == (int)v[dest].size())
						{
							res[dest] = -1;
						//	cerr << dest << " " << - 1 << endl;
							q[r++] = dest;
							used[dest] = true;
						}
					}
				}

			if (res[cur] == -1)
			{
			    for (i = 0; i < (int)u[cur].size(); i++)
				{
					int dest = u[cur][i];

					if (!used[dest])
					{
						res[dest] = 1;
						//cerr << dest << " " << 1 << endl;
						q[r++] = dest;
						used[dest] = true;
					}
				}
			}
		}

		l = r = 0;

		for (i = 1; i <= n; i++)
		{
			lose[i] = win[i] = inf;
		}

		static int gomax[N], gocur[N];
		int dp[N];

		for (i = 1; i <= n; i++)
		{
			gomax[i] = 0;
			gocur[i] = 0;

			if (res[i] == 1)
				dp[i] = -1;
			else
				dp[i] = inf;
		}

		for (i = 1; i <= n; i++)
		{
			if (res[i] == 0)
				continue;
			for (j = 0; j < (int)v[i].size(); j++)
			{
				int dest = v[i][j];

				if (res[dest] == -res[i])
					gomax[i]++;
			}
		}

		for (i = 1; i <= n; i++)
		{
			if (res[i] == 0)
				continue;
			used[i] = false;

			if ((int)v[i].size() == 0)
				q[r++] = i, dp[i] = 0;
		}

		while (l < r)
		{
		    int cur = q[l];
		    l++;
		    used[cur] = true;

		    for (i = 0; i < (int)u[cur].size(); i++)
		   	{
		   		int dest = u[cur][i];

		   		if (res[dest] == -res[cur])
		   		if (!used[dest])
		   			gocur[dest]++;
		   	}

		   	for (i = 0; i < (int)u[cur].size(); i++)
		   	{
		   		int dest = u[cur][i];

		   		if (!used[dest] && res[dest] == -res[cur])
		   		{
		   			if (gomax[dest] == gocur[dest] || res[dest] == -1)
		   			{
		   				q[r++] = dest;

		   				if (res[dest] == -1)
		   				{
                            dp[dest] = dp[cur] + 1;
                            used[dest] = true;
		   				}
		   				else  if (res[dest] == 1)
		   				{
		   					for (j = 0; j < (int)v[dest].size(); j++)
		   					if (res[v[dest][j]] == -1)
		   						dp[dest] = max(dp[dest], dp[v[dest][j]] + 1);
		   					used[dest] = true;
		   				}
		   				else assert(0);
		   			}
		   		}
		   	}
		}

		for (i = 1; i <= n; i++)
			if (res[i] == 1 && dp[i] == -1)
				dp[i] = inf;

	//	cerr<< endl;
		for (i = 1; i <= n; i++)
		  print(i, dp);

		printf("\n");
	}
}