
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
#define li unsigned long long int
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
const li INF = 4294967295ULL;


using namespace std;



int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("ropes.in", "r", stdin);
	freopen("ropes.out", "w",stdout);
#endif
	lo n, k;
	cin >> n >> k;
	vector<lo> g(n);
	lo r = 0;
	FOR(i, n)
	{
		scanf("%d", &g[i]);
		r = max(r, g[i]);
	}
	lo l = 0;
	while(l != r)
	{
		lo cnt = 0;
		lo m = (l + r + 1) / 2;
		FOR(i, n)
		{
			cnt += g[i] / m;
		}
		if(cnt >= k)
			l = m;
		else
			r = m - 1;
	}
	cout << l;
}
