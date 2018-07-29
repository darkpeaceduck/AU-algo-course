

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

struct automato
{
	struct leaf
	{
		int link, len;
		int cnt;
		map<char, int> nex;
	};
	vector<leaf> tree;
	int sz, pre;
	automato() {
		sz = 1;
		pre = 0;
		tree = vector<leaf>(1);
		tree[0].link = -1;
		tree[0].len = 0;
	}
	void add_s(char c)
	{
		int cur = sz++;
		tree.push_back(leaf());
		tree[cur].len = tree[pre].len + 1;
		int temp = pre;
		for (; temp != -1 && !tree[temp].nex.count(c); temp = tree[temp].link)
		{
			tree[temp].nex[c] = cur;
		}
		if (temp == -1)
		{
			tree[cur].link = 0;
		}
		else
		{
			int p = tree[temp].nex[c];
			if (tree[p].len == tree[temp].len + 1)
			{
				tree[cur].link = p;
			}
			else
			{
				int clone = sz++;
				tree.push_back(leaf());
				tree[clone].nex = tree[p].nex;
				tree[clone].len = tree[temp].len + 1;
				tree[clone].link = tree[p].link;
				tree[p].link = clone;
				tree[cur].link = clone;

				for (; temp != -1 && tree[temp].nex.count(c) && tree[temp].nex[c] == p; temp = tree[temp].link)
				{
					tree[temp].nex[c] = clone;
				}
			}
		}
		tree[cur].cnt = tree[cur].len - tree[tree[cur].link].len;
		pre = cur;
	};
	void gather_stat(int &n, int &m , vector<int> &st) {
		n = sz;
		for(size_t i = 0; i < sz; i++) {
			m += (int)tree[i].nex.size();
		}
		int st_full = pre;
		while(st_full != -1) {
			st.push_back(st_full);
			st_full = tree[st_full].link;
		}
	}
	void print_diff_substr(const char *s, size_t sn) {
			vector<ll> out;
			int v = 0;
			ll answer = 0;
			for(size_t i = 0; i < sn; i++) {
				v = tree[v].nex[s[i]];
				answer += tree[v].cnt;
				writeInt(answer);
				writeChar('\n');
			}
			flush();
	}
	void print() {
		int n = 0, m = 0;
		vector<int> t;
		gather_stat(n, m, t);
		writeInt(n);
		writeChar(' ');
		writeInt(m);
		writeChar('\n');

		for(size_t i = 0; i < sz; i++) {
			for(auto it : tree[i].nex) {
				writeInt(i + 1);
				writeChar(' ');
				writeInt(it.second + 1);
				writeChar(' ');
				writeChar(it.first);
				writeChar('\n');
			}
		}
		writeInt((int)t.size());
		writeChar('\n');
		for(auto a : t){
			writeInt(a + 1);
			writeChar(' ');
		}
		flush();
	}

} AT;
int main() {

#ifdef LOCAL
	freopen("input", "r", stdin);
#else
#define TASK "keepcounted"
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
#define MAXN 400000
	static char s[MAXN];
	readLine(s);
	size_t sn = strlen(s);
	for(size_t i = 0; i < sn; i++) {
		AT.add_s(s[i]);
	}
	AT.print_diff_substr(s, sn);
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
