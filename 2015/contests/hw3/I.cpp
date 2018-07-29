
#include <vector>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <map>
#include <algorithm>
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

//=====================================================
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
#define MN 5000000
#define SM MN * 4
//=======================
struct node{
	int sum;
	node *l, *r;
	node() :  sum(0), l(NULL), r(NULL) {}
	node(const node & from) : sum(from.sum),
			l(from.l), r(from.r) {}
	node & operator=(const node &from){
		sum = from.sum;
		l = from.l;
		r = from.r;
		return *this;
	}
}memo[MN];
int ptr = 0;
node * new_node(){
	if(ptr >= MN)
		return new node();
	return memo + (ptr++);
}
node * new_node(node & oth){
	if(ptr >= MN)
		return new node(oth);
	memo[ptr] = oth;
	return memo + (ptr++);
}
typedef node * pnode;


int get_sum(pnode root){
	return root ? root->sum : 0;
}
void upd(pnode root){
	if(!root)
		return;
	root->sum = get_sum(root->l) + get_sum(root->r);
}

pnode inc(pnode root, int l, int r, int wh, int need){
	pnode root_copy = new_node(*root);
	if(l == r){
		root_copy->sum += need;
		return root_copy;
	}
	int m = (l + r) / 2;
	if(wh <= m){
		if(!root_copy->l)
			root_copy->l = new_node();
		root_copy->l = inc(root_copy->l, l, m, wh, need);
	}
	else{
		if(!root_copy->r)
			root_copy->r = new_node();
		root_copy->r = inc(root_copy->r, m + 1, r, wh, need);
	}
	upd(root_copy);
	return root_copy;
}

int parallel(pnode a, pnode b, int l, int r, int k){
	while(l != r){
		int m = (l + r) / 2;
		int with = (b ? get_sum(b->l) : 0) - (a ? get_sum(a->l) : 0);
		if(with < k){
			k -= with;
			if(a)
				a = a->r;
			if(b)
				b = b->r;
			l = m + 1;
		}else{
			if(a)
				a = a->l;
			if(b)
				b = b->l;
			r = m;
		}
	}
	return l;
}





int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("gyakkyou.in", "r", stdin);
    freopen("gyakkyou.out", "w", stdout);
#endif
    int n = readInt();
    vector<int> from(n);
    from[0] = readInt();
    int l = readInt();
    int m = readInt();
    int mod = 1e9;
    for(int i = 1; i < n; i++){
    	from[i] = (from[i - 1] * 1LL * l + m) % mod;
    }
    vector<int> is = from;
    map<int, int > his;
    sort(all(is));
    FOR(i, sz(is)){
    	if(his.count(is[i]))
    		continue;
    	his[is[i]] = i;
    }
    vector<pnode> roots(n);
    pnode now = new_node();
    FOR(i, n){
//    	cerr << from[i] << endl;
    	now = inc(now, 0, sz(is) - 1, his[from[i]], 1);
    	roots[i] = now;
    }

    int B = readInt();
    unsigned li sum = 0;
    FOR(i, B){
    	int G = readInt();
    	int x1 = readInt();
    	int lx = readInt();
    	int mx = readInt();

    	int y1 = readInt();
    	int ly = readInt();
    	int my = readInt();

    	int k1 = readInt();
    	int lk = readInt();
    	int mk = readInt();
    	FOR(j, G){
    		int a = min(x1, y1);
    		int b = max(x1, y1);
    		if(j > 0)
    			k1 = ((k1 - 1) * 1LL * lk + mk) % (b - a + 1) + 1;
    		int val = parallel((a - 1 ? roots[a - 2] : (node *)NULL), roots[b - 1],
    					0, sz(is) - 1,
    					k1);
			sum += is[val];
//    		cerr << a << " " << b << " " << k1 << " " << is[val] << endl;


    		x1 = ((a - 1) * 1LL * lx + mx) % n + 1;
    		y1 = ((b - 1) * 1LL * ly + my) % n + 1;
    	}
    }
    cout << sum << endl;
};
