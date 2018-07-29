

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

#define eps 1e-9
#define INF 1e20

int where[MAXN];

int gauss (double a[MAXN][MAXN], int n, int m, vector<double> & ans) {
//	FOR(i, n) {
//		FOR(j, m + 1)
//				cout << a[i][j] << " ";
//		cout << endl;
//	}
//	cout << endl;

	memset(where, -1, sizeof(int) * m);
	fill(ans.begin(), ans.end(), 0);
	int row = 0;
	FOR(col, n){
		int with = row;
		for (int i=row; i<n; ++i)
			if (fabs (a[i][col]) > fabs (a[with][col]))
				with = i;
		if (fabs (a[with][col]) < eps)
			continue;
		FORN(i, col, m + 1)
			swap (a[with][i], a[row][i]);
		where[col] = row;
		FOR(i, n)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				FORN(j, col, m + 1)
					a[i][j] -= a[row][j] * c;
			}
		++row;
	}
//	cout << endl;
//	FOR(i, n) {
//			FOR(j, m + 1)
//					cout << a[i][j] << " ";
//			cout << endl;
//		}

	FOR(i, m)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	FOR(i, n){
		double sum = 0;
		FOR(j, m)
			sum += ans[j] * a[i][j];
		if (fabs (sum - a[i][m]) > eps)
			return 0;
	}

	FOR(i, m)
		if (where[i] == -1)
			return 2;
	return 1;
}

int transform(double matrix[MAXN][MAXN], int m, int n) {
	int extra = m;
	FOR(i, m) {
		matrix[i][n + extra] = matrix[i][n];
		matrix[i][n] = 0;
		matrix[i][n + i] = 1;
	}
	return extra;
}

pair<double, int> solve(double ma_in[MAXN][MAXN], vector<double> &k, int m, int n) {
	static double matrix[MAXN][MAXN], tmp[MAXN][MAXN];
	vector<double> ans(MAXN, 0);
	FOR(i, MAXN)
		memcpy(matrix[i], ma_in[i], sizeof(double) * MAXN);

//	FOR(i, m) {
//		FOR(j, n + 1)
//			cout << matrix[i][j] << " ";
//		cout << endl;
// 	}

	int extra = transform(matrix, m, n);

	double total = -INF;
	int total_set = 0;
	FOR(c, (1<<(n+extra))) {
		int nn = __builtin_popcount(c);
		if (nn <= 8) {
			vector<int> take;
			FOR(i, m) {
				int cnt = 0;
				FOR(j, n + extra) {
					if ((1<<j) & c) {
						take.push_back(j);
						tmp[i][cnt++] = matrix[i][j];
					}
				}
				tmp[i][nn] = matrix[i][n+extra];
			}
			int ret = gauss(tmp, m, nn, ans);
			if (ret == 1){
				double with = 0;
				int cnt = 0;
				int skip = 0;
				FOR(j, n + extra) {
					if ((1<<j) & c) {
						if (j < n)
							with += ans[cnt++] * k[j];
						else if (ans[cnt++] < 0)
							skip = 1;
					}
				}
				if (!skip) {
					total = max(total, with);
					total_set = 1;
				}
			}
		}
	}
	return make_pair(total, total_set);
}

double matrix[MAXN][MAXN];
int main() {
#ifdef LOCAL
	freopen("input", "r", stdin);
#else
#define TASK "simple2"
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
	int n = readInt();
	int m = readInt();
	vector<double> k(n);
	FOR(i, m) {
		FOR(j, n + 1) {
			matrix[i][j] = readInt();
		}
	}
	FOR(i, n)
		k[i] = readInt();

	FOR(i, n) {
		matrix[m + i][i] = -1;
	}
	m += n;

	FOR(i, n) {
		matrix[m][i] = -k[i];
		matrix[m][n] = -INF;
	}

	pair<double, int> sol = solve(matrix, k, m, n);
	if (!sol.second)
		cout << "No solution";
	else {
		pair<double, int> check_sol = solve(matrix, k, m + 1, n);
		if (check_sol.second) {
			cout << "Unbounded";
			exit(0);
		}
		cout << fixed << setprecision(10) << sol.first;
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
