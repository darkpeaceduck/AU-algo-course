
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
#define all(a) (a).begin(), (a).end()
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
#define MN 500000
const li INF= 2e18;
//==========================
struct node{
	int minpoint;
	int cnt;
	int info;
	node() : info(0), minpoint(0), cnt(0) {}
}tree[MN * 4];


void push(int id){
	tree[id].cnt += tree[id].info;
	if(id * 2 < MN * 4)
		tree[id * 2].info += tree[id].info;
	if(id * 2 + 1 < MN * 4)
		tree[id * 2 + 1].info += tree[id].info;
	tree[id].info = 0;
}

void upd(int id, int l){
	tree[id].minpoint = l;
	tree[id].cnt = 0;
	if(id * 2 < MN * 4){
		tree[id].minpoint = tree[id * 2].minpoint;
		tree[id].cnt = tree[id * 2].cnt;
	}
	if(id * 2 + 1 < MN * 4 && tree[id * 2 + 1].cnt > tree[id * 2].cnt){
		tree[id].minpoint = tree[id * 2 + 1].minpoint;
		tree[id].cnt = tree[id * 2 + 1].cnt;
	}
}

void build(int id, int l, int r){
	if(l == r){
		tree[id].minpoint = l;
		return;
	}
	int m = (l + r) / 2;
	build(id * 2, l, m);
	build(id * 2 + 1, m + 1, r);
	upd(id, l);
}
void inc(int id, int l, int r, int zl, int zr, int value){
	push(id);
	if(zl > zr)
		return;
	if(l == zl && r == zr){
		push(id);
		tree[id].info = value;
		push(id);
		return;
	}
	if(l == r)
		return;
	int m = (l + r) / 2;
	inc(id * 2, l, m, zl, min(m, zr), value);
	inc(id * 2 + 1, m + 1, r, max(m + 1, zl), zr, value);
	upd(id, l);
}


int from(int a){
	return a - MN / 2;
}
int to(int a){
	return a + MN / 2;
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("windows.in", "r", stdin);
    freopen("windows.out", "w", stdout);
#endif
    build(1, 0, MN - 1);
    int n = readInt();
    vector<pair<pair<int, int>, int >> vec;
    vector<pair<int, int>> forfor(n);
    FOR(i, n){
    	int x = to(readInt()),
		y = to(readInt()),
		x2 = to(readInt()) ,
		y2 = to(readInt());
    	vec.pb(mp(mp(x, 0), i));
    	vec.pb(mp(mp(x2, 1), i));
    	forfor[i] = mp(y, y2);
    }
    sort(all(vec));
    pair<int, pair<int, int>> ans = mp(0, mp(0, 0));
    FOR(i, sz(vec)){
    	int x = vec[i].first.first ;
    	int tt = vec[i].first.second;
    	int id = vec[i].second;
		inc(1, 0, MN - 1, forfor[id].first, forfor[id].second,
				!tt ? 1 : -1);
		ans = max(ans, mp(tree[1].cnt, mp(x, tree[1].minpoint)));
    }
    cout << ans.first << endl <<
    		from(ans.second.first) << " " << from(ans.second.second);
}
