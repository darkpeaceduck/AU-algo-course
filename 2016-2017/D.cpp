


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


#define MAXN 300000
#define MAXK 10
#define MAXC 28

int link[MAXN];
int len[MAXN];
int dp[MAXN];
int ans[MAXN];
int nex[MAXN][MAXC];
char ss[MAXK][MAXN];
size_t slen[MAXK];
char out[MAXN];
vector<int> lenv[MAXN];
vector<pair<char, int>> previous[MAXN];

int sz, pre;
inline void init() {
	sz = 1;
	pre = 0;
	link[0]= -1;
	len[0] = 0;
}

inline void add_s(char c)
{
	int cur = sz++;
	len[cur]= len[pre]+ 1;
	int temp = pre;
	for (; temp != -1 && !nex[temp][c - 'a']; temp = link[temp])
	{
		nex[temp][c - 'a'] = cur;
	}
	if (temp == -1)
	{
		link[cur] = 0;
	}
	else
	{
		int p = nex[temp][c - 'a'];
		if (len[p] == len[temp]+ 1)
		{
			link[cur]= p;
		}
		else
		{
			int clone = sz++;
			memcpy(nex[clone], nex[p], sizeof(int) * MAXC);
			len[clone] = len[temp] + 1;
			link[clone] = link[p];
			link[p] = clone;
			link[cur]= clone;

			for (; temp != -1 && nex[temp][c - 'a'] && nex[temp][c - 'a'] == p; temp = link[temp])
			{
				nex[temp][c - 'a'] = clone;
			}
		}
	}
	pre = cur;
};

void search_most_longest_sub(size_t sn, int ignore, char * out) {
	for(int i = 0; i < sz; i++) {
		ans[i] = dp[i] = len[i];
		lenv[len[i]].push_back(i);
		for(int j = 0; j < MAXC; j++) {
			if (!nex[i][j])
				continue;
			char c = 'a' + j;
			int to = nex[i][j];
			previous[to].push_back(make_pair(c, i));
		}
	}
	for(int i = 0; i < sn; i++) {
		if (i == ignore)
			continue;
		memset(dp, 0, sizeof(dp));
		int v = 0;
		int maxlen = 0;
		for(int j = 0; j < slen[i]; j++) {
			char c = ss[i][j];
			while(v && !nex[v][c-'a']) {
				v = link[v];
				maxlen = len[v];
			}
			if (nex[v][c-'a']) {
				v = nex[v][c-'a'];
				maxlen++;
			}
			dp[v] = max(dp[v], maxlen);
		}
		for(int j = sz; j >= 0; j--) {
			for(int v : lenv[j]) {
				ans[v] = min(ans[v], dp[v]);
				int lnk = link[v];
				if (lnk >= 0) {
					dp[lnk] = max(dp[lnk], min(len[lnk], dp[v]));
				}
			}
		}
	}
	int wh_maxans = 0;
	for(int v = 0; v < sz; v++) {
		if (ans[v] > ans[wh_maxans])
			wh_maxans = v;
	}
	int v = wh_maxans;
	int cur_len = ans[v];
	out[cur_len] = 0;
	vector<int> used(sz, 0);
	while(cur_len) {
		cur_len--;
		used[v] = 1;
		for(auto pair_prev : previous[v]) {
			int prev = pair_prev.second;
			char c = pair_prev.first;
			int minlen = 0;
			if (prev) {
				int lnk = link[prev];
				minlen = len[lnk];
			}
			if (!used[prev] && len[prev] < len[v] && minlen <= cur_len && cur_len <= len[prev]) {
				out[cur_len] = c;
				v = prev;
				break;
			}
		}
	}
	for(int i = 0; i < ans[wh_maxans]; i++) {
		writeChar(out[i]);
	}
	flush();
}
int main() {

#ifdef LOCAL
	freopen("input", "r", stdin);
#else
#define TASK "substr4"
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif


#ifdef TEST
	int k = 10;
#else
	int k = readInt();
#endif
	int minlen = 0;
	for(int i = 0; i < k; i++) {
#ifdef TEST
		int maxlen = 200000;
		for(int j = 0; j < maxlen; j++) {
			ss[i][j] = 'a';
		}
		ss[i][maxlen] = 0;
#else
		readLine(ss[i]);
#endif
		slen[i] = strlen(ss[i]);
		if (slen[i] <= slen[minlen])
			minlen = i;
	}
	init();
	for(size_t i = 0; i < slen[minlen]; i++) {
		add_s(ss[minlen][i]);
	}
	search_most_longest_sub(k, minlen, out);
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
