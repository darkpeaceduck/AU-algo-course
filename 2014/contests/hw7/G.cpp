
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
#define MN 20010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;


using namespace std;

char a[MN], b[MN];
int main(){
#ifdef MYLOCAL
	 //freopen("perm.out", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("patterns.in", "r", stdin);
	freopen("patterns.out", "w",stdout);
#endif
	scanf("%s%s", &a, &b);
	lo n = strlen(a);
	lo m = strlen(b);
	bool have = false;
	lo ptr = 0;
	vector<string> v;
	FOR(i, n)
	{
		if(a[i] == '*')
		{
			if(v.empty() || v.back() != "*")
				v.pb("*");
		}
		else
		{
			v.pb(string());
			for(; i < n && a[i] != '*'; i++)
			{
				v.back() += a[i];
			}
			i--;
		}
	}
	FOR(i, sz(v))
	{
		if(v[i] != "*")
		{
			bool yep = false;
			if(i == sz(v) - 1)
			{
				ptr = max(ptr, m - sz(v[i]));
			}
			while(ptr + sz(v[i]) - 1 < m)
			{
				yep = true;
				FOR(j, sz(v[i]))
				{
					if(v[i][j] != b[ptr + j] && v[i][j] != '?')
					{
						yep = false;
						break;
					}
				}
				if(yep)
					break;
				ptr++;
			}
			if(!i && ptr)
			{
				cout << "NO";
				return 0;
			}
			if(!yep)
			{
				cout << "NO";
				return 0;
			}
			ptr +=sz(v[i]);
		}
	}
	cout << "YES";
}
