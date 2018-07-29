
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
vector<int> g[MN];
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

char ma[400][400];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("floor.in", "r", stdin);
    freopen("floor.out", "w", stdout);
#endif
    int n = readInt();
    int m = readInt();
    int A = readInt();
    int B = readInt();
    FOR(i, n){
    	readWord(ma[i]);
    }
    const pair<int, int> go[4] = {mp(0, 1), mp(0, -1), mp(1, 0), mp(-1, 0) };
    int cnt = 0;
    FOR(i, n) FOR(j, m){
    	cnt += (ma[i][j] == '*');
    	if((i + j) & 1){
    		if(ma[i][j] == '*')
    		FOR(k, 4){
    			int toi = i + go[k].first;
    			int toj = j + go[k].second;
    			if(toi >= 0 && toj>= 0 && toi < n && toj < m && ma[toi][toj] == '*'){
    				g[i * m + j].pb(toi * m + toj);
    			}
    		}
    	}
    }
    int res = 0;
    memset(mt, -1, sizeof mt);
    memset(remt, -1, sizeof remt);
    int color = 1;
    for (int run = 1; run; ) {
      run = 0;
      color++;
      FOR(i, n) FOR(j, m)
    		  if((i + j) & 1){
    		  int pos = i * m + j;
        if (remt[pos] == -1 && try_kuhn(pos, color)) {
          run = 1;
       }
      }
    }
    FOR(i, n) FOR(j, m){
    	if((i + j) & 1){
    		int pos = i * m + j;
    		res += (remt[pos] != -1);
    	}
    }
    writeInt(min(res * A + (cnt - 2 * res) * B, B * cnt));
    fast_flush();
};
