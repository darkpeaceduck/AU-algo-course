
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
#define MN 100000
#define SM 12
//========================

int p[MN];
int lead[MN];
vector<int> g[MN];
vector<pair<int, int> > q[MN];
int used[MN];
int ans[MN];
int get_p(int id){
	return p[id] = (p[id] == id ? id : get_p(p[id]));
}
void unite(int a, int b, int root){
	a  = get_p(a);
	b = get_p(b);
	if(rand() & 1)
		swap(a, b);
	p[a] = b;
	lead[b] = root;
}

void dfs(int id){
	used[id]++;
	for(auto pa : q[id]){
		int to = pa.first;
		int wr_id = pa.second;
		if(used[to]){
//			DEB("%d %d\n", id, to);
			ans[wr_id] = lead[get_p(to)] + 1;
		}
	}
	for(auto to : g[id]){
		if(!used[to]){
			dfs(to);
			unite(id, to, id);
		}
	}
}


void clean(){
	FOR(i, MN)
		p[i] = lead[i] = i;
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
#endif
    clean();
    int n = readInt();
    int root = 0;
    FOR(i, n - 1){
    	int a = readInt();
    	a--;
    	if(a == -1)
    		root = i;
    	else
    		g[a].pb(i +1 );
//    	DEB("%d %d\n", a, i);
    }
    int m = readInt();
    FOR(i, m){
    	int a = readInt(),
    	    b = readInt();
    	a--;
    	b--;
    	q[a].pb(mp(b, i));
    	q[b].pb(mp(a, i));
    }
    dfs(root);
    FOR(i, m){
    	writeInt(ans[i]);
    	fast_writechar('\n');
    }
    fast_flush();
}
