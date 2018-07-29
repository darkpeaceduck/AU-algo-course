




#include <bits/stdc++.h>
using namespace std;

template <class T = int> inline T readInt();
inline double readDouble();
inline int readUInt();
inline int readChar();
inline void readWord( char *s );
inline bool readLine( char *s ); // do not save '\n'
inline bool isEof();
inline int peekChar();
inline bool seekEof();

template <class T> inline void writeInt( T x, int len = -1 );
template <class T> inline void writeUInt( T x, int len = -1 );
inline void writeChar( int x );
inline void writeWord( const char *s );
inline void writeDouble( double x, int len = 0 );
inline void flush();

typedef long long int ll;

#define MN 150
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FOR_MASK(i, n, mask) for(int i = 0; i < (n); i++) if ((1LL<<i) & mask)
#define FORN(i, j, n) for(int i = (j); i <(n); i++)

#define eps 1e-6
#define INF 1e18

typedef vector<double> pt;
pt read_pt(int d) {
	pt out(d);
	FOR(i, d)
		out[i] = readDouble();
	return out;
}

void print_pt(pt &a) {
	for(auto d : a)
		cout << fixed << setprecision(10) << d << " ";
}

double operator*(pt a, pt b) {
	double out = 0;
	FOR(i, a.size()) {
		out += a[i] * b[i];
	}
	return out;
}
pt operator*(pt a, double b) {
	pt out(a.size());
	FOR(i, a.size()) {
		out[i] = a[i] * b;
	}
	return out;
}


pt operator+(pt a, pt b) {
	pt out(a.size());
	FOR(i, a.size()) {
		out[i] = a[i] + b[i];
	}
	return out;
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

int main() {
#ifdef LOCAL
	freopen("input", "r", stdin);
#else
#define TASK "pam"
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
	int n = readInt();
	int d = readInt();
	vector<pair<pt, int>> pts(n);
	FOR(i, n) {
		pts[i].first = read_pt(d);
		pts[i].second = readInt();
	}
	pt ans = pts[0].first;
	int it = 0;
	while(1) {
		int cont = 0;
		FOR(i, n) {
			int s = sgn(pts[i].first * ans);
//			cout << s << " " << pts[i].second << endl;
			if (s != pts[i].second) {
				ans = ans + (pts[i].first*pts[i].second);
				cont = 1;
			}
//			print_pt(ans);
//			cout << endl;
		}
		if (!cont)
			break;
	}
	print_pt(ans);
}

/** Read */

static const int buf_size = 4096;

static char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
	if (buf_pos == buf_len) {
		buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
		if (buf_pos == buf_len)
			return 1;
	}
	return 0;
}

inline int getChar() {
	return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() {
	return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() {
	int c;
	while ((c = peekChar()) != -1 && c <= 32)
		buf_pos++;
	return c == -1;
}

inline int readChar() {
	int c = getChar();
	while (c != -1 && c <= 32)
		c = getChar();
	return c;
}

inline int readUInt() {
	int c = readChar(), x = 0;
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return x;
}

template <class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

inline double readDouble() {
	int s = 1, c = readChar();
	double x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	if (c == '.') {
		c = getChar();
		double coef = 1;
		while ('0' <= c && c <= '9')
			x += (c - '0') * (coef *= 1e-1), c = getChar();
	}
	return s == 1 ? x : -x;
}

inline void readWord( char *s ) {
	int c = readChar();
	while (c > 32)
		*s++ = c, c = getChar();
	*s = 0;
}

inline bool readLine( char *s ) {
	int c = getChar();
	while (c != '\n' && c != -1)
		*s++ = c, c = getChar();
	*s = 0;
	return c != -1;
}

/** Write */

static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
	if (write_buf_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
	write_buf[write_buf_pos++] = x;
}

inline void flush() {
	if (write_buf_pos)
		fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
}

template <class T>
inline void writeInt( T x, int output_len ) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n < output_len)
		s[n++] = '0';
	while (n--)
		writeChar(s[n]);
}

template <class T>
inline void writeUInt( T x, int output_len ) {
	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n < output_len)
		s[n++] = '0';
	while (n--)
		writeChar(s[n]);
}

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

inline void writeDouble( double x, int output_len ) {
	if (x < 0)
		writeChar('-'), x = -x;
	int t = (int)x;
	writeUInt(t), x -= t;
	writeChar('.');
	for (int i = output_len - 1; i > 0; i--) {
		x *= 10;
		t = std::min(9, (int)x);
		writeChar('0' + t), x -= t;
	}
	x *= 10;
	t = std::min(9, (int)(x + 0.5));
	writeChar('0' + t);
}

