
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

vector<pair<lo, lo> > g[MN];
lo off_edge[MN], ptr = 0;
void gen(lo n, lo res, lo osn, lo base)
{
	FOR(i, base)
	{
		lo numb = res + osn * i;
		if(n == 1){
			numb /= base;
//			if(res != numb)
//			{
				if(!res && !numb)
					continue;
//				cout << res << " " << numb << endl;
				g[res].pb(mp(numb, i));
//			}
		}
		else
		{
			gen(n - 1, numb, osn * base, base);
		}
	}
}

void print(lo numb, lo need, lo base)
{
	for(int i = 0; i < need; i++)
	{
		cout << numb % base;
		numb /= base;
	}
}

void eyler(lo id, lo val, vector<lo> &in)
{
//	cout << " id << "<< id << endl;
	while(!g[id].empty())
	{
		lo to = g[id][0].first;
		lo val = g[id][0].second;
		swap(g[id][0], g[id][sz(g[id]) - 1]);
		g[id].pop_back();
		eyler(to, val, in);
	}
	if(val != -1)
		in.pb(val);
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("codelock.in", "r", stdin);
    freopen("codelock.out", "w",stdout);
#endif
    lo n, k;
    cin >> n >> k;
    if(k == 1)
    {
    	FOR(i, n)
    			cout<<i;
    	return 0;
    }
    gen(k, 0, 1, n);

    FOR(i, k)
    	cout << 0;
    vector<lo> in;
    eyler(0, -1, in);
    reverse(in.begin(), in.end());
    FOR(i, sz(in))
    	printf("%d", in[i]);
}


