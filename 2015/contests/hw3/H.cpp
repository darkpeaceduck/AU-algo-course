
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
//const int MAX_MEM = 1e8;
//int mpos = 0;
//char mem[MAX_MEM];
//inline void * operator new ( size_t n ) {
//  char *res = mem + mpos;
//  mpos += n;
//  assert(mpos <= MAX_MEM);
//  return (void *)res;
//}
//inline void operator delete ( void * ) { }
///** End fast allocation */
//
//inline void * operator new [] ( size_t ) { assert(0); }
//inline void operator delete [] ( void * ) { assert(0); }

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
pair<li, int> maxi;
node *l, *r;
node() : maxi(mp(0, -1)), l(NULL), r(NULL){}
};
typedef node * pnode;
pair<li, int> get_max(pnode id){
	return id->maxi;
}

void create(pnode id){
	if(!id)
		return;
	if(!id->l)
		id->l = new node();
	if(!id->r)
		id->r = new node();
}
void upd(pnode id){
	id->maxi = max(get_max(id->l),
		get_max(id->r));
}

void inc(pnode id, int l, int r, int zl, pair<li, int> value){
	create(id);
	if(l == r){
		id->maxi = max(id->maxi, value);
		return;
	}
	int m = (r -l ) / 2;
	if(zl <= l + m)
		inc(id->l, l, m + l, zl, value);
	else
		inc(id->r, m + l + 1, r, zl, value);
	upd(id);
}

pair<li, int> sum_q(pnode id, int l, int r, int zl, int zr){
	create(id);
	if(zl > zr)
		return mp(-1, -1);
	if(l == zl && r == zr){
		return id->maxi;
	}
	int m = (r - l) / 2;
	return max(sum_q(id ->l ,l, l + m , zl, min(zr,l + m)),
			sum_q(id->r, l + m + 1, r, max(zl, l +m +1), zr));
}

void re(int now, vector<int> &from){
	if(now == -1)
		return;
	re(from[now], from);
	writeInt(now + 1);
	fast_writechar(' ');
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("rects.in", "r", stdin);
    freopen("rects.out", "w", stdout);
#endif
    pnode root = new node();
    int n = readInt();
    vector<li> ans(n);
    vector<lo> from(n), value(n);
    vector<pair<pair<int, int>, pair<int, int>> > vec;
    FOR(i ,n){
    	int x = readInt();
    	int y = readInt();
    	int x2 = readInt();
    	int y2 = readInt();
    	value[i]= readInt();
    	vec.pb(mp(mp(x, 0), mp(-y2, i)));
    	vec.pb(mp(mp(x2, 1), mp(-y, i)));
    }
    int limit = 1e9 + 1;
    sort(all(vec));
    FOR(i, sz(vec)){
    	int tt = vec[i].first.second;
    	int y = -vec[i].second.first;
    	int id = vec[i].second.second;
    	if(!tt){
    		pair<li, lo> gett = sum_q(root, -limit, limit, y + 1, limit);
//    		cerr << gett.first << " " << gett.second << endl;
    		ans[id] = gett.first + value[id];
    		from[id] = gett.second;
    	}
    	else{
//    		cerr << y << " " << ans[id] << endl;
    		inc(root, -limit, limit, y, mp(ans[id], id));
    	}
    }
    int beg = 0;
    FOR(i, n){
    	if(ans[i] > ans[beg])
    		beg = i;
    }
    writeLong(ans[beg]);
    fast_writechar('\n');
    re(beg, from);
    fast_flush();
}
