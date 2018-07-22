
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
#define eps 1e-3
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e9;


using namespace std;

db func(vector<db> kof, db x)
{
	db cur = 1;
	reverse(kof.begin(), kof.end());
	db ans = 0;
	FOR(i, sz(kof))
	{
		ans += kof[i] * cur;
		cur *= x;
	}
	return fabs(ans);
}
vector<db> getit(vector<db> kof)
{
	if(sz(kof) == 1)
		return vector<db>{0};
	vector<db> dkof;
	FOR(i, sz(kof) - 1)
	{
		dkof.pb(kof[i] * (sz(kof) - i));
	}
	vector<db> x = getit(dkof);
	x.insert(x.begin(), -INF);
	x.pb(INF);
	vector<db> ans;
	FOR(i, sz(x) - 1)
	{
		db l = x[i];
		db r = x[i + 1];
		FOR(i, 1000)
		{
			db a = (2 * l + r) / 3;
			db b = (l + r * 2) / 3;
			if(func(kof, a) <= func(kof, b))
			{
				r = b;
			}
			else
			{
				l = a;
			}
		}
		if(func(kof, l) < eps)
			ans.pb(l);
	}
	return ans;
}

int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("cubroot.in", "r", stdin);
	freopen("cubroot.out", "w",stdout);
#endif
	db a, b, c, d;
	cin >> a >> b >> c >> d;
	vector<db> kof = {a, b, c, d};
	vector<db> ans = getit(kof);
	if(ans.empty())
		cout << 0;
	else
		cout << fixed << setprecision(10) << ans[0];
}
