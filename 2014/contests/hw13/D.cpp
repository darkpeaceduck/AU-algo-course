
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
#define MN 300100
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>
lo p[MN], with[MN];

lo find(lo a)
{
	if(a == -1)
		return -1;
	return p[a] == a ? a : p[a] = find(p[a]);
}

lo unite_ok(lo a, lo b)
{
	a = find(a);
	b = find(b);
	if(a == -1 || b == -1)
	{
		return a == -1 ? b : a;
	}
	p[a] = b;
	return b;
}
bool unite(lo a, lo b)
{
	a  = find(a);
	b = find(b);
	lo witha = find(with[a]);
	lo withb = find(with[b]);
	if(a == b)
		return false;
	lo v1 = unite_ok(a, withb);
	lo v2 = unite_ok(b, witha);
	if(min(v1, v2) == -2)
		return false;
	with[v1] = v2;
	with[v2] = v1;
	return true;
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
//    freopen("cutting.in", "r", stdin);
//    freopen("cutting.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    FOR(i, n)
    {
    	with[i] = -1;
    	p[i] = i;
    }

    bool yep = true;
    FOR(i, m)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	if(yep)
    	{
    		yep= unite(a, b);
    	}
    	printf(yep ? "1" : "0");
    }
}
