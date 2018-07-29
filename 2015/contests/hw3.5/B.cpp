
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
#define all(a) (a).begin(), (a).end()
using namespace std;

//=====================================================
const int MAX_MEM = 1e8;
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
#define MN 150100
#define SM MN * 4
//=======================

vector<int> Tree[SM];
vector<int> fen[SM];
void inc(int id, int x, int val){
	for(; x < sz(fen[id]); x += ((x + 1) & -(x + 1))){
		fen[id][x]+= val;
	}
}
int geti(int id, int x){
	int val = 0;
	for(; x >=0; x -= ((x + 1) &-(x + 1))){
		val += fen[id][x];
	}
	return val;
}
int geti(int id, int l, int r){
	if(l > r)
		return 0;
	return geti(id, r) - (l ? geti(id, l - 1) : 0);
}

void build(int id, int l, int r, vector<pair<int, vector<pair<int, int> > > > &from){
	if(l == r){
		FOR(i, sz(from[l].second)){
				if(from[l].second[i].second)
				Tree[id].pb(from[l].second[i].first);
		}
		fen[id].resize(sz(Tree[id]));
		return;
	}
	int m = (l + r ) / 2;
	build(id * 2, l , m, from);
	build(id * 2 + 1, m + 1, r, from);
	Tree[id].resize(sz(Tree[id * 2]) + sz(Tree[id * 2 + 1]));
	fen[id].resize(sz(Tree[id * 2]) + sz(Tree[id * 2 + 1]));
	merge(all(Tree[id * 2]), all(Tree[id * 2 + 1]),
	Tree[id].begin());
}

int get_it(int id, int l, int r , int zl, int zr, int L, int R, bool need = false){

if(zl  > zr)
	return 0;
if(l == zl && r == zr){
	int pos1 = lower_bound(all(Tree[id]), L) - Tree[id].begin();
	int pos2 = upper_bound(all(Tree[id]), R) - Tree[id].begin() - 1;
	int val =  geti(id, pos1, pos2);
	return pos2 - pos1 + 1 -val;
}
int m = (l + r) / 2;
return get_it(id * 2, l, m, zl, min(m, zr), L, R, need) +
	   get_it(id * 2 + 1, m + 1, r ,max(m + 1, zl), zr, L, R, need);
}

void del(int id, int l, int r, int zl, int zr){
	int pos = lower_bound(all(Tree[id]), zr) - Tree[id].begin();
	inc(id, pos, 1);
	if(l == r){
		return;
	}
	int m = (l + r) / 2;
	if(zl <= m)
		del(id * 2, l, m, zl, zr);
	else
		del(id * 2 + 1, m + 1, r, zl, zr);
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("countoffline.in", "r", stdin);
    freopen("countoffline.out", "w", stdout);
#endif
    int n = readInt();
    vector<pair<pair<int, int>, pair<int, int>>> q;
    const int INF = 2e9;
    FOR(i, n){
    	int x = readInt();
    	int y = readInt();
    	q.pb(mp(mp(0, -INF), mp(x, y)));
    }
    int m = readInt();
    FOR(i, m){
    	char c = fast_readchar();
    	int l = readInt(),
			r = readInt();
    	if(c == '?'){
			int L = readInt(),
			R = readInt();
			q.pb(mp(mp(l, r), mp(L, R)));
    	}
    	else{
    		q.pb(mp(mp(0, -INF), mp(l, r)));
    	}
    }
    map<int, vector<pair<int, int> > > temp;
	FOR(i, sz(q)){
    	int l = q[i].first.first;
    	int r = q[i].first.second;
    	int L = q[i].second.first;
    	int R = q[i].second.second;
    	if(r == -INF){
    		temp[L].pb(mp(R, 1));
    	}
    	else{
    		temp[l].pb(mp(r, 0));
    		temp[L].pb(mp(R, 0));
    	}
    }
	vector<pair<int, vector<pair<int, int>>>> b;
	vector<int> a;
	for(auto it : temp){
		sort(all(it.second));
		a.pb(it.first);
		b.pb(it);
	}
	build(1, 0, sz(a) - 1, b);
	vector<int> ans;
	FOR(i, m){
		int l = q[sz(q) - 1 - i].first.first;
		int r = q[sz(q) - 1 - i].first.second;
		int L = q[sz(q) - 1 - i].second.first;
		int R = q[sz(q) - 1 - i].second.second;
		if(r == -INF){
			int pos = lower_bound(all(a), L) - a.begin();
			del(1, 0, sz(a) - 1, pos, R);
		}else{
			int pos = lower_bound(all(a), l) - a.begin();
			int pos2 = upper_bound(all(a), L) - a.begin() - 1;
			ans.pb(get_it(1, 0, sz(a) - 1, pos, pos2, r, R));
		}
	}
	reverse(all(ans));
	FOR(i, sz(ans)){
		writeInt(ans[i]);
		fast_writechar('\n');
	}
    fast_flush();
};
