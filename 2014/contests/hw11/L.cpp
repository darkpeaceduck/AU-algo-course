
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
#define MN 2010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e18;

using namespace std;

//#include <memory>
//#include <pthread.h>
li L[MN], T[MN];
li add[MN][MN], dp[MN][MN];
lo position[MN][MN],p[MN][MN];

void make_ans(lo a, lo b)
{
	if(b)
	{
		make_ans(p[a][b], b - 1);
	}
	printf("%d ", position[p[a][b] + (b > 0)][a] + 1);
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("server.in", "r", stdin);
    freopen("server.out", "w",stdout);
#endif
    lo n, K;
    cin >> n >> K;
    cin >> T[0];
    for(int i = 1; i < n; i++)
    {
    	scanf("%I64d%I64d", &L[i], &T[i]);
    }
    FOR(i, n)
    {
    	li lenL = 0, ansL = 0, kofL = 0,
    			lenR = 0,
    			kofR = 0,
    			ansR = 0;
    	lo pos = i;
    	add[i][i] = 0;
    	position[i][i] = pos;
    	for(lo j = i + 1; j < n; j++)
    	{
    		li edge = L[j];
    		lenR += edge;
    		ansR += lenR * T[j];
    		kofR += T[j];
    		while(pos + 1 < n)
    		{
    			li nex = (ansL + L[pos + 1] * (kofL + T[pos])) + (ansR - L[pos + 1] * kofR);
    			if(nex <= ansL + ansR)
    			{
    				kofL += T[pos];
    				ansL += L[pos + 1] * kofL;
    				lenL += L[pos + 1];

    				ansR -= L[pos + 1] * kofR;
    				lenR -= L[pos + 1];
    				kofR -= T[pos + 1];
    				pos++;
    			}
    			else
    				break;
    		}
    		add[i][j] = ansL + ansR;
    		position[i][j] = pos;
    	}
    }
    FOR(i, n)
    {
    	dp[i][0] = add[0][i];
    }
    for(lo k = 1; k < K; k++)
    {
    	p[n][k] = n;
    	for(lo i = n - 1; i >= 0; i--)
    	{
    		lo l = p[i][k - 1];
    		lo r = min(i - 1, p[i + 1][k]);
    		dp[i][k] = INF;
    		for(int j = l; j <= r; j++)
    		{
    			li with = dp[j][k - 1] + add[j + 1][i];
    			if(with < dp[i][k])
    			{
    				dp[i][k] = with;
    				p[i][k] = j;
    			}
    		}
    	}
    }
    cout << dp[n - 1][K - 1] << endl;
    make_ans(n - 1, K - 1);
}


