
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double

#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr, __VA_ARGS__)
using namespace std;

const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
 if(mpos >= MAX_MEM)
	 return malloc(n);
 char *res = mem + mpos;
  mpos += n;
//  assert(mpos <= MAX_MEM);
  return (void *)res;
}
inline void operator delete ( void * ) { }
/** End fast allocation */

inline void * operator new [] ( size_t ) { assert(0); }
inline void operator delete [] ( void * ) { assert(0); }
//===============================================
static const int buf_size = 4096 ;
   inline  int fast_readchar() {
     static char buf[buf_size];
     static int len = 0, pos = 0;
     if (pos == len)
       pos = 0, len = fread(buf, 1, buf_size, stdin);
     if (pos == len)
       return -1;
     return buf[pos++];
   }

   inline  int readUInt() {
     int c = fast_readchar(), x = 0;
     while (c <= 32)
       c = fast_readchar();
     while ('0' <= c && c <= '9')
       x = x * 10 + c - '0', c = fast_readchar();
     return x;
   }

   inline int readInt() {
     int s = 1, c = fast_readchar();
     int x = 0;
     while (c <= 32)
       c = fast_readchar();
     if (c == '-')
       s = -1, c = fast_readchar();
     while ('0' <= c && c <= '9')
       x = x * 10 + c - '0', c = fast_readchar();
     return x * s;
   }

   inline li readLong(){
	   int s = 1, c = fast_readchar();
		li x = 0;
		while (c <= 32)
		  c = fast_readchar();
		if (c == '-')
		  s = -1, c = fast_readchar();
		while ('0' <= c && c <= '9')
		  x = x * 10 + c - '0', c = fast_readchar();
		return x * s;
   }

   inline void readWord( char *s ) {
     int c = fast_readchar();
     while (c <= 32)
       c = fast_readchar();
     while (c > 32)
       *s++ = c, c = fast_readchar();
     *s = 0;
   }

   /** Write */

   static int write_pos = 0;
   static char write_buf[buf_size];

   inline void fast_writechar( int x ) {
     if (write_pos == buf_size)
       fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
     write_buf[write_pos++] = x;
   }

   inline   void fast_flush() {
     if (write_pos)
       fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
   }

   inline void writeInt( int x ) {
     if (x < 0)
       fast_writechar('-'), x = -x;

     char s[24];
     int n = 0;
     while (x || !n)
       s[n++] = '0' + x % 10, x /= 10;
     while (n--)
       fast_writechar(s[n]);
   }

   inline void writeLong( li x ) {
      if (x < 0)
        fast_writechar('-'), x = -x;

      char s[100];
      int n = 0;
      while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
      while (n--)
        fast_writechar(s[n]);
    }

   inline void writeWord( const char *s ) {
     while (*s)
       fast_writechar(*s++);
   }
//=======================
#define pi 3.14159265358979323
#define eps 1e-6
#define INF 2e9
#define MN 270000
#define SM 20
//========================

int tin[MN], tout[MN], timer = 0;
pair<int, int> sp[SM][MN];
vector<int> g[MN];
void dfs(int id, int h){
	tin[id] = timer;
	sp[0][timer++] = mp(h, id);
	for(auto to : g[id]){
		dfs(to, h + 1);
		sp[0][timer++] = mp(h, id);
	}
}

int Len[MN];
int isLen[MN];
void prepare(){
	for(int i = 0, len = 1; len < timer; i++, len <<= 1){
		int nex = (len << 1);
		isLen[i] = len;
		for(int j = len; j < nex; j++){
			Len[j] = i;
		}
		for(int j = 0; j < timer; j++){
			if(j + len < timer){
				sp[i + 1][j] = min(sp[i][j], sp[i][j + len]);
			}
			else
				sp[i + 1][j] = sp[i][j];
		}
	}
}

inline pair<int, int> lca(int a, int b){
	a = tin[a];
	b = tin[b];
	if(a > b)
		swap(a, b);
	int cur = Len[b - a + 1];
	return min(sp[cur][a], sp[cur][b - isLen[cur] + 1]);
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("lca_rmq.in", "r", stdin);
    freopen("lca_rmq.out", "w", stdout);
#endif
    int n = readInt();
    int m = readInt();
    FOR(i, n - 1){
    	int a = readInt();
		g[a].pb(i + 1);
    }
    dfs(0, 0);
    prepare();
//    DEB("%d %d\n", sp[0][0].second, isLen[1]);
    int a1 = readInt(),
    		a2 = readInt(), x = readInt(),  y = readInt(), z = readInt();
    int last = 0;
    li sum = 0;

    FOR(i, m){
    	last = lca((a1 + last) % n, a2).second;
    	sum += last;
    	a1 = (x * 1LL * a1 + y * 1LL * a2 + z) % n;
    	a2 = (x * 1LL * a2 + y * 1LL * a1 + z) % n;
    }
    cout << sum;
    fast_flush();
}
