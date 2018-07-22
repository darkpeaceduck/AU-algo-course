
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
#define MN 8000000
//#define sz(n) (lo) (n).size()
#define SM 32
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = (1LL<<62) ;

using namespace std;

li mine[MN];
int main()
{
#ifdef MYLOCAL
   freopen("input.txt", "r", stdin);
#else
    freopen("refrigerator.in", "r", stdin);
    freopen("refrigerator.out", "w", stdout);
#endif
    lo t;
    cin >> t;
    FOR(qq, t)
    {
    	lo k;
    	scanf("%d", &k);
    	li q = 1;
    	lo Sz = 0;
    	mine[Sz++] = 1;
    	FOR(i, k)
    	{
    		li a, b;
    		scanf("%I64d%I64d", &a, &b);
//    		cin >> a >> b;
    		lo old = Sz;
    		li cur = 1;
    		FOR(j, b)
    		{
    			cur *= a;
    			FOR(k, old)
					mine[Sz++] = (mine[k] * cur);
    			q *= a;
    		}
    	}


    	li ans = INF;
    	vector<li> outp(3, INF);
    	lo ptr = 0;
    	FOR(i, Sz)
    	{
    		if((db)q / (db)mine[i] >=(db)mine[i])
    			mine[ptr++] = mine[i];
    	}
    	Sz = ptr;
    	sort(mine, mine + Sz);
    	lo fr = 0;
    	for(; fr < Sz && mine[fr] * mine[fr] *mine[fr] <= q; fr++)
    	{

    	}
    	//

    	for(lo i = min(Sz - 1, fr + 70) ; i >= max(0, fr - 70) ; i--)
    	{
    		for(lo j = i; j < Sz && (j - i < 10) ; j++)
    		{

    			li dno = q / (mine[i]) / (mine[j]);

    			if(q == (mine[i]) * (mine[j])* dno)
    			{
    				li with = 2 * ((mine[i]) * (mine[j])
								 + (mine[j]) * dno + dno * (mine[i]));
    				if(ans > with)
    				{
    					ans = with;
    					outp[0] = (mine[i]);
    					outp[1] = (mine[j]);
    					outp[2] = dno;
    				}
    			}
    		}
    	}
    	printf("%I64d ", ans);
    	FOR(i , 3)
    		printf("%I64d ", outp[i]);
    	printf("\n");
    }
}
