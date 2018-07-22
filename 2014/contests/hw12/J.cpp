
//#pragma comment(linker, "/STACK:100000000000000")
#include <stdio.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
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
#define lo  int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 12
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>
vector<pair<lo, lo> > g[MN][SM];
lo used[MN], dest[MN];
lo minedge[MN];
lo ans = INF;
		lo it = 0;
void dfs(lo id, lo fr, lo edge_fr)
{
	if(dest[id] + minedge[id] > ans)
		return;
	used[id]++;
	FOR(j, SM)
	{
		FOR(i, sz(g[id][j]))
		{
			it++;
			if(it > 6000000)
				return;
			lo edge = g[id][j][i].second;
			if(edge_fr == edge)
				continue;
			lo to = g[id][j][i].first;
			if(to == fr)
				ans = min(ans, dest[id] + j);
			if(!used[to])
			{
				dest[to] = dest[id] + j;
				dfs(to, fr, edge);
			}
		}
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
    freopen("excurs.in", "r", stdin);
    freopen("excurs.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    FOR(i, n)
    	minedge[i] = INF;
    FOR(i, m)
    {
    	lo a, b, c;
    	a = readInt();
    	b = readInt();
    	c = readInt();
    	a--;
    	b--;
    	minedge[a] = min(minedge[a], c);
    	minedge[b] = min(minedge[b], c);
    	g[a][c].pb(mp(b, i));
    	g[b][c].pb(mp(a, i));
    }
    FOR(i, n )
    {
    	FOR(j, n)
		{
    		dest[j] = INF;
    		used[j]=0;
		}
    	dest[i] = 0;
    	dfs(i, i, -1);
    }
    cout << ans;
}

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


