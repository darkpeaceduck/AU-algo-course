
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
#define SM 20
#define INF 2e9
//============================
int p[SM][MN];
int d[MN];
int tin[MN], tout[MN], timer = 0;
vector<int> g[MN];


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

void dfs(int id, int fr){
	tin[id] = timer++;
	for(auto to : g[id]){
		if(to == fr)
			continue;
		add(id, to);
		dfs(to, id);
	}
	tout[id] = timer;
}

bool is(int a, int b){
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int query(int a, int b, int root){
	if(is(root, a) && is(root, b))
		return lca(a, b);
	if(!is(root, a) && !is(root, b)){
		int aa = lca(root, a);
		int ab = lca(root, b);
		if(aa == ab){
			return lca(a, b);
		}
		if(d[aa] > d[ab])
			return aa;
		return ab;
	}
	return root;
}

void clean(int n){
	FOR(i, n + 1){
		g[i].clear();
		vector<int>().swap(g[i]);
		d[i] = tin[i] = tout[i] = 0;
		FOR(j, SM){
			p[j][i] = 0;
		}
	}
	timer = 0;
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("dynamic.in", "r", stdin);
    freopen("dynamic.out", "w", stdout);
#endif
    while(1){
    	int n = readInt();
    	if(!n)
    		break;
    	clean(n);
    	FOR(i, n - 1){
    		int a = readInt();
    		int b = readInt();
    		g[a].pb(b);
    		g[b].pb(a);
    	}
    	dfs(1, -1);
    	int m = readInt();
    	int root = 1;
    	FOR(i, m){
    		char c = fast_readchar();
    		if(c == '?'){
    			int a = readInt();
    			int b = readInt();
    			writeInt(query(a, b, root));
    			fast_writechar('\n');
    		}
    		else{
    			int a = readInt();
    			root = a;
    		}
    	}
    	fast_flush();
    }
};
