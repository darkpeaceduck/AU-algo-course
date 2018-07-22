
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
	freopen("find3.in", "r", stdin);
	freopen("find3.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	vector<lo> a(n);
	FOR(i, n)
	{
		scanf("%d", &a[i]);
	}
	sort(a.begin(), a.end());
	lo k;
	cin >> k;
	FOR(q, k)
	{
		lo L, R;
		scanf("%d%d", &L, &R);
		lo l = upper_bound(a.begin(), a.end(), L - 1) - a.begin();
		lo r = upper_bound(a.begin(), a.end(), R) - a.begin() - 1;
		printf("%d ", max(r - l + 1, 0));
	}
}
