
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

//#include <unordered_map>
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
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 100010
#define sz(n) (lo) (n).size()
#define SM 13
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = 2e18 + 1;

using namespace std;

vector<lo> pr, nx;
char names[MN][11];
void query(lo id)
{
	printf("%s %s\n",names[pr[id]], names[nx[id]]);
}
void del(lo id)
{
	lo pre = pr[id];
	lo nxe = nx[id];
	pr[nxe] = pre;
	nx[pre] = nxe;
}
int main()
{
#ifdef MYLOCAL
   freopen("input.txt", "r", stdin);
#else
    freopen("meeting.in", "r", stdin);
    freopen("meeting.out", "w", stdout);
#endif
    lo n;
    cin >> n;
    nx.resize(n);
    pr.resize(n);
    scanf("\n");
    FOR(i, n)
    {
    	scanf("%s", &names[i]);
    }
    FOR(i, n)
    {
    	pr[i] = (i - 1 + n) % n;
    	nx[i] = (i + 1) % n;
    }
    FOR(i, n - 3)
    {
    	lo cur;
    	scanf("%d", &cur);
    	cur--;
    	query(cur);
    	del(cur);
    }
}

