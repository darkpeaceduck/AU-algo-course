
#include <bits/stdc++.h>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <vector>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double

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
#define MN 300010
#define SM 52
//================================
#define cd complex<db>
li A, B, C, D, E, F;

cd att_get(int q){
	return cd( db((A + B * q) ^ (C * q)) / 1000.0, db((D + E * q) ^ (F * q)) /1000.0);
}

void print(cd q){
	printf("%.10lf %.10lf ", q.real(), q.imag());
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("real.in", "r", stdin);
    freopen("real.out", "w", stdout);
#endif
    li N;
    cin >> N >> A >> B >> C >> D >> E >> F;
    int m;
    cin >> m;
    FOR(i, m){
    	int q;
    	scanf("%d", &q);
    	cd a = att_get(q);
    	cd b = att_get(q == 0 ? 0 : N-q);
    	b = cd(b.real(), -b.imag());
    	print((a + b) * 0.5);
    	cd c =(a - b) * 0.5;
    	c = cd(c.imag(), -c.real());
    	print(c);
    	printf("\n");
    }
//    cout << (1<<30);
};
