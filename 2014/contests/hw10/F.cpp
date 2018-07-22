
///#pragma comment(linker, "/STACK:100000000000000")
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
//#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 100100
#define sz(n) (lo) (n).size()
#define SM 1010
const li INF = 2e9;

using namespace std;

char ma[SM][SM];
lo used[SM][SM];
lo n, m;
lo resx, resy;
bool cor(lo x, lo y)
{
	return x >= 0 && y >= 0 && x < n && y < m;
}
pair<lo, lo>  go[4] = {mp(0, 1), mp(0, -1), mp(1, 0), mp(-1, 0)};
bool dfs(lo x, lo y, vector<pair<lo, lo> > &outp)
{
	if(x == resx && y == resy)
	{
		outp.pb(mp(x, y));
		return true;
	}
	used[x][y]++;
	FOR(i, 4)
	{
		lo tox = x + go[i].first;
		lo toy = y + go[i].second;
		if(cor(tox, toy) && !used[tox][toy] && ma[tox][toy] == '.')
		{
			if(dfs(tox, toy, outp))
			{
				outp.pb(mp(x, y));
				return true;
			}
		}
	}
	return false;
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("dfsongrid.in", "r", stdin);
    freopen("dfsongrid.out", "w",stdout);
#endif
    cin >> n >> m;
    swap(n, m);
    lo sx, sy;
    cin >> sx >> sy >> resx >> resy;
    sx--;
    sy--;
    resx--;
    resy--;
    swap(sx, sy);
    swap(resx, resy);
    FOR(i, n) FOR(j, m)
    		cin >> ma[i][j];
    vector<pair<lo, lo> > outp;
    if(dfs(sx, sy, outp))
    {
    	reverse(outp.begin(), outp.end());
    	cout << "YES" << endl;
    	FOR(i, sz(outp))
    	{
    		swap(outp[i].first, outp[i].second);
    		printf("%d %d ", outp[i].first + 1, outp[i].second + 1);
    	}
    }else{
    	cout << "NO";
    }

}
