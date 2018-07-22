
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
#define MN 300
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>
string name[MN];
vector<lo> g[MN];
lo used[MN], st[MN], have[MN][MN];
int strtoint(string s)
{
	stringstream ss;
	ss << s;
	int res;
	if((ss>>res).fail())
		return -1;
	return res;
}
bool comp(const lo a, const lo b)
{
	return (name[a] < name[b]) || (name[a] == name[b] && a < b);
}


int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("functions.in", "r", stdin);
    freopen("functions.out", "w",stdout);
#endif
    lo n;
    cin >> n;
    string s;
    int cur = -1;
    while(cin >> s)
    {
    	lo val = strtoint(s);
    	if(val ==-1)
    	{
    		cur++;
    		name[cur] = s;
    	}
    	else
    		g[val].pb(cur), st[cur]++;
    }
    vector<lo> start;
    FOR(i, n)
    	start.pb(i);
    sort(all(start), comp);
    FOR(q, n)
    FOR(i, n)
    {
    	lo id = start[i];
    	if(used[id])
    		continue;
    	if(!st[id])
    	{
    		cout << name[id] << endl;
    		FOR(i, sz(g[id]))
    		{
    			lo to = g[id][i];
    			st[to]--;
    		}
    		used[id]++;
    		break;
    	}
    }
}
