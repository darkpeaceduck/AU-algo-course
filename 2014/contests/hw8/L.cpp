
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
//#define eps 1e-3
#define MN 5010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;


using namespace std;

lo **check;
inline lo sum(li a, li b)
{
    return (a + b) % 1000000007;
}
lo dfs(lo n, lo k)
{
    if(n == k)
        return 1;
    if(k == 1)
        return 1;
    if(k > n)
        return 0;
    if(check[n][k] != -1)
        return check[n][k];
    return check[n][k] = sum(dfs(n - 1, k - 1) ,dfs(n - k , k));
}
int main(){
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("summand.in", "r", stdin);
    freopen("summand.out", "w",stdout);
#endif
    lo n, k;
    cin >> n >> k;
    lo temp = n - k * 1LL *(k + 1) / 2;
    if(temp < 0)
    {
        cout << 0;
        return 0;
    }
    check = new int *[temp + 1];
	FOR(i, temp + 1)
	{
		check[i] = new int[k + 1];
		FOR(j, k + 1)
			check[i][j] = -1;
	}
    lo outp = 0;
    for(int i = 1; i <= k; i++)
    {
        outp = sum(outp, dfs(temp, i));
    }
    cout << outp << endl;
}
