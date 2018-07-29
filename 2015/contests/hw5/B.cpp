
#include <vector>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pi 3.14159265358979323
#define eps 1e-6
#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define DEB(...) fprintf(stderr, __VA_ARGS__)
#define all(a) (a).begin(), (a).end()
using namespace std;

//=====================================================
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
#define MN 301000
#define SM 17
#define INF 2e9
//============================
//=============   TREAP    =========================
struct leaf
{
	lo x, y, Sz;
	leaf *l, *r, *p;
	leaf(lo x) : x(x), Sz(1), l(NULL), r(NULL), p(NULL) {
		y = rand();
	}
};

typedef leaf * tree;

int get_sz(tree to){
	return to ? to->Sz : 0;
}

void re_parent(tree go){
	if(!go)
		return;
	go->p = NULL;
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
	re_parent(to);
}


void split(tree fr, tree &l, tree &r, lo cur, lo x)
{
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


void print(tree go){
	if(!go)
		return;
	print(go->l);
	DEB("%d ", go->x);;
	print(go->r);
}
// ==========================
set<pair<int, int> > g[MN];
tree node[MN];
int counter = 0;

tree make_root(int a){
	if(g[a].empty())
		return NULL;
	pair<int, int> pa = *g[a].begin();
	tree tree_with = node[pa.second];
	tree root = NULL;
	int id = get_id(tree_with, true, root);
	tree L = NULL, R = NULL;
	split(root, L, R, 0, id - 1);
	merge(root, R, L);
	return root;
}

void link(int a, int b){
	tree L = NULL, R = NULL;
	L = make_root(a);
	R = make_root(b);
	g[a].insert(mp(b, counter));
	g[b].insert(mp(a, counter + 1));
	node[counter] = new leaf(counter);
	node[counter + 1] = new leaf(counter + 1);
	merge(L, L, node[counter]);
	merge(L, L, R);
	merge(L, L, node[counter + 1]);
	counter += 2;
}

void cut(int a, int b){
	auto itL = g[a].lower_bound(mp(b, 0));
	auto itR = g[b].lower_bound(mp(a, 0));
	int idL, idR;
	tree root = NULL;
	idL = get_id(node[itL->second], true, root);
	idR = get_id(node[itR->second], true, root);
	if(idL > idR){
		swap(idL, idR);
	}
	tree L = NULL, R = NULL, L2 = NULL, R2 = NULL;
	split(root, L, R, 0, idL - 1);
	split(R, L2, R2, 0, idR - idL + 1);
	merge(root, L, R2);
//	get_id(L2, true, L2);
//	print(L2);
//	DEB("\n");
	L  = R = R2 = NULL;
	split(L2, L, R, 0, 1);
	L2 = NULL;
	split(R, L2, R2, 0, get_sz(R) - 1);
	delete node[itR->second];
	g[a].erase(itL);
	g[b].erase(itR);
}

bool get(int a, int b){
	if(a == b)
		return true;
	if(g[a].empty())
		return false;
	if(g[b].empty())
		return false;
	tree root_a, root_b;
	auto itL = g[a].begin();
	auto itR = g[b].begin();
//	DEB("%d\n", node[itL->second]->p->p->x);
//	DEB("%d\n", itR->first);
	get_id(node[itL->second], true, root_a);
	get_id(node[itR->second], true, root_b);
	return root_a == root_b;
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("eulertour.in", "r", stdin);
    freopen("eulertour.out", "w", stdout);
#endif
    int n = readInt();
    int m = readInt();
    char s[10];
    FOR(i, m){
    	readWord(s);
    	int a = readInt();
    	int b = readInt();
    	if(s[0] == 'l'){
    		link(a, b);
    	}else if(s[0] == 'g'){
    		writeInt(get(a, b));
    	}else {
    		cut(a, b);
    	}
    }
    fast_flush();
};
