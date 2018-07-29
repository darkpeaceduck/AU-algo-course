
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
#define INF 2e9

const int MAX_MEM = 1e9;
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

//=============   TREAP    =========================
struct leaf
{
	lo y, Sz, info;
	pair<int ,int > x, mini;
	leaf *l, *r, *p;
	leaf() {}
	leaf(pair<int, int> x) : x(x), mini(x), info(0), Sz(1), l(NULL), r(NULL), p(NULL) {
		y = rand();
	}
};

typedef leaf * tree;

int get_sz(tree to){
	return to ? to->Sz : 0;
}
pair<int, int> get_mini(tree to){
	return to ? to->mini : mp((int)INF, -1);
}

void re_parent(tree go){
	if(!go)
		return;
	if(go->l)
		go->l->p = go;
	if(go->r)
		go->r->p = go;
}
void upd(tree to)
{
	if(!to)
		return;
	to->Sz = 1 + get_sz(to->l) + get_sz(to->r);
	to->mini = min({to->x, get_mini(to->l), get_mini(to->r)});
	re_parent(to);
}

void push(tree to){
	if(!to)
		return;
	if(!to->info )
		return;
	to->mini.first += to->info;
	to->x.first += to->info;
	if(to->l)
		to->l->info += to->info;
	if(to->r)
		to->r->info += to->info;
	to->info = 0;
}

void split(tree fr, tree &l, tree &r, lo cur, lo x)
{
	push(fr);
	if(!fr)
	{
		l = r = NULL;
		return;
	}
	lo now = cur + (fr->l ? fr->l->Sz : 0) + 1;
	if(now > x)
	{
		split(fr->l, l, fr->l, cur, x);
		r = fr;
	}
	else
	{
		split(fr->r, fr->r, r, now, x);
		l = fr;
	}
	upd(l);
	upd(r);
}
void merge(tree &to, tree l, tree r)
{
	push(l);
	push(r);
	if(!l || !r)
	{
		to = (l ? l : r);
		upd(to);
		return;
	}
	if(r->y > l->y)
	{
		merge(r->l, l, r->l);
		to = r;
	}
	else
	{
		merge(l->r, l->r, r);
		to = l;
	}
	upd(to);
}
lo get_id(tree go, bool from, tree &root, lo cur_l = 0, lo cur_r = 0){
    //!from = left, else = right
    if(!go)
        return cur_l;
    if(!go->p)
        root = go;

    if(!from){
        return get_id(go->p, go->p ? go->p->r == go : false, root,
            cur_l,
            cur_r + get_sz(go->r) + 1);
    }else{
        return get_id(go->p, go->p ? go->p->r == go : false, root,
            cur_l + get_sz(go->l) + 1,
            cur_r);
    }
}

// ==========================
#define pi 3.14159265358979323
#define eps 1e-6
#define MN 1000000
#define SM 12
//========================
vector<int> g[MN];
tree ptr[MN];
int p[MN];
void rebuild(int id, int h, tree &ar){
	ptr[id] = new leaf(mp(h, id));
	for(auto to : g[id]){
		merge(ar, ar, new leaf(ptr[id]->x));
		rebuild(to, h + 1, ar);
	}
 	merge(ar, ar, ptr[id]);
}


void pre_push(tree to){
	if(!to)
		return;
	pre_push(to->p);
	push(to);
}

void temp_query(int root, int v){
	g[v].pb(root);
	p[root] = v;
//	while(1){
//		if(p[v] == -1)
//			break;
//		v = p[v];
//	}
	tree temp = NULL, l, r, l2, r2;
	int where = get_id(ptr[v], true, temp );
	split(temp, l, r, 0, where - 1);
	split(r, l2, r2, 0, 1);
	int temp_val = ptr[v]->x.first;
	rebuild(v, ptr[v]->x.first, l2);
	merge(r, l2, r2);
	merge(temp, l, r);
}
void query(int root, int v){
	tree vroot = NULL, root_root = NULL, l = NULL, r = NULL;
	int where = get_id(ptr[v], true, vroot);
	get_id(ptr[root], true, root_root);
	split(vroot, l, r, 0, where);

	pre_push(ptr[v]);
	root_root->info += ptr[v]->x.first + 1;
	push(root_root);

	merge(l, l, root_root);
	merge(l, l, new leaf(ptr[v]->x));
	merge(vroot, l, r);
}

int lca(int a, int b){
	tree aroot, broot;
	int wha = get_id(ptr[a], true, aroot);
	int whb = get_id(ptr[b], true, broot);
	if(aroot != broot){
		return 0;
	}
	if(wha > whb){
		swap(wha, whb);
	}
	tree l, r, l2, r2;
	split(aroot, l, r, 0, wha - 1);
	split(r, l2, r2, 0, whb - wha + 1);
	int lca = get_mini(l2).second;
	merge(r, l2, r2);
	merge(aroot, l, r);
	return lca;
}

void test(){
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("lca3.in", "r", stdin);
    freopen("lca3.out", "w", stdout);
#endif
    memset(p, -1, sizeof p);
    int n = readInt();
    vector<int> roots;
    for(int i = 1; i <= n; i++){
    	int a = readInt();
    	if(a == 0)
    		roots.pb(i);
    	else{
    		g[a].pb(i);
    		p[i] = a;
    	}
    }
    for(auto id : roots){
    	tree temp = NULL;
    	rebuild(id, 0, temp);
    }
    int last = 0;
    int m = readInt();
    bool mode = (m< 15000);
    FOR(i, m){
    	int t = readInt(),
    		u = readInt(),
    		v = readInt();
    	u = (u - 1 + last) % n + 1;
    	v = (v - 1 + last) % n + 1;
    	if(t){
			temp_query(u, v);
//    			query(u, v);
    	}else{
    		last = lca(u, v);
    		writeInt(last);
    		fast_writechar('\n');
    	}
    }
    	fast_flush();
}
