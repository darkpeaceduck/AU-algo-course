
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
const li INF = 2e12;


using namespace std;

lo cnt[MN];
lo ans = 0;
void dfs(lo n, lo cur)
{
	if(!n)
	{
		ans++;
		return;
	}
	for(lo i = cur; i <= n; i++)
	{
		for(lo j = 1; j * i <=n ;j++)
		{
			if(cnt[j])
				continue;
			cnt[j]++;
			dfs(n - i * j, i + 1);
			cnt[j]--;
		}
	}
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou	t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("numdiff.in", "r", stdin);
	freopen("numdiff.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	dfs(n, 1);
	cout << ans;
}

