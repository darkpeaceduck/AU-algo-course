
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
#define MN 100100
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e9;


using namespace std;

map<li, unsigned lo> f;
unsigned lo func(li a)
{
	if(a <=2)
		return 1;
	if(f.count(a))
		return f[a];
	unsigned int res = 0;
	if(a % 2 == 0)
	{
		res = func(a - 1) + func(a - 3);
	}
	else
	{
		res = func(6 * a / 7) + func(2 * a / 3);
	}
	return f[a] = res;
}
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("function.in", "r", stdin);
	freopen("function.out", "w",stdout);
#endif
	li n;
	cin >> n;
	cout << func(n);
}
