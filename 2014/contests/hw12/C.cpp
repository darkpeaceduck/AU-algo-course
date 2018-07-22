
//#pragma comment(linker, "/STACK:100000000000000")
#include <stdio.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <queue>
//#include <unordered_set>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <functional>
*/
//

#define mp make_pair
#define pb push_back
#define lo  int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 12
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>

lo dp[SM][SM][SM][SM];
pair<pair<lo, lo>, pair<lo, lo> > fr[SM][SM][SM][SM];

pair<lo, lo> go[8] = {mp(2, -1), mp(2, 1), mp(-2, 1), mp(-2, -1),
					  mp(1, 2), mp(1, -2), mp(-1, 2), mp(-1, -2) };

queue<pair<pair<lo, lo>, pair<lo, lo> > > q;
bool cor(lo x)
{
	return x >=0 && x < 8;
}
void add(lo x, lo y, lo x2, lo y2, lo fx, lo fy, lo fx2, lo fy2)
{
	lo val = dp[fx][fy][fx2][fy2] + 1;
	if(cor(x) && cor(y) && cor(x2) && cor(y2) && !(x == x2 && y == y2))
	{
		if(dp[x][y][x2][y2] > val)
		{
			dp[x][y][x2][y2] = val;
			fr[x][y][x2][y2] = mp(mp(fx, fy), mp (fx2, fy2));
			q.push(mp(mp(x, y), mp(x2, y2)));
		}
	}
}
void bfs(lo x, lo y, lo x2, lo y2)
{
	FOR(i, SM) FOR(j, SM) FOR(k, SM) FOR(d, SM)
			dp[i][j][k][d] = INF,
			fr[i][j][k][d] = mp(mp(-1, -1), mp(-1, -1));
	q.push(mp(mp(x, y), mp(x2, y2)));
	dp[x][y][x2][y2] = 0;
	while(!q.empty())
	{
		x = q.front().first.first;
		y = q.front().first.second;
		x2 = q.front().second.first;
		y2 = q.front().second.second;
		q.pop();
		FOR(i, 8)
		{
			lo tox = x + go[i].first;
			lo toy = y + go[i].second;
			lo tox2 = x2 + go[i].first;
			lo toy2 = y2 + go[i].second;
			add(tox,toy,x2,y2,x,y,x2,y2);
			add(x, y, tox2,toy2,x,y,x2,y2);
		}
	}
}

void print(lo x, lo y)
{
	printf("%c%d\n", (char)(x + 'a'), y + 1);
}

void scan(lo &x, lo &y)
{
	char c;
	cin >> c >> y;
	x = c - 'a';
	y--;
}
void re(lo x, lo y, lo x2, lo y2)
{
	lo tox = fr[x][y][x2][y2].first.first;
	lo toy = fr[x][y][x2][y2].first.second;
	lo tox2 = fr[x][y][x2][y2].second.first;
	lo toy2 = fr[x][y][x2][y2].second.second;
	if(tox != -1)
	{
		re(tox, toy, tox2, toy2);
		if(x == tox && y == toy)
			printf("2 "), print(x2, y2);
		else
			printf("1 "), print(x, y);
	}
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("knight2.in", "r", stdin);
    freopen("knight2.out", "w",stdout);
#endif
    lo x, y, x2, y2,
       tox, toy, tox2, toy2;
    scan(x, y);
    scan(x2, y2);
    scan(tox, toy);
    scan(tox2, toy2);
    bfs(x, y, x2, y2);
    re(tox, toy, tox2, toy2);
}

