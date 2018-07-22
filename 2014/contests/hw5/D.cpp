
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


int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w",stdout);
#endif
	lo n, k;
	cin >> n >> k;
	vector<lo> cnt(k);
	lo m;
	cin >> m;
	vector<pair<lo, pair<lo, pair<lo, lo> > > > segm;
	FOR(i, m)
	{
		lo a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a--;
		b--;
		c--;
		segm.pb(mp(b, mp(1, mp(i, a))));
		segm.pb(mp(c+1, mp(0, mp(i, a))));
	}

	sort(segm.begin(), segm.end());
	set<pair<lo, lo> > good;
	lo last = segm[0].first;
	FOR(i, sz(segm))
	{
		lo x = segm[i].first;
		lo is = segm[i].second.first;
		lo color = segm[i].second.second.second;
		lo t = segm[i].second.second.first;
		if(!good.empty())
		{
			cnt[(--good.end())->second] += x - last;
		}
		last = x;
		if(is)
		{
			good.insert(mp(t, color));
		}
		else
		{
			if(good.count(mp(t, color)))
				good.erase(good.find(mp(t, color)));
		}
	}
	FOR(i, k)
	{
		printf("%d ", cnt[i]);
	}

}
