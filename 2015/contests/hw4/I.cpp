
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
#define MN 300000
#define SM 20
//========================

int p[SM][MN];
int d[MN];
int dsu[MN];
int lead[MN];

int find_p(int id){
	return id == dsu[id] ? id : dsu[id] = find_p(dsu[id]);
}

void unite(int a, int b){
	a = find_p(a);
	b = find_p(b);
	if(a == b)
		return;
	dsu[a] = b;
}

int lca(int a, int b) {
   if (d[a] > d[b]) {
	   swap(a, b);
   }
   int k = d[b] - d[a];
   for (int i = 0; i < SM; ++i) {
	   if (((k >> i) & 1) == 1) {
		   b = p[i][b];
	   }
   }
   assert(d[a] == d[b]);
   if (a == b) {
	   return a;
   }
   for (int i = SM - 1; i >= 0; --i) {
	   if (p[i][a] != p[i][b]) {
		   a = p[i][a];
		   b = p[i][b];
	   }
   }
   a = p[0][a];
   b = p[0][b];
   assert(a == b);
   return a;
}

void add(int a, int b) {
   d[b] = d[a] + 1;
   p[0][b] = a;
   for (int i = 1; i < SM; ++i) {
	   p[i][b] = p[i - 1][p[i - 1][b]];
   }
}

void clean(){
	FOR(i, MN){
		dsu[i] = lead[i] = i;
	}
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("carno.in", "r", stdin);
    freopen("carno.out", "w", stdout);
#endif
    clean();
    int n = readInt();
    int ptr = 1;
    FOR(i, n){
    	char c = fast_readchar();
    	int a = readInt();
//    	DEB("%c %d\n", c, a);
    	if(c == '+'){
    		ptr++;
    		add(a, ptr);
    	}else if(c == '-'){
    		unite(a, p[0][a]);
    	}else{
    		int b = readInt();
    		int lc = lca(a, b);
//    		DEB("%d\n", lc);
    		writeInt(lead[find_p(lc)]);
    		fast_writechar('\n');
    	}
    }
    fast_flush();
}
