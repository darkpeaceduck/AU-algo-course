
#include <bits/stdc++.h>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <vector>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db long double

#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FORN(i, j, n) for(int i = (j); i <(n); i++)
#define all(a) (a).begin(), (a).end()
using namespace std;
#define DEB(...) fprintf(stderr, __VA_ARGS__)
//=======================
//======================

#include <cstdio>

/** Interface */

template <class T = int>
inline T readInt();              // skip spaces, read signed int
inline int readUInt();           // skip spaces, read unsigned int
inline int readChar();           // skip spaces, read char
inline void readWord( char *s ); // skip spaces, read word
inline bool readLine( char *s ); // read line (do not save '\n')
inline bool isEof();
inline int peekChar();
inline bool seekEof();

template <class T>
inline void writeInt( T x );
inline void writeChar( int x ); // you may use putchar() instead of it
inline void writeWord( const char *s );
inline void flush();

/** Read */

static const int buf_size = 4096;

static char __buf[buf_size];
static int __len = 0, __pos = 0;

inline bool isEof() {
  if (__pos == __len) {
    __pos = 0, __len = fread(__buf, 1, buf_size, stdin);
    if (__pos == __len)
      return 1;
  }
  return 0;
}

inline int getchar_fast() { // you may use getchar() instead of it
  return isEof() ? -1 : __buf[__pos++];
}

inline int peekChar() {
  return isEof() ? -1 : __buf[__pos];
}

inline bool seekEof() {
  int c;
  while ((c = peekChar()) != -1 && c <= 32)
    __pos++;
  return c == -1;
}

inline int readChar() {
  int c = getchar_fast();
  while (c != -1 && c <= 32)
    c = getchar_fast();
  return c;
}

inline int readUInt() {
  int c = readChar(), x = 0;
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getchar_fast();
  return x;
}

template <class T>
inline T readInt() {
  int s = 1, c = readChar();
  T x = 0;
  if (c == '-')
    s = -1, c = getchar_fast();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getchar_fast();
  return s == 1 ? x : -x;
}

inline void readWord( char *s ) {
  int c = readChar();
  while (c > 32)
    *s++ = c, c = getchar_fast();
  *s = 0;
}

inline bool readLine( char *s ) {
  int c = getchar_fast();
  while (c != '\n' && c != -1)
    *s++ = c, c = getchar_fast();
  *s = 0;
  return c != -1;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
  if (write_pos == buf_size)
    fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
  write_buf[write_pos++] = x;
}

inline void flush() {
  if (write_pos)
    fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
}

template <class T>
inline void writeInt( T x ) {
  if (x < 0)
    writeChar('-'), x = -x;

  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    writeChar(s[n]);
}

inline void writeWord( const char *s ) {
  while (*s)
    writeChar(*s++);
}

//=======================
//#define pi 3.14159265358979323
#define eps 1e-9
#define INF 2e9
#define MN 2010
#define SM 52
//================================

int gauss (vector < bitset<MN> > &a, int m, vector< int > & ans) {
	int n = (int) a.size();
	vector<int> where (m, -1);

	int row = 0;
	FOR(col, m - 1) {
		int with = row;
		for (int i=row; i<n; ++i)
			if (a[i][col]){
				with = i;
				break;
			}
		if(!a[with][col])
			continue;
		swap(a[with], a[row]);
		where[col] = row;
		FOR(i, n){
			if (i != row && a[i][col]) {
				a[i] ^= a[row];
			}
		}
		++row;
	}

	FOR(i, m - 1){
		writeWord(where[i] != -1 ? "No\n" : "Yes\n");
	}

	ans.assign(m - 1, 0);
	FOR(i, m - 1){
		if(where[i] != -1)
			ans[i] = a[where[i]][m - 1];
	}
	FOR(i, n){
		int sum = 0;
		FOR(j, m - 1)
			sum += ans[j] * a[i][j];
		if (sum % 2 != a[i][m - 1])
			return 0;
	}
	return 1;
}


int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("vectors.in", "r", stdin);
    freopen("vectors.out", "w", stdout);
#endif
    int n = readInt(), m = readInt();
    vector<bitset<MN> > kof(n);
    FOR(i, m){
    	FOR(j, n){
    		int a = readInt();
    		kof[j][i] = a;
    	}
    }
    vector<int> ans;
    int res = gauss(kof, m, ans);
    if(!res){
    	writeWord("No\n");
    	flush();
		return 0;
	}
    writeWord("Yes\n");
    FOR(i ,sz(ans)){
    	writeInt(ans[i] ? 1 : 0);
    	writeChar(' ');
    }
    flush();
};
