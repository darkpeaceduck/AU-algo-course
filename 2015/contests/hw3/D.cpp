
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
#define MN 100100
const li INF= 2e18;
//==========================
struct node{
	li info, value, max;
	node() : info(0), value(-INF), max(-INF){}
};
node tree[MN * 4];
li get_max(int id){
	return id < MN * 4 ? tree[id].max : -INF;
}
void upd(int id){
	tree[id].max = max({tree[id].value, get_max(id * 2),
		get_max(id * 2 + 1)});
}
void push(int id){
	tree[id].value += tree[id].info;
	tree[id].max  += tree[id].info;
	if(id * 2 < MN * 4)
		tree[id * 2].info += tree[id].info;
	if(id * 2  + 1< MN * 4)
		tree[id * 2 + 1].info += tree[id].info;
	tree[id].info = 0;
}
void inc(int id, int l, int r, int zl, int zr, int value){
	push(id);
	if(zl > zr)
		return;
	if(l == zl && r == zr){
		tree[id].info += value;
		push(id);
		return;
	}
	int m = (l + r) / 2;
	inc(id * 2, l, m, zl, min(m, zr), value);
	inc(id * 2 + 1, m + 1, r, max(m + 1, zl),zr, value);
	upd(id);
}

li sum_q(int id, int l, int r, int zl, int zr){
	push(id);
	if(zl > zr)
		return -INF;
	if(l == zl && r == zr){
		return tree[id].max;
	}
	int m = (l + r) / 2;
	return max(sum_q(id * 2, l, m, zl, min(zr, m)),
			sum_q(id * 2 + 1, m + 1, r, max(zl, m +1), zr));
}

void build(int id, int l, int r, vector<lo> &x){
	if(l == r){
		tree[id].value = tree[id].max = x[l];
		return;
	}
	int m = (l + r) / 2;
	build(id * 2, l, m, x);
	build(id * 2 + 1, m + 1, r, x);
	upd(id);
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
#endif
    int n = readInt();
    int k = readInt();
    vector<int> from(n);
    FOR(i, n){
    	from[i] = readInt();
    }
    build(1, 0, n -1, from);
    char s[10];
    FOR(i, k){
    	readWord(s);
    	int l = readInt();
    	int r = readInt();
    	if(l > r)
    		continue;
    	l--;
    	r--;
    	if(!strcmp(s, "max")){
    		writeLong(sum_q(1, 0, n -1, l, r));
    		fast_writechar('\n');
    	}
    	else{
    		int value = readInt();
    		inc(1, 0, n - 1, l, r, value);
    	}
    }
    fast_flush();
}
