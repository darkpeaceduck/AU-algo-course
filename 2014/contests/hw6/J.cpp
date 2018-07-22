
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
const li INF = 2e9;


using namespace std;


int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("cows.in", "r", stdin);
	freopen("cows.out", "w",stdout);
#endif
	lo n, k;
	cin >> n >> k;
	vector<lo> x(n);
	FOR(i, n)
	{
		scanf("%d", &x[i]);
	}
	li l = 0, r = INF;
	while(l != r)
	{
		li m = (l + r + 1) / 2;
		li at = -INF;
		lo can = k;
		FOR(i, n)
		{
			if(x[i] - at >= m)
			{
				if(can)
				{
					can--;
					at=  x[i];
				}
			}
		}
		if(!can)
			l = m;
		else
			r = m-  1;
	}
	cout << l;
}
