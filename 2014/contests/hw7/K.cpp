
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
#define MN 310
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;


using namespace std;

lo last[MN][SM], nex[MN][SM];
lo fr[MN][SM];
lo x[MN];
void re(lo a, lo b)
{
	if(b > 1)
	{
		re(fr[a][b], b - 1);
	}
	cout << x[a] << " ";
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.out", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("post.in", "r", stdin);
	freopen("post.out", "w",stdout);
#endif
	FOR(i, MN) FOR(k, SM)
	{
		last[i][k] = INF;
		fr[i][k] = -1;
	}
	//
	lo n,m ;
	cin >> n >> m;
	FOR(i, n)
	{
		cin >> x[i];
	}
	sort(x, x + n);
	last[0][1] = last[0][0] = 0;
	for(lo i = 1; i < n; i++)
	{
		FOR(j, MN) FOR(k, SM)
		{
			nex[j][k] = INF;
		}
		FOR(j, i) FOR(k, m + 1)
		{
			nex[j][k] = last[j][k];
			nex[j][k] = last[j][k];
			if(k && nex[j][k] != INF)
				nex[j][k] += x[i] - x[j];
		}
		FOR(j, i) FOR(k, m + 1)
		{
			lo val = nex[j][k];
			FOR(d, i + 1)
			{
				if(!k)
					val += x[i] - x[d];
				else if(x[i] - x[d] < abs(x[d] - x[j]))
				{
					val -= abs(x[d] - x[j]);
					val += x[i] - x[d];
				}
			}
			if(nex[i][k + 1] > val)
			{
				nex[i][k + 1] = val;
				fr[i][k + 1] = j;
			}
		}
		memcpy(last, nex, sizeof last);
	}
	lo in = 0;
	FOR(i, n)
	{
		if(nex[in][m] > nex[i][m])
			in = i;
	}
	cout << nex[in][m]  << endl;
	re(in, m);
}
