
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
#define MN 1010
#define sz(n) (lo) (n).size()
#define SM 105 * 100
const li INF = 2e9 ;


using namespace std;

inline int readInt();
inline int readUInt();
inline void readWord( char *s );
inline int fast_readchar();

inline void writeInt( int x );
inline void fast_writechar( int x );
inline void writeWord( const char *s );
inline void fast_flush();

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

struct Que
{
	struct stack_min
	{
        pair<lo, lo> * v;
        lo ptr;
		stack_min() : ptr(0) {v = new pair<lo, lo>[MN];}
		void push(lo el)
		{
			pair<lo, lo> ins = (!ptr ? mp(el, el) : mp(el, min(el, v[ptr - 1].second)));
			v[ptr++] = ins;
		}
		void pop()
		{
			ptr--;
		}
		lo back()
		{
			return v[ptr - 1].first;
		}
		bool empty()
		{
			return ptr == 0;
		}
		lo getmin()
		{
			return v[ptr - 1].second;
		}
	};
	stack_min front, back;
	lo MI;
	Que():front(), back(){}
	void push(lo el)
	{
		back.push(el);
	}
	void pop()
	{
		if(front.empty())
		{
			while(!back.empty())
			{
				lo el = back.back();
				back.pop();
				front.push(el);
			}
		}
		front.pop();
	}
	lo getmin()
	{
		return min(!front.empty() ? front.getmin() : INF,
				    !back.empty() ? back.getmin() : INF);
	}
};

lo ma[MN][MN];
lo Lmin[MN][MN];
lo ans[MN][MN];
int main(){
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
     //freopen("perm.out", "w", stdout);
#else
    freopen("matrixmin.in", "r", stdin);
    freopen("matrixmin.out", "w",stdout);
#endif
    lo n, L;
    cin >> n >> L;
    scanf("\n");
    FOR(i, n) FOR(j, n)
	{
    	ma[i][j] = readInt();
	}
    FOR(i, n)
    {
    	Que mine;
    	FOR(j, L)
    	{
    		mine.push(ma[i][j]);
    	}
    	Lmin[i][0] = mine.getmin();
    	for(lo j = 1; j + L <= n; j++)
    	{
    		mine.pop();
    		mine.push(ma[i][j + L - 1]);
    		Lmin[i][j] = mine.getmin();
    	}
    }
    FOR(j, n - L + 1)
    {
    	Que mine;
    	FOR(i, L)
    	{
    		mine.push(Lmin[i][j]);
    	}
    	ans[0][j] = mine.getmin();
    	for(lo i = 1; i + L <= n; i++)
    	{
    		mine.pop();
    		mine.push(Lmin[i + L - 1][j]);
    		ans[i][j] = mine.getmin();
    	}
    }
    FOR(i, n - L + 1)
    {
    	FOR(j, n - L + 1)
		{
    		printf("%d ", ans[i][j]);
		}
    	printf("\n");
    }
}
