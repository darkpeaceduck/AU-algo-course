
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
const li INF = 1e15;


using namespace std;

unsigned int cur = 0, a, b;
unsigned int ra24()
{
	cur = cur * a + b;
	return cur >> 8;
}
unsigned int ra32()
{
	unsigned int A = ra24(), B = ra24();
	return (A << 8) ^ B;
}
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("postman.in", "r", stdin);
	freopen("postman.out", "w",stdout);
#endif
	lo n;
	cin >> n >> a >> b;
	vector<unsigned int> X(n);
	FOR(i, n)
	{
		X[i] = ra32();
	}
	sort(X.begin(), X.end());
	li res = 0;
	FOR(i, n)
	{
		res += abs(1LL * (X[i]) - 1LL * X[n / 2]);
	}
	cout << res;
}
