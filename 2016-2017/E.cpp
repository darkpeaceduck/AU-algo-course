


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
int nex[MAXN][MAXC];
int firstpos[MAXN];

int sz, pre;
inline void init() {
	sz = 1;
	pre = 0;
	link[0]= -1;
	len[0] = 0;
	firstpos[0] = -1;
	memset(nex[0], 0, sizeof(int) * MAXC);
//	memset(link, 0, sizeof(int) * MAXN);
//	memset(len, 0, sizeof(int) * MAXN);
//	memset(firstpos, 0, sizeof(int) * MAXN);
//	memset(nex, 0, sizeof(int) * MAXN * MAXC);
}

int newv() {
	int cur = sz++;
	memset(nex[cur], 0, sizeof(int) * MAXC);
	link[cur] = -1;
	len[cur] = 0;
	firstpos[cur] = 0;
	return cur;
}

inline void add_s(char c)
{
	int cur = newv();
	len[cur]= len[pre]+ 1;
	firstpos[cur] = len[cur] - 1;
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
			int clone = newv();
			memcpy(nex[clone], nex[p], sizeof(int) * MAXC);
			len[clone] = len[temp] + 1;
			link[clone] = link[p];
			firstpos[clone] = firstpos[p];
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

inline int geti(char c){
	return c-'a';
}

inline int getc(int i){
	return i+'a';
}

void LZSS(char *s, size_t sn, int case_ind) {
	int pos = 0;
	char temp[200];
	sprintf(temp, "Case #%d:\n", case_ind);
	writeWord(temp);
	while(pos < sn) {
		int delta = 0;
		int v = 0;
		for(delta = pos; delta < sn; delta++) {
			char c = s[delta];
			if (!nex[v][geti(c)])
				break;
			int to = nex[v][geti(c)];
			if (firstpos[to] - (delta - pos) >= pos)
				break;
			v = to;
		}
		if (delta == pos) {
			int c = s[pos];
			writeInt(-1);
			writeChar(' ');
			writeInt(c);
			writeChar('\n');
			pos++;
		} else {
			writeInt(delta - pos);
			writeChar(' ');
			writeInt(firstpos[v] - ((delta - 1)- pos));
			writeChar('\n');
			pos = delta;
		}
	}
	flush();
}

int main() {

#ifdef LOCAL
	freopen("input", "r", stdin);
#else
#define TASK "lzss"
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
	static char s[MAXN];
	int t = readInt();
	for(int i = 1; i <= t; i++) {
		readLine(s);
		init();
		size_t sn = strlen(s);
		for(size_t j = 0; j < sn; j++)
			add_s(s[j]);
		LZSS(s, sn, i);
	}
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
