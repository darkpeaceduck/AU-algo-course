
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
//#include <unordered_map>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
*/
//

#define mp make_pair
#define pb push_back
#define lo unsigned int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 1<<24
#define sz(n) (lo) (n).size()
#define SM 32
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = (1LL<<62) ;

using namespace std;

unsigned int cur = 0;
unsigned int ra(unsigned int a,unsigned int b)
{
	cur = cur * a + b;
	return cur >> 8;
}
lo A[MN], sum[MN];
li mod = (1LL<<32);

lo gsum(li a,li b)
{
	return (a + b);
}
int main()
{
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	// freopen("perm.out", "w", stdout);
#else
	freopen("fastadd.in", "r", stdin);
	freopen("fastadd.out", "w",stdout);
#endif
	lo m, q;
	cin >> m >> q;
	lo a, b;
	cin >> a >> b;
	FOR(i, m)
	{
		lo add = ra(a, b);
		lo l = ra(a, b);
		lo r= ra(a, b);
		if(l > r)
			swap(l, r);
		A[l] = gsum(A[l], add);
		A[r + 1] = gsum(A[r + 1] , mod-add);

	}
	lo ans = 0;
	lo now = 0;
	FOR(i, MN)
	{
		now = gsum(now, A[i]);
		sum[i] = gsum(i ? sum[i - 1] : 0, now);
	}
	FOR(i, q)
	{
		lo l = ra(a, b);
		lo r= ra(a, b);
		if(l > r)
			swap(l, r);

		lo val = gsum(sum[r] ,mod- (l ? sum[l - 1] : 0));
		ans = gsum(ans, val);
		//cout << ans << " " << ans2 << endl;
	}
	//cout << ans2 % mod<< endl;
	cout << ans;
}
