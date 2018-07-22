
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
#define DEB(...) fprintf(err,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-3
#define MN 20010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;


using namespace std;

li joseph (li n, li k) {
	if (n == 1)
		return 0;
	if (k == 1)
		return n - 1;
	if (k > n)
		return (joseph (n -1, k) + k) % n;
	li res = joseph (n - n / k, k);
	res -= n % k;
	if (res < 0)
		res += n;
	else
		res += res / (k - 1);
	return res;
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.out", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("psyche.in", "r", stdin);
	freopen("psyche.out", "w",stdout);
#endif
	li n, k;
	cin >> n >> k;
	cout << joseph(n, k) + 1;
}
