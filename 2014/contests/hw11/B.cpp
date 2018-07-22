
#pragma comment(linker, "/STACK:100000000000000")
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
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 100100
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

#include <memory>

vector<lo> g[MN];
lo h[MN];
lo maxi = -1;
vector<lo> num;
void dfs(lo id, lo p){
	if(h[id] > maxi){
		maxi = h[id];
		num.clear();
	}
	if(h[id] == maxi)
	{
		num.pb(id);
	}
	FOR(i, sz(g[id])){
		lo to = g[id][i];
		if(to == p)
			continue;
		h[to] = h[id] + 1;
		dfs(to, id);
	}
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("rootdist.in", "r", stdin);
    freopen("rootdist.out", "w",stdout);
#endif
    lo n;
    cin >> n;
    FOR(i, n - 1)
    {
    	lo a;
    	cin >> a;
    	a--;
    	g[a].pb(i + 1);
    }
    dfs(0, -1);
    cout << maxi << endl << sz(num) << endl;
    sort(all(num));
    FOR(i, sz(num))
    	cout << num[i] + 1<< " ";
}
