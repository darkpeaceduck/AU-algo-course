
//#pragma comment(linker, "/STACK:100000000000000")
#include <bits/stdc++.h>
#include <unordered_map>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for (lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr, __VA_ARGS__)
#define what_is(x) cerr << #x << " is " << x << endl;
#define sz(n) (lo) (n).size()
#define mt make_tuple
#define eb emplace_back
// #define pi 3.14159265358979323
#define eps 1e-7
#define MN 300000
#define SM 32
const lo INF = 2e5;


using namespace std;


//	static const int buf_size = 4096;
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

	inline 	 void fast_flush() {
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


int last[MN], used[MN], ptr, bufa[MN], bufb[MN];
int main()
{
#ifdef MYLOCAL
   freopen(NULL, "w", stdout);
   freopen("input.txt", "r", stdin);
#else
 freopen("sforce.in", "r", stdin);
 freopen("sforce.out", "w",stdout);
#endif
 	int n, m;
 	unordered_map<int, priority_queue<int, vector<int>, greater<int> > > cnt;
 	unordered_map<int, int> delta;
 	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > numb;
 	n = readInt();
		FOR(i, n){
			int a = readInt();
			cnt[a].push(i );
			last[i] = a;
		}
		for(auto it : cnt){
			numb.push(mp(sz(it.second), it.second.top()));
		}
		memset(used ,-1, sizeof used);
		m = readInt();
		FOR(i, m){
			char c = fast_readchar();
			if(c == '?'){
				while(ptr > 0){
					int a = bufa[ptr - 1];
					int b = bufb[--ptr];
					used[a] = -1;
					if(b == last[a])
						continue;
					//del
					auto it = cnt.find(last[a]);
					delta[last[a]]++;
					last[a] = b;
					while(!it->second.empty() && it->first != last[it->second.top()]){
						delta[it->first]--;
						it->second.pop();
					}
					if(!it->second.empty())
						numb.push(mp(sz(it->second) - delta[it->first] , it->second.top()));
					//insert
					cnt[b].push(a);
					it = cnt.find(b);
					while(!it->second.empty() && it->first != last[it->second.top()]){
						it->second.pop();
					}
					numb.push(mp(sz(it->second) - delta[it->first], it->second.top()));
				}
				while(1){
					pair<int, int> cur = numb.top();
					auto it = cnt.find(last[cur.second]);
					if(sz(it->second) - delta[it->first]!= cur.first || it->second.top() != cur.second ){
						numb.pop();
					}
					else
						break;
				}
				writeInt(numb.top().second);
				fast_writechar('\n');
				fast_readchar();
			}
			else
			{
				int a = readInt();
				int b = readInt();
				if(used[a] != -1)
					bufb[used[a]] = b;
				else{
					used[a] = ptr;
					bufa[ptr] = a;
					bufb[ptr++] = b;
				}
			}
		}
		fast_flush();
}
