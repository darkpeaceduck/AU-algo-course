


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

const int MAXN = 233;

int n;
vector<int> g[MAXN];
int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
bool used[MAXN], blossom[MAXN];
int lca_it[MAXN];

int lca (int a, int b) {
	static int color = 0;
	color++;
	for (;;) {
		a = base[a];
		lca_it[a] = color;
		if (match[a] == -1)  break;
		a = p[match[a]];
	}
	for (;;) {
		b = base[b];
		if (lca_it[b] == color)  return b;
		b = p[match[b]];
	}
	return -1;
}

void mark_path (int v, int b, int children) {
	while (base[v] != b) {
		blossom[base[v]] = blossom[base[match[v]]] = true;
		p[v] = children;
		children = match[v];
		v = p[match[v]];
	}
}


int find_path (int root) {
	memset (used, 0, sizeof used);
	memset (p, -1, sizeof p);
	for (int i=0; i<n; ++i)
		base[i] = i;

	used[root] = true;
	int qh=0, qt=0;
	q[qt++] = root;
	while (qh < qt) {
		int v = q[qh++];
		for (size_t i=0; i<g[v].size(); ++i) {
			int to = g[v][i];
			if (base[v] == base[to] || match[v] == to)  continue;
			if (to == root || match[to] != -1 && p[match[to]] != -1) {
				int curbase = lca (v, to);
				memset (blossom, 0, sizeof blossom);
				mark_path (v, curbase, to);
				mark_path (to, curbase, v);
				for (int i=0; i<n; ++i)
					if (blossom[base[i]]) {
						base[i] = curbase;
						if (!used[i]) {
							used[i] = true;
							q[qt++] = i;
						}
					}
			}
			else if (p[to] == -1) {
				p[to] = v;
				if (match[to] == -1)
					return to;
				to = match[to];
				used[to] = true;
				q[qt++] = to;
			}
		}
	}
	return -1;
}

int main() {

#ifdef LOCAL
	freopen("input", "r", stdin);
#else
#define TASK "schedule"
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
	scanf("%d", &n);
	for(;;) {
		int a, b;
		if (scanf("%d", &a) != 1)
			break;
		scanf("%d", &b);
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	memset (match, -1, sizeof match);
	int amount = 0;
	for (int i=0; i<n; ++i)
		if (match[i] == -1) {
			int v = find_path (i);
			while (v != -1) {
				int pv = p[v],  ppv = match[pv];
				match[v] = pv,  match[pv] = v;
				v = ppv;
			}
		}
	vector<pair<int, int>> ans;
	for(int i = 0; i < n; i++) {
		if (match[i] != -1) {
			ans.push_back(make_pair(i, match[i]));
			match[match[i]] = -1;
		}
	}
	writeInt((int)ans.size() * 2);
	writeChar('\n');
	for(auto item : ans) {
		writeInt(item.first + 1);
		writeChar(' ');
		writeInt(item.second + 1);
		writeChar('\n');
	}
	flush();
	return 0;
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
