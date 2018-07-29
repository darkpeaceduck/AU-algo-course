




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

#define MAXN 100
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FOR_MASK(i, n, mask) for(int i = 0; i < (n); i++) if ((1LL<<i) & mask)
#define FORN(i, j, n) for(int i = (j); i <(n); i++)

#define eps 1e-6
#define INF 1e18

struct pt {
	double x;
	double y;
};

struct ci {
	pt c;
	double r;
};


void print_pt(pt a) {
	cout << fixed << setprecision(10) << a.x << " " << a.y;
}

pt read_pt() {
	pt r;
	r.x = readInt();
	r.y = readInt();
	return r;
}

void print_ci(ci c) {
	cout << fixed << setprecision(10) << c.r << endl;
	print_pt(c.c);
}

double det(pt a, pt b, pt c) {
	return a.x * (b.y - c.y) - a.y * (b.x - c.x) + (b.x * c.y - b.y * c.x);
}

double is_eq(double a, double b) {
	return fabs(a - b) <= eps;
}

pt operator+(pt a, pt b) {
	return pt {a.x + b.x, a.y + b.y};
}

pt operator*(pt a, double b) {
	return pt {a.x * b, a.y * b};
}

bool operator<(pt a, pt b) {
	return a.x < b.x || (is_eq(a.x, b.x) && a.y < b.y);
}

double R2(pt a){
	return a.x * a.x + a.y * a.y;
}

double dest2(pt a, pt b) {
	return R2(a+b*-1);
}

inline bool inside_ci(ci &a, pt &b, bool pr=false) {
	double f = dest2(a.c, b);
	double s = a.r * a.r;
	if (pr)
		cout << fixed << setprecision(10) << " " << s << endl;
	return f < s || is_eq(f, s);
}

ci circle3(pt a, pt b, pt c) {
	double D = 2 * det(a, b, c);
	if (is_eq(D, 0)) {
		pt pts[3] = {a, b, c};
		sort(pts, pts + 3);
		double diam = INF;
		ci out = { pt {0, 0}, INF };
		do {
			pt ce = (pts[0] + pts[1]) * 0.5;
			double newd = 0;
			FOR(i, 3) {
				newd = max(newd, dest2(ce, pts[i]));
			}
			if (newd < out.r) {
				out.r = newd;
				out.c = ce;
			}
		}while(next_permutation(pts, pts + 3));
		out.r = sqrt(out.r);
		return out;
	}
	double x0 = det( pt { R2(a), a.y},
	                 pt { R2(b), b.y},
					 pt { R2(c), c.y}) / D;
	double y0 = det( pt { R2(a), a.x},
            		 pt { R2(b), b.x},
			         pt { R2(c), c.x}) / -D;
	pt ce = pt {x0, y0};
	double r2 = max(dest2(ce, a), max(dest2(ce, b), dest2(ce, c)));
	return ci {ce, sqrt(r2)};
}

ci circle2(pt a, pt b) {
	pt ce = (a + b) * 0.5;
	double r2 = max(dest2(ce, a), dest2(ce, b));
	return ci {ce, sqrt(r2)};
}

ci circle1(pt a) {
	return ci {a, 0};
}


ci ans { pt{0, 0}, 0};

void solve2(vector<pt> &pts, pt & a, const pt & b, int m) {
    ans = circle2(a, b);
    for (int i = 0; i < m; i++) {
        if (!inside_ci(ans, pts[i])) {
            ans = circle3(a, b, pts[i]);
        }
    }
}

void solve1(vector<pt> &pts, const pt & a, int m) {
	ans.c = a;
    for (int i = 0; i < m; i++) {
        if (!inside_ci(ans, pts[i])) {
            solve2(pts, pts[i], a, i);
        }
    }
}

void solve(vector<pt> &pts) {
    random_shuffle(pts.begin(), pts.end());
    ans.c = pts[0];
    for (int i = 1; i < (int)pts.size(); i++) {
    	if (!inside_ci(ans, pts[i]))  {
            solve1(pts, pts[i], i);
        }
    }
}

//ci circle2ci(pt a, ci c) {
////	print_ci(c);
////	cout << endl;
////	print_pt(a);
////	pt huy{10,10};
////	if (a.x != 10 || a.y != 10)
////	assert(inside_ci(c,huy));
////	cout << endl << endl;
//	double r1 = sqrt(dest2(a, c.c));
//	double R = (r1 + c.r) / 2;
//	pt vec = ((c.c + a*-1) * (1.0 / r1)) * R;
//	pt ce = a + vec;
//	return ci {ce, R};
//}
//
//bool check_inside(ci a, ci b) {
//	double aa = a.r - b.r - sqrt(dest2(a.c, b.c));
//	return aa > 0 || is_eq(aa, 0);
//}
//
//ci circle3ci(pt a, pt b, ci c) {
////	pt huy{10, 10};
////	assert(inside_ci(c, huy));
////	cout << "ya" << endl;
////	print_ci(c);
////	cout << endl;
////	print_pt(a);
////	cout << endl;
////	print_pt(b);
////	cout << endl;
//	double h = sqrt(dest2(a, b))/2;
//	pt d = a + ((b + a*-1) * 0.5);
//	pt vec = (c.c  + d * -1)* (1.0/sqrt(dest2(d, c.c)));
////	print_pt(vec);
////	cout << endl;
//	double l = 0, r = INF;
//	ci last;
//	FOR(i, 30) {
//		double m = (l + r) / 2;
//		double R = sqrt(m*m+h*h);
//		pt ce = d + vec * m;
//		ci with = {ce, R};
//		last = with;
////		assert(inside_ci(with, a));
////		if (!inside_ci(with, b, true)) {
////			abort();
////		}
//		if (check_inside(with, c))
//			r = m;
//		else
//			l = m;
//	}
////	print_ci(last);
////	cout << endl << endl;
//	return last;
//}
//
//ci process_buf(vector<pt> &pts, ci c) {
//	if (pts.size() == 3)
//		return circle3(pts[0], pts[1], pts[2]);
//	if (pts.size() == 1) {
////		cout << "NOT" << endl;
//		return circle2ci(pts[0], c);
//	}
////	cout << "YA" << endl;
//	return circle3ci(pts[0], pts[1], c);
//}
//
//ci solve(vector<pt> &pts, ci c) {
//	vector<pt> buf;
////	cout << "order" << endl;
//	FOR(i, pts.size()) {
////		print_pt(pts[i]);
////		cout << " ";
//		if (!inside_ci(c, pts[i])) {
//			buf.push_back(pts[i]);
//		}
//		if (buf.size() == 3) {
//			c = process_buf(buf, c);
//			buf.clear();
//		}
//	}
////	cout << endl;
//	if (!buf.empty())
//		c = process_buf(buf, c);
//	return c;
//}
//
//ci solve_full(vector<pt> &pts) {
//	ci best = circle3(pts[0], pts[1], pts[2]);
//	return solve(pts, best);
//}
//
//void check() {
//	vector<pt> buf = {pt{0, 0}};
//	ci c {pt{1, 1}, 1};
//	print_ci(process_buf(buf, c));
//}
//
//void check2() {
//	pt huy = pt{10, 10};
//	ci c = circle3(pt{10, 10}, pt{2,1}, {0, 1});
//	print_ci(c);
//	assert(inside_ci(c, huy));
//}


int main() {
#ifdef LOCAL
	freopen("input", "r", stdin);
#else
#define TASK "tower"
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
//	check2();
	int n = readInt();
	vector<pt> pts(n);
	FOR(i, n)
		pts[i] = read_pt();

	solve(pts);
	print_ci(ans);
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
