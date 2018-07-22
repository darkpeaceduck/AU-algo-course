
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
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-4
#define MN 2000100
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = -1;


using namespace std;

bool bin(vector<lo> &a, vector<lo> &b, db m, lo k, vector<lo> &outp)
{
	outp.clear();
	vector<pair<db, lo> > newo(sz(a));

	FOR(i, sz(a))
	{
		newo[i] = mp(-(db(a[i]) - m *db(b[i])), i);
	}
	nth_element(newo.begin(), newo.begin() + k, newo.end());
	db val = (newo.begin() + k)->first;
	val = -val;
	FOR(i, sz(a))
		newo[i].first = -newo[i].first;
	db sum = 0;
	lo have = k + 1;
	FOR(i, sz(a))
	{
		if(newo[i].first > val)
		{
			sum += newo[i].first;
			outp.pb(newo[i].second);
			have--;
		}
	}
	FOR(i, sz(a))
	{
		if(!have)
			break;
		if(newo[i].first == val)
		{
			sum += newo[i].first;
			outp.pb(newo[i].second);
			have--;
		}
	}
	/*sort(newo.begin(), newo.end());
	db sum = 0;
	FOR(i, k + 1)
	{
		sum += -newo[i].first;
		outp.pb(newo[i].second);
	}
	*/
	if(sum >= 0)
		return true;
	return false;
}
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("kbest.in", "r", stdin);
	freopen("kbest.out", "w",stdout);
#endif
	lo n, k;
	cin >> n >> k;
	k--;
	vector<lo> a(n), b(n), newo(n);
	FOR(i, n)
	{
		lo x, y;
		scanf("%d%d", &x, &y);
		a[i] = x;
		b[i] = y;
	}

	db l = 0, r = 1e7 + 1;
	vector<lo> outp;
	FOR(i, 100)
	{
		db m = (l + r + 1) / 2;
		if(bin(a, b, m, k, outp))
		{
			l = m;
		}
		else
		{
			r = m - 1;
		}
	}
	bin(a, b, l, k, outp);
	FOR(i, sz(outp))
	{
		printf("%d ", outp[i] + 1);
	}
}
