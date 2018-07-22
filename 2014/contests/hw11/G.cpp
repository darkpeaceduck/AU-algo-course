
//#pragma comment(linker, "/STACK:100000000000000")
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
#include <functional>
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
#define eps 1e-7
#define MN 3000100
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>

int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("newphone.in", "r", stdin);
    freopen("newphone.out", "w",stdout);
#endif
    lo n, k;
    cin >> n >> k;
    lo log_2 = log2(n) + 2;
    k = min(k, log_2);
    vector<lo> f(n + 1, INF);
    f[0] =  0;
    for(int i = 1; i <= k; i++)
    {
    	lo pos = 1;
    	vector<lo> newf(n + 1, 0);
    	for(lo j = 1; j <= n; j++)
    	{
    		while(f[pos - 1] < newf[j - pos])
    			pos++;
    		newf[j] = 1 + max(f[pos - 1], newf[j - pos]);
    		if(pos > 1)
    			newf[j] = min(newf[j], 1 + max(f[pos - 2], newf[j - (pos - 1)]));
//    		cout <<	 newf[j] << " " << endl;
    	}
    	f = newf;
    }
    if(f[n - 1] == INF)
    	cout << -1;
    else
    	cout << f[n - 1];
}


