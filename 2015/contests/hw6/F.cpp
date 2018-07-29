
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
vector<int> g[MN], g2[MN], reg[MN];
int mt[MN];
int remt[MN];
int used[MN];
int takex[MN], takey[MN];

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
    freopen("question.in", "r", stdin);
    freopen("question.out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    FOR(i, n){
    	int num;
    	scanf("%d", &num);
    	FOR(j, num){
    		int a;
    		scanf("%d", &a);
    		a--;
    		g2[a].pb(i);
    		reg[i].pb(a);
    	}
    }
    int q;
    cin >> q;
    FOR(i ,q){
    	int num;
    	clean();
    	int color = 1;
    	scanf("%d", &num);
		set<int> start;
    	FOR(i, num){
    		int a;
    		scanf("%d", &a);
    		a--;
    		for(auto to : reg[a]){
    			if(!start.count(to)){
    				start.insert(to);
    				for(auto to2 : g2[to]){
    					if(to2 < a)
    						g[to].pb(to2);
    				}
    			}
    		}
    	}
    	int val = 0;
    	for(auto to : start){
    		val += try_kuhn(to, color++);
    	}
    	printf(val == sz(start) ? "Yes\n" : "No\n");
    }
}
