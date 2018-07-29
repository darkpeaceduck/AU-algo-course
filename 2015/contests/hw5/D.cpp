
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
#define MN 200100
#define SM MN * 4
#define INF 2e9
//============================

int p[MN];
int lead[MN];
int Rank[MN];
int used[MN];
vector<pair<int, int> > g[MN];
vector<pair<int, int> >q[MN];
pair<pair<int, int>, int>  z[MN];
vector<int> h[MN];
int last[MN];
int count_lca[MN];
int ans[MN];

int get_p(int id){
	return p[id] = (p[id] == id ? id : get_p(p[id]));
}
void unite(int a, int b, int root){
	a  = get_p(a);
	b = get_p(b);
	if(Rank[a] > Rank[b])
		swap(a, b);
	p[a] = b;
	Rank[b] += Rank[a];
	lead[b] = root;
}

void dfs(int id){
	used[id]++;
	for(auto to_p : g[id]){
		int to = to_p.first;
		if(used[to])
			continue;
		dfs(to);
		unite(id, to, id);
	}
	for(auto to : q[id]){
		int with = to.first;
		int z_id = to.second;
		if(used[with]){
			int lca = lead[get_p(with)];
//			DEB("%d %d %d\n", id, z_id, lca);
			count_lca[z_id] = lca;
		}
	}
}
//==========================
vector<int> tree;
void inc(int id, int val){
	for(; id < sz(tree); id += (id + 1) & -(id + 1)){
		tree[id] += val;
	}
}
int geti(int id){
	int val = 0;
	for(; id >= 0; id -= (id + 1) & -(id + 1)){
		val += tree[id];
	}
	return val;
}
//===============================
void dfs2(int id, int edge){
//DEB("%d %d\n", id, edge);
	if(edge != -1){
		inc(edge, -1);
	}
	used[id]++;
	for(auto to_p : g[id]){
		int to = to_p.first;
		int w = to_p.second;
		if(used[to])
			continue;
		int last_sz = sz(h[id]);
		dfs2(to, w);
		for(int i = last_sz; i < sz(h[id]); i++){
			int z_id = h[id][i];
			int W = z[z_id].second;
			ans[z_id] += geti(W) - last[z_id];
 		}
	}
	for(auto to : q[id]){
		int z_id = to.second;
		int w = z[z_id].second;
		int lca = count_lca[z_id];
		last[z_id] = geti(w);
		h[lca].pb(z_id);
	}
	if(edge != -1){
		inc(edge, 1);
	}
}

void clean(int n){
	FOR(i, MN)
		p[i] = lead[i] = i;
	memset(last, -1, sizeof last);
}

int is[1001000];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("union.in", "r", stdin);
    freopen("union.out", "w", stdout);
#endif
    int n = readInt();
    clean(n);
    vector<lo> tempo;
    FOR(i, n - 1){
    	int a= readInt();
    	int b= readInt();
    	int c = readInt();
    	a--;b--;
    	g[a].pb(mp(b, c));
    	g[b].pb(mp(a, c));
    	tempo.pb(c);
    }

    int m = readInt();
    FOR(i, m){
    	int a = readInt(),
    	    b = readInt(),
    	    c = readInt();
    	a--; b--;
    	z[i] = mp(mp(a, b), c);
    	q[a].pb(mp(b, i));
    	q[b].pb(mp(a, i));
    	tempo.pb(c);
    }
    sort(all(tempo));
    tempo.resize(unique(all(tempo)) - tempo.begin());
    FOR(i, sz(tempo)){
    	is[tempo[i]] = i;
    }
    FOR(i, n){
    	for(auto &to : g[i]){
    		to.second = is[to.second];
    	}
    }
    FOR(i, m){
    	z[i].second = is[z[i].second];
    }
    tree.resize(sz(tempo));
    memset(used, 0, sizeof(used));
    dfs(0);
    memset(used, 0, sizeof(used));
    dfs2(0, -1);
    FOR(i, m){
    	writeInt(ans[i]);
    	fast_writechar('\n');
    }
    fast_flush();
};
