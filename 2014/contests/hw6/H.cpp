
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
#define eps 1e-4
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e9;


using namespace std;

bool func(vector<pair<db, db> > &segm, db P, db L)
{
	db cur = 0;
	db T = 0;
	FOR(i, sz(segm))
	{
		cur += segm[i].first * segm[i].second;
		T += segm[i].first;

		db cur2 = 0;
		db T2 = 0;
		FOR(j, sz(segm))
		{
			if(segm[j].first >= T + P - T2 && T + P - T2 >= 0)
			{
				db f = cur2 + (T + P - T2) * segm[j].second;
				if(f - cur < L)
				{
//					cout << P << " " <<i << " " << j << " " <<0 << endl;
					return false;
				}
			}
			if(T - P >= 0 && segm[j].first >= T - P -T2 && T - P - T2 >= 0)
			{
				db f = cur2 + (T - P - T2) * segm[j].second;
				if(cur - f < L)
				{
//					cout << i << " " << j <<" "<< 1<< endl;
					return false;
				}
			}
			T2 += segm[j].first;
			cur2 += segm[j].first * segm[j].second;
		}
	}
	return true;
}
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("trains.in", "r", stdin);
	freopen("trains.out", "w",stdout);
#endif
	lo L, n;
	cin >> L >> n;
	vector<pair<db, db> > segm(n + 1);
	segm[0] = mp(0, 0);
	FOR(i, n)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		segm[i + 1] = mp(a, b);
	}
	db l = 0, r = INF;
	FOR(i, 50)
	{
		db m = (l + r) / 2;
		if(func(segm, m, L))
			r = m;
		else
			l = m;
	}
	cout << fixed << setprecision(3) << l;
}
