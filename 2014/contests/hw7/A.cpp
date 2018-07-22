
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
#define MN 100100
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e9;


using namespace std;

queue<lo> g;
lo g2[MN];
lo ans[MN];
lo in[MN];
lo ty[MN];
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	memset(ans, -1, sizeof ans);
	vector<lo> outp;
	FOR(i, n)
	{
		lo a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if(a == 1)
		{
			g2[c]++;
		}
		else
		{
			outp.pb(i);
			g.push(i);
			ty[i] = c;	
			in[i] = b;
		}
		while(!g.empty() && g2[ty[g.front()]])
		{
			lo temp = ty[g.front()];
			g2[temp]--;
			ans[g.front()] = b - in[g.front()];
			g.pop();
		}
	}

	FOR(i, sz(outp))
	{
		printf("%d ", ans[outp[i]]);
	}
}
