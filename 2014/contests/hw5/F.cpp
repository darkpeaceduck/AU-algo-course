
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
const li INF = 100100100;


using namespace std;


int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("watches.in", "r", stdin);
	freopen("watches.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	scanf("\n");
	vector<lo> good;
	FOR(i, n)
	{
		lo a, b, c;
		scanf("%d:%d:%d\n", &a, &b, &c);
		good.pb(c + b * 60 + 60 * 60 * a);
	}
	sort(good.begin(), good.end());
	li ans = 0;
	lo maxi = 12 * 60 * 60;

	for(lo i = 1; i < n; i++)
	{
		ans += maxi - good[i] + good[0];
	}
	lo with = good[0];
	lo now = ans;
	for(lo i = 1; i < n; i++)
	{
		now += (good[i] - good[i-  1]) * n;
		now -= maxi;
		if(now < ans)
		{
			ans = now;
			with = good[i];
		}
	}
	printf("%d:%02d:%02d", with / 3600, (with % 3600) / 60, (with %60));
}
