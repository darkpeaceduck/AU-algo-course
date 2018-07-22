
#pragma comment(linker, "/STACK:100000000000000")
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

vector<pair<lo, lo> > g[MN];
li dn[MN], num[MN], ans[MN];
void count_dn(lo id, lo p)
{
	dn[id] = 0;
	num[id] = 1;
	FOR(i, sz(g[id])){
		lo to = g[id][i].first;
		if(to == p)
			continue;
		count_dn(to, id);
		dn[id] += dn[to] + num[to];
		num[id] += num[to];
	}
}
void dfs(lo id, lo p, lo edge_id, li up, lo upnum)
{
	if(edge_id != -1)
	{
		ans[edge_id] = dn[id] * upnum + num[id] * up + num[id] * upnum;
	}
	FOR(i, sz(g[id])){
		lo to = g[id][i].first;
		if(to == p)
			continue;
		dfs(to, id, g[id][i].second, up + dn[id] - (dn[to] + num[to]) + upnum, upnum + num[id] - num[to]);
	}
}


inline int readInt();
inline int readUInt();
inline void readWord( char *s );
inline int fast_readchar(); // you may use readchar() instead of it

inline void writeInt( int x );
inline void fast_writechar( int x ); // you may use putchar() instead of it
inline void writeWord( const char *s );
inline void fast_flush();


int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("treedp.in", "r", stdin);
    freopen("treedp.out", "w",stdout);
#endif
    lo n;
    cin >> n;
    FOR(i, n - 1)
    {
    	lo a, b;
    	a = readInt();
    	b = readInt();
    	a--;
    	b--;
    	g[a].pb(mp(b, i));
    	g[b].pb(mp(a, i));
    }
	count_dn(0, -1);
	dfs(0, -1, -1, 0, 0);
    FOR(i, n - 1)
    {
    	printf("%I64d\n", ans[i]);
    }
}

/** Read */

static const int buf_size = 4096;

inline int fast_readchar() {
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len)
    pos = 0, len = fread(buf, 1, buf_size, stdin);
  if (pos == len)
    return -1;
  return buf[pos++];
}

inline int readUInt() {
  int c = fast_readchar(), x = 0;
  while (c <= 32)
    c = fast_readchar();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = fast_readchar();
  return x;
}

inline int readInt() {
  int s = 1, c = fast_readchar();
  int x = 0;
  while (c <= 32)
    c = fast_readchar();
  if (c == '-')
    s = -1, c = fast_readchar();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = fast_readchar();
  return x * s;
}

inline void readWord( char *s ) {
  int c = fast_readchar();
  while (c <= 32)
    c = fast_readchar();
  while (c > 32)
    *s++ = c, c = fast_readchar();
  *s = 0;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void fast_writechar( int x ) {
  if (write_pos == buf_size)
    fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
  write_buf[write_pos++] = x;
}

inline void fast_flush() {
  if (write_pos)
    fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
}

inline void writeInt( int x ) {
  if (x < 0)
    fast_writechar('-'), x = -x;

  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    fast_writechar(s[n]);
}

inline void writeWord( const char *s ) {
  while (*s)
    fast_writechar(*s++);
}
