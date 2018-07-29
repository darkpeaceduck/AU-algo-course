




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

#define MN 20
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FOR_MASK(i, n, mask) for(int i = 0; i < (n); i++) if ((1LL<<i) & mask)
#define FORN(i, j, n) for(int i = (j); i <(n); i++)

#define eps 1e-6
#define INF 2e18

struct pt{
	ll x;
	ll y;
};


/* 0 .. 2PI (conterclock)*/
long double angle(pt && a) {
	long double out = atan2(a.y, a.x);

	if (out >= 0) {
		return out <= M_PI_2 ? (M_PI_2 - out) : (2 * M_PI - (out - M_PI_2));
	}

	return M_PI_2 - out;
//	if (out < 0)
//		out = 2 * PI + out;
//	if (out > 2 * PI)
//	return out;
}

pt operator+(pt a, pt b) {
	return pt {a.x + b.x, a.y + b.y};
}


bool operator<(pt &a, pt &b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
pt operator*(pt a, ll b) {
	return pt {a.x * b, a.y * b};
}

pt operator-(pt a, pt b) {
	return a + b * -1;
}

ll vv(pt a, pt b) {
	return a.x * b.y - a.y * b.x;
}

ll vv2(pt a, pt b) {
	return a.x * b.y + a.y * b.x;
}

ll sc(pt a, pt b) {
	return a.x * b.x + a.y * b.y;
}


ll cw(pt f, pt s, pt d) {
	pt a  = s - f;
	pt b  = d - f;
	return vv(a, b);
}

bool right(pt f, pt s, pt d) {
	return cw(f, s, d) > 0;
}

bool left(pt f, pt s, pt d)
{
	return cw(f, s, d) < 0;
}


struct ConvexHull {
	vector<pt> pts;
	vector<long double> ang;
	ConvexHull () {}
	ConvexHull(pt start) {
		pts.push_back(start);
	}

	void rebuild_convex() {
		sort(pts.begin(), pts.end());
		pt fr = pts.front(),
		   to = pts.back();
		vector<pt> f = {fr}, s = {fr};
		FOR(i, pts.size()) {
			pt now = pts[i];
			if (!left(fr, now, to)  || (i == (int)(pts.size() - 1))) {
				f.push_back(now);
				while(f.size() > 2 &&
						!right(*(f.end() - 3), *(f.end() - 2), *(f.end() - 1))) {
					*(f.end() - 2) = *(f.end() - 1);
					f.pop_back();
				}
			}
			if(!right(fr, now, to) || (i == (int) pts.size() - 1)) {
				s.push_back(now);
				while(s.size() > 2 &&
						!left(*(s.end() - 3), *(s.end() - 2), *(s.end() - 1)))
				{
					*(s.end() - 2) = *(s.end() - 1);
					s.pop_back();
				}
			}
		}
		pts.clear();
		swap(f, s);
		pts.insert(pts.end(), f.begin(), f.end());
		pts.insert(pts.end(), s.rbegin() + 1, s.rend() - 1);
	}

	void rebuild_ang() {
		ang.clear();
		FOR(i, pts.size()) {
			ang.push_back(angle(pts[(i+1)%pts.size()] - pts[i]));
		}
//		for(auto a : ang)
//			cerr << a << " ";
//		cerr << endl;
	}

	void rebuild() {
		rebuild_convex();
		rebuild_ang();
	}

	void merge(ConvexHull &hull) {
		pts.insert(pts.end(), hull.pts.begin(), hull.pts.end());
		sort(pts.begin(), pts.end());
		rebuild();
	}

	ll get(pt q) {
		if (pts.empty())
			return -INF;
		if (pts.size() == 1)
			return sc(q, pts.front());

		long double req_ang = angle(pt{q.y, -q.x});
		int ind = upper_bound(ang.begin(), ang.end(), req_ang) - ang.begin();
		if (ind == ang.size())
			ind = 0;
		return sc(pts[ind], q);
	}

	void clear() {
		pts.clear();
	}

};

ConvexHull parts[MN];

void add(pt q) {
    ConvexHull new_hull(q);

    for (int i = 0; i < MN; i++) {
        if (parts[i].pts.empty()) {
            swap(parts[i], new_hull);
            break;
        } else {
            new_hull.merge(parts[i]);
            parts[i].clear();
        }
    }
}

ll get(pt q) {
    ll res = -INF;
    for (int i = 0; i < MN; i++) {
        res = max(res, parts[i].get(q));
    }

    return res;
}

pt read_pt() {
	pt out;
	out.x = readInt();
	out.y = readInt();
	return out;
}

void print_pt(pt &a) {
	cerr << a.x << " " << a.y;
}

void print_vec(vector<pt> &a) {
	cerr << "vec" << endl;
	for(auto v : a) {
		print_pt(v);
		cerr << endl;
	}
	cerr << endl;
}

int main() {
#ifdef LOCAL
	freopen("input", "r", stdin);
#else
#define TASK "mostfar"
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
//	vector<pt> aa {pt{-1, 2}, pt{0, 0}, pt{0, 3}, pt{0, 4}, pt{1, 3}, pt{2, 0},
//	pt{2,4}, pt{3,2}};
////	vector<pt> aa{pt{0,1}, pt{1,2}, pt	{3,4}};
//	convex::convex_hull(aa);
//	print_vec(aa);
	int n = readInt();
	FOR(i, n) {
		add(read_pt());
	}

	int m = readInt();
	char s[10];
	FOR(i, m) {
		readWord(s);
		pt q = read_pt();
		if (!strcmp(s, "get")) {
			writeInt(get(q));
			writeChar('\n');
		}
		else {
			add(q);
		}
	}
	flush();

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