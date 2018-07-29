
#include <bits/stdc++.h>
#include <unordered_map>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pi 3.14159265358979323
#define eps 1e-6
#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
using namespace std;
const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
  char *res = mem + mpos;
  mpos += n;
  assert(mpos <= MAX_MEM);
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
#define MN 300100
const li INF= 2e18;
//==========================
int tree[MN * 4];
li sum[MN * 4];
li get_sum(int id){
	return id < MN * 4 ? sum[id] : 0;
}
void upd(int id){
	sum[id] = tree[id] + get_sum(id * 2) + get_sum(id * 2 + 1);
}
void inc(int id, int l, int r, int zl, int value){
	if(l == r){
		tree[id] = sum[id] = value;
		return;
	}
	int m = (l + r) / 2;
	if(zl <= m)
		inc(id * 2, l, m, zl, value);
	else
		inc(id * 2 + 1, m + 1, r, zl, value);
	upd(id);
}

li sum_q(int id, int l, int r, int zl, int zr){
	if(zl > zr)
		return 0;
	if(l == zl && r == zr){
		return sum[id];
	}
	int m = (l + r) / 2;
	return sum_q(id * 2, l, m, zl, min(zr, m)) + sum_q(id * 2 + 1, m + 1, r, max(zl, m +1), zr);
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
#endif
    memset(tree, 0, sizeof tree);
    memset(sum ,0, sizeof sum);
    int n = readInt();
    int k = readInt();
    FOR(i, k){
    	char c = fast_readchar();
    	int a = readInt();
    	int b = readInt();
    	if(c == 'A'){
    		a--;
    		inc(1, 0, n -1, a, b);
    	}else{
    		a--;
    		b--;
    		writeLong(sum_q(1, 0, n -1, a, b));
    		fast_writechar('\n');
    	}
    }
    fast_flush();
}
