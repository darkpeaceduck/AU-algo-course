
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
#define MN 100001
#define SM MN * 4
#define INF 2e9
//============================
set<int> g[MN];
int mt[MN];
int remt[MN];
int used[MN];
bool try_kuhn (int v, int color) {
	if (used[v] == color)
		return false;
	used[v] = color;
	for(auto to : g[v]){
		if (mt[to] == -1 || try_kuhn (mt[to], color)) {
			mt[to] = v;
			remt[v] = to;
			return true;
		}
	}
	return false;
}


void dfs(int id){
	used[id]++;
	for(auto to : g[id]){
		if(!used[to]){
			dfs(to);
		}
	}
}

int runit(int n){
	int res = 0;
	memset(mt, -1, sizeof mt);
	memset(remt, -1, sizeof remt);
	int color = 1;
	for (int run = 1; run; ) {
	  run = 0;
	  color++;
	  FOR(i, n){
		if (remt[i] == -1 && try_kuhn(i, color)) {
		  run = 1;
	   }
	  }
	}
	FOR(i, n){
		res += (remt[i] != -1);
	}
	return res;
}



void control(int n, int m, vector<int> &L, vector<int> &R){
	FOR(i, n){
		if(remt[i] < 0)
			continue;
		g[remt[i]].insert(i);
		g[i].erase(g[i].find(remt[i]));
	}
	memset(used, 0, sizeof used);
	FOR(i, n){
		if(remt[i] == -1  && !used[i]){
			dfs(i);
		}
	}
	FOR(i, n){
		if(used[i]){
			L.pb(i);
		}
	}
	FOR(i, m){
		if(!used[i + n]){
			R.pb(i);
		}
	}
}

void clean(){
	memset(mt, -1, sizeof mt);
	memset(used, 0, sizeof used);
	memset(remt, -1, sizeof remt);
	FOR(i, MN){
		g[i].clear();
	}
}

struct tempo{
	int t, x, y, x2, y2;
	int geti(){
		return abs(x2 - x) + abs(y2 - y);
	}
};
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("taxi.in", "r", stdin);
    freopen("taxi.out", "w", stdout);
#endif
    clean();
    int n;
    cin >> n;
    vector<tempo> det;
    int last = -100;
    FOR(i, n){
    	int h, m;
    	int x, y, x2, y2;
    	scanf("%d:%d %d %d %d %d", &h, &m, &x, &y, &x2, &y2);
    	int t = h * 60 + m;
    	if(t < last)
    		t += 24 * 60;
    	last = t;
    	det.pb({t, x, y, x2, y2});
    }
    FOR(i, n) for(int j = i  + 1; j < n; j++){
    	int d = det[i].geti() + tempo({0, det[i].x2, det[i].y2, det[j].x, det[j].y}).geti();
    	if(d < det[j].t - det[i].t){
    		g[i].insert(j);
    	}
    }
    cout << n - runit(n);
}
