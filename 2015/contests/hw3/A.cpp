
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
using namespace std;
//===========================================
/** Begin fast allocation */
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

   inline void writeWord( const char *s ) {
     while (*s)
       fast_writechar(*s++);
   }
//=======================
#define MN 400100
const li INF= 2e18;
//==========================
li city[MN]; int ans[MN];
int is_city[MN]; li money[MN];

struct mycomp{
public:
	bool operator()(int a, int b){
		return city[a] > city[b] || (city[a] == city[b] && a < b);
	}
};
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("milliarder.in", "r", stdin);
    freopen("milliarder.out", "w", stdout);
#endif
    int n = readInt();
    char Name[30], City[30];
    int hname, hcity;
//    priority_queue<int, vector<int>, mycomp> q;
    set<int, mycomp> q;
    unordered_map<string, int> names;
    int c1 = 0, c2  = 0;
    map<string, int> cityes;
    FOR(i, n){
    	readWord(Name);
    	readWord(City);
    	string strName(Name);
    	string strCity(City);
    	if(!names.count(strName))
    		names[strName] = c1++;
    	if(!cityes.count(strCity))
			cityes[strCity] = c2++;
    	hname = names[strName];
    	hcity = cityes[strCity];
    	li c = readLong();
    	money[hname] = c;
    	is_city[hname] = hcity;
    	city[hcity] += c;

    }
    FOR(i, c2){
    	if(city[i])
    		q.insert(i);
    }

    int last = 0;
    int k = readInt();
    int m = readInt();
    FOR(i, m){
//    	for(auto it : q){
//    	       	cerr <<  it << " " << city[it] << endl;
//    	    }
//    	cerr << endl;
    	int day = readInt();
    	if(sz(q) == 1 || city[*q. begin()] != city[*(++q.begin())])
			ans[*q.begin()] += day - last;
    	last = day;
		readWord(Name);
		readWord(City);
		string strName(Name);
		string strCity(City);
//		cerr << day << " " << Name << " " << City << endl;
		if(!cityes.count(strCity))
					cityes[strCity] = c2++;
		hname = names[strName];
		hcity = cityes[strCity];
		q.erase(is_city[hname]);
		city[is_city[hname]] -= money[hname];
		q.insert(is_city[hname]);
		q.erase(hcity);
		city[hcity] += money[hname];
		q.insert(hcity);
		is_city[hname] = hcity;
    }
    if(sz(q) == 1 || city[*q. begin()] != city[*(++q.begin())])
    			ans[*q.begin()] += k - last;
    for(auto it : cityes){
    	if(ans[it.second]){
    		writeWord(it.first.c_str());
    		fast_writechar(' ');
    		writeInt(ans[it.second]);
    		fast_writechar('\n');
    	}
    }
    fast_flush();
}
