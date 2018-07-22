
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
#define MN 18
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

db sqr(db a)
{
	return a * a;
}

bool eq(db a, db b)
{
	return fabs(a - b) < eps;
}
bool leq(db a, db b)
{
	return b - a > -eps;
}
struct pt
{
	db x, y;
	pt () {}
	pt(db x, db y) : x(x), y(y) {}
	pt operator-(pt other)
	{
		return pt(x - other.x, y - other.y);
	}
	db get_dist()
	{
		return sqrt(sqr(x) + sqr(y));
	}
	pt operator+(pt other)
	{
		return pt(x + other.x, y + other.y);
	}
	db operator*(pt other)
	{
		return x * other.y - y * other.x;
	}
	pt operator*(db other)
	{
		return pt(x * other, y * other);
	}
	db operator%(pt other)
	{
		return x * other.x + y * other.y;
	}
	pt operator/(db a)
	{
		return pt(x / a, y / a);
	}
	void print()
	{
		printf("%lf %lf\n", x, y);
	}
	bool operator==(pt other)
	{
		return eq(x, other.x) && eq(y, other.y);
	}
	bool operator<(const pt &other)const
	{
		return x < other.x;
	}
};
void get_circle(pt ra, pt rb, pt rc, pt &center, db &r)
{
	db a = (rb - rc).get_dist();
	db b = (ra - rc).get_dist();
	db c = (ra - rb).get_dist();
	db S = fabs((ra - rb) * (ra - rc) / 2);
	if(eq(S, 0))
	{
		db maxi = max(a, max(b, c));
		r =  maxi / 2;
		if(maxi == a)
			center = rc + (rb - rc) / 2;
		else if(maxi == b)
			center = rc + (ra - rc) / 2;
		else
			center = rb + (ra - rb) / 2;
		return;
	}
	r = a * b * c / (4 * S);
	db kofa = sqr(a) / (8 * sqr(S));
	db kofb = sqr(b) / (8 * sqr(S));
	db kofc = sqr(c) / (8 * sqr(S));
	db ala = kofa * ((ra - rb) % (ra - rc));
	db alb = kofb * ((rb - ra) % (rb - rc));
	db alc = kofc * ((rc - ra) % (rc - rb));
	center = ra * ala + rb * alb  + rc * alc ;
}

db dp[1<<MN][MN];
pair<pt, lo> fr[1<<MN][MN];
void solve(vector<pt> &good, lo K, lo num_case)
{
	vector<pair<pair<db, pt>, lo> > C;
	lo n = sz(good);
	FOR(i, n) for(int j = i; j < n; j++) for(int k = j; k < n; k++)
	{
		pt center;
		db r;
		lo mask = 0;
		get_circle(good[i], good[j], good[k], center, r);
		FOR(d, n)
		{
			if(leq((center - good[d]).get_dist(), r))
			{
				mask |= (1<<d);
			}
		}
		C.pb(mp(mp(r, center), mask));
	}
	sort(C.begin(), C.end());
	FOR(i, 1<<n) FOR(j, n + 1)
	{
		dp[i][j] = INF;
	}
	dp[0][0] = 0;
	FOR(k, sz(C))
	{
		FOR(j, K)
		{
			FOR(i, (1<<n))
			{
				if(dp[i][j] == INF)
					continue;
	//			cout << i << " " << j << " " << dp[i][j] <<  endl;
					db r = C[k].first.first;
					lo mask = C[k].second;
					db to = max(r, dp[i][j]);
					lo tomask = i | mask;
					if(dp[tomask][j + 1] > to)
					{
						dp[tomask][j + 1] = to;
						fr[tomask][j + 1] = mp(C[k].first.second, i);

					}
			}
		}
		if(dp[(1<<n) - 1 ][K] != INF)
			break;
	}
	lo mask = (1<<n) - 1;
	printf("Case %d: The minimal possible radius is %.10lf\n", num_case, dp[mask][K]);
	for(int i = K; i > 0; i--)
	{
		pt center = fr[mask][i].first;
		mask = fr[mask][i].second;
		printf("  circle %d at (%.10lf, %.10lf)\n", K - i + 1, center.x, center.y);
//		cout << mask << endl;
	}
	printf("\n");
}
int main(){
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w",stdout);
#endif
    for(int cass = 1; ;cass++)
    {
    	lo n, k;
    	cin >> n >> k;
    	if(!n && !k)
    		break;
    	vector<pt> good(n);
    	FOR(i ,n)
    	{
    		cin >> good[i].x >> good[i].y;
    	}
    	solve(good, k, cass);
    }
}


