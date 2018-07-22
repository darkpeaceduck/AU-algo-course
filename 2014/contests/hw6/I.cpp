
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
#define eps 1e-7
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e15;


using namespace std;

db aS = sqrt(2.0) / 2.0;
void rot(db &x, db &y, db f)
{
	db X = aS * (x + (-1 * f) * y);
	db Y = aS * (f * x + y);
	x = X;
	y = Y;
}
bool prov(vector<pair<db, db> > &ko, db m, db &Ax, db &Ay)
{
	db Lx = ko[0].first - m;
	db Rx = ko[0].first + m;
	db Ly = ko[0].second - m;
	db Ry = ko[0].second + m;
	FOR(i, sz(ko))
	{
		Lx = max(Lx, ko[i].first - m);
		Rx = min(Rx, ko[i].first + m);
		Ly = max(Ly, ko[i].second - m);
		Ry = min(Ry, ko[i].second + m);
	}
	if(Lx > Rx || Ly > Ry)
		return false;
	Ax = Lx;
	Ay = Ly;
	return true;
}
li func(vector<pair<lo, lo> > &a, lo x, lo y)
{
	li ans = 0;
	FOR(i, sz(a))
	{
		ans = max(ans, abs(a[i].first -x) + 0LL + abs(a[i].second - y));
	}
	return ans;
}
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("cucarach.in", "r", stdin);
	freopen("cucarach.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	vector<pair<db, db> > ko(n);
	vector<pair<lo, lo> > old(n);
	FOR(i, n)
	{
		db x, y;
		scanf("%lf%lf", &x, &y);
		old[i] = mp(x, y);
		rot(x, y, 1);
		ko[i] = mp(x, y);

	}
	li l = 0, r = INF;
	db ax = 0, ay = 0;
	while(l != r)
	{
		db m = (l + r ) / 2;
		if(prov(ko, m * (aS + eps), ax, ay))
			r = m ;
		else
			l = m + 1;
	}
	prov(ko, l * (aS + eps), ax, ay);
	rot(ax, ay, -1);
	lo oux = int(ax) ;
	lo ouy = int(ay);
	li curans = func(old, oux, ouy);
	for(lo i = oux - 5; i <= oux + 5; i++)
	{
		for(lo j = ouy - 5; j <= ouy + 5; j++)
		{
			li with = func(old, i, j);
			if(with < curans)
			{
				curans = with;
				oux = i;
				ouy = j;
			}
		}
	}
	cout << oux << " " << ouy;
}
