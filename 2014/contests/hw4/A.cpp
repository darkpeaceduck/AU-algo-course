
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
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 10000
#define sz(n) (lo) (n).size()
#define SM 105 * 100
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = 1e9 ;


using namespace std;


int main(){
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
     //freopen("perm.out", "w", stdout);
#else
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w",stdout);
#endif
    lo m;
    cin >> m;
    vector<pair<lo, lo> > segm;
    while(true)
    {
    	lo x, y;
    	scanf("%d%d", &x, &y);
    	if(!x && !y)
    		break;
    	segm.pb(mp(x, y));
    }
    sort(segm.begin(), segm.end());
    lo cur = 0;
    lo maxi = -1;
    vector<lo> ans;
    FOR(i, sz(segm))
    {
    	if(segm[i].first > cur)
    	{
			if(maxi == -1)
			{
				break;
			}
			ans.pb(maxi);
			cur = segm[maxi].second;
			maxi= -1;
			if(cur >= m)
				break;
		}
    	if(segm[i].first > cur)
    		break;
    		if(maxi == -1 || segm[maxi].second < segm[i].second)
    		{
    			maxi = i;
    		}

    }
    if(maxi != -1)
    {
    	ans.pb(maxi);
		cur = segm[maxi].second;
		maxi= -1;
    }
    if(cur < m)
    	cout << "No solution";
    else
    {
    	cout << sz(ans) << endl;
    	FOR(i, sz(ans))
    	{
    		lo id = ans[i];
    		printf("%d %d\n", segm[id].first, segm[id].second);
    	}
    }
}
