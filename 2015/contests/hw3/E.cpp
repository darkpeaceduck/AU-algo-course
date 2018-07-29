
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
#define MN 1000100
const li INF= 2e18;
//==========================
struct node{
	int info;
	int cnt, len;
	int l_len, r_len;
	node() : info(0), len(0), cnt(0), l_len(-1), r_len(-1){}
};
node tree[MN * 4];

void push(int id, int l, int r){
	if(tree[id].info != -1){
		if(tree[id].info == 0){
			tree[id].cnt = tree[id].len = 0;
			tree[id].l_len = tree[id].r_len = -1;
		}else
		{
			tree[id].cnt = 1;
			tree[id].len = tree[id].r_len = tree[id].l_len = r - l + 1;
		}
		if(id * 2 < MN * 4)
			tree[id * 2].info = tree[id].info;

		if(id * 2 < MN * 4)
			tree[id * 2 + 1].info = tree[id].info;
		tree[id].info = -1;
	}
}

void print(int id){
	cerr << ":l_len " << tree[id].l_len << endl <<
			":r_len " << tree[id].r_len << endl <<
			":cnt " << tree[id].cnt << endl <<
			":len " << tree[id].len << endl;
}
void upd(int id, int l, int r){
	/*cerr << " upd " << id << " " << l << " " << r <<   endl << "LEFT" << endl;
	print(id * 2);
	cerr << "RIGHT " << endl;
	print(id * 2 + 1);
	cerr << endl;
	*/
	tree[id].r_len = tree[id * 2 + 1].r_len;
	tree[id].l_len = tree[id * 2].l_len;
	tree[id].len = tree[id * 2].len + tree[id * 2 + 1].len;
	tree[id].cnt = tree[id * 2].cnt + tree[id * 2 + 1].cnt;
	if(tree[id * 2].r_len != -1 && tree[id * 2 + 1].l_len != -1)
		tree[id].cnt--;
//			(tree[id * 2].r_len != -1 || tree[id * 2 + 1].l_len != -1);'
//	cerr << "RESULT" << endl;
//	print(id);
//	cerr << endl;

}
void inc(int id, int l, int r, int zl, int zr, int value){
	push(id, l, r);
	if(zl > zr)
		return;
	if(l == zl && r == zr){
		tree[id].info = value;
		push(id, l, r);
		return;
	}
	if(l == r)
		return;
	int m = (l + r) / 2;
	inc(id * 2, l, m, zl, min(m, zr), value);
	inc(id * 2 + 1, m + 1, r, max(m + 1, zl),zr, value);
	upd(id, l, r);
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("painter.in", "r", stdin);
    freopen("painter.out", "w", stdout);
#endif
       int n = readInt();
    FOR(i, n){
    	char s = fast_readchar();
    	int l = readInt();
    	int r = readInt();
    	l += MN / 2;
//    	cerr << "QUERY " << l << " " << l + r - 1 << endl;
		inc(1, 0, MN - 1, l, l + r - 1, s == 'B');
		writeInt(tree[1].cnt);
		fast_writechar(' ');
		writeInt(tree[1].len);
		fast_writechar('\n');
//		cerr << endl;
    }
	fast_flush();
}
