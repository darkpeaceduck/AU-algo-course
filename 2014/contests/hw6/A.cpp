
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
	freopen("sqrt.in", "r", stdin);
	freopen("sqrt.out", "w",stdout);
#endif
	li a;
	while(cin >> a)
	{
		li l = 0, r = INF;
		while(l != r)
		{
			li m = (l + r + 1) / 2;
			if(m * m > a)
				r = m - 1;
			else
				l = m;
		}
		cout << max(0ULL, l) << endl;
	}
}
