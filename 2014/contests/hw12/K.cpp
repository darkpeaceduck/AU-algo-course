
//#pragma comment(linker, "/STACK:100000000000000")
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <bitset>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cctype>
#include <fstream>
#include <cassert>


#include <ctime>
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
#define lo int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 510
#define sz(n) (lo) (n).size()
#define SM 12
const lo INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>

pair<lo, lo> d[MN][MN];
char ma[MN][MN];
lo used[MN][MN][2];

int main()
{
#ifdef MYLOCAL
//     freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
//    freopen("customs.in", "r", stdin);
//    freopen("customs.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    lo A, B, C, D;
    cin >> A >> B >> C >> D;
    A--;
    B--;
    C--;
    D--;
    scanf("\n");
    FOR(i, n)
    {
    	scanf("%s", &ma[i]);
    	FOR(j, m)
    	{
    		d[i][j] = mp(INF, INF);
    	}
    }
    d[A][B] = mp(0, 0);
    queue<pair<lo, lo> > q;
    q.push(mp(A, B));
    used[A][B][0] = used[A][B][1] = 1;
    pair<lo, lo> go[8] = {mp(0, 1), mp(0, -1), mp(1, 0), mp(-1, 0),
                          mp(1, 1), mp(1, -1), mp(-1, 1), mp(-1, -1)};
    vector<pair<lo, lo> > nex;
    bool yep = false;
    while(!q.empty() || !nex.empty())
    {
    	if(q.empty())
    	{
    			if(yep)
				{
					cout << d[C][D].second + 1 << " " << d[C][D].first << endl;
					return 0;
				}
    		FOR(i, sz(nex))
			{
    			if(!used[nex[i].first][nex[i].second][0])
    				q.push(nex[i]);
			}
    		nex.clear();
    	}
    	lo x = q.front().first;
    	lo y = q.front().second;
    	if(x == C && y == D)
    		yep = true;
//    	cout << x << " " << y << " " << d[x][y].first << " " << d[x][y].second << endl;
    	q.pop();
    	FOR(i, 8)
    	{
    		lo tox = x + go[i].first;
    		lo toy = y + go[i].second;
    		if(tox >= 0 && tox < n && toy >= 0 && toy < m && ma[tox][toy] != '0')
    		{
    			if(ma[x][y] != ma[tox][toy])
    			{

    				pair<lo, lo> with = mp(d[x][y].first + 1, d[x][y].second + 1);
    				if(!used[tox][toy][0] && d[tox][toy] > with)
    				{
    					used[tox][toy][1]++;
    					d[tox][toy] = with;
    					nex.pb(mp(tox, toy));
    				}
    			}
    			else
    			{
    				pair<lo, lo> with = mp(d[x][y].first , d[x][y].second + 1);
    				if(d[tox][toy] > with)
    				{
    					used[tox][toy][0]++;
    					d[tox][toy] = with;
    					q.push(mp(tox, toy));
    				}
    			}
    		}
    	}
    }
    if(d[C][D] == mp(INF, INF))
    	cout << "0 0";
    else
    	cout << d[C][D].second + 1 << " " << d[C][D].first << endl;
}

