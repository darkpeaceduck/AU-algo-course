
//#pragma comment(linker, "/STACK:100000000000000")
#include <bits/stdc++.h>
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
#define MN 3000000
#define SM 32
const lo INF = 2e5;


using namespace std;

class input{
public:
	static const int buf_size = 4096;

	 int fast_readchar() {
	  static char buf[buf_size];
	  static int len = 0, pos = 0;
	  if (pos == len)
	    pos = 0, len = fread(buf, 1, buf_size, stdin);
	  if (pos == len)
	    return -1;
	  return buf[pos++];
	}

	 int readUInt() {
	  int c = fast_readchar(), x = 0;
	  while (c <= 32)
	    c = fast_readchar();
	  while ('0' <= c && c <= '9')
	    x = x * 10 + c - '0', c = fast_readchar();
	  return x;
	}

	 int readInt() {
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

	 void readWord( char *s ) {
	  int c = fast_readchar();
	  while (c <= 32)
	    c = fast_readchar();
	  while (c > 32)
	    *s++ = c, c = fast_readchar();
	  *s = 0;
	}

	/** Write */

	int write_pos = 0;
	char write_buf[buf_size];

	 void fast_writechar( int x ) {
	  if (write_pos == buf_size)
	    fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	  write_buf[write_pos++] = x;
	}

	 void fast_flush() {
	  if (write_pos)
	    fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}

	 void writeInt( int x ) {
	  if (x < 0)
	    fast_writechar('-'), x = -x;

	  char s[24];
	  int n = 0;
	  while (x || !n)
	    s[n++] = '0' + x % 10, x /= 10;
	  while (n--)
	    fast_writechar(s[n]);
	}

	 void writeWord( const char *s ) {
	  while (*s)
	    fast_writechar(*s++);
	}
	void assign_stream(const char * filein, const char *fileout)
	{
		#ifdef MYLOCAL
		   freopen(NULL, "w", stdout);
		   freopen("input.txt", "r", stdin);
		#else
		 freopen(filein, "r", stdin);
		 freopen(fileout, "w",stdout);
		#endif
	}

	input(){
		string filename = "bst";
		assign_stream((filename + ".in").c_str(), (filename + ".out").c_str());
		read();
	}

	virtual ~input()
	{
		fclose(stdin);
		fclose(stdout);
	}
	//==============================================================
	void read()
	{
	}
};

class sol : public input{
	int n, m;
	vector<vector<int> > g;
	vector<int> types;
	vector<int> cnt;
public:
	bool dfs1(int id){
		int child_num = sz(g[id]);
		if(child_num != 0 && child_num != 2)
			return false;
		if(child_num == 0 && !types[id])
			return false;
		set<int> nums;
		FOR(i, sz(g[id])){
			int to = g[id][i];
			if(!types[id] && !types[to])
				return false;
			if(!dfs1(to))
				return false;
			cnt[id] = cnt[to];
			nums.insert(cnt[to]);
		}
		if(sz(nums) > 1)
		{
			return false;
		}
		cnt[id] += types[id];
		return true;
	}
	void dfs2(int id, int p, vector<pair<int, int> >&edge){
		if(types[id]){
		if(p != -1)
			edge.pb(mp(id, p));
		p = id;
		}
		FOR(i, sz(g[id])){
			int to = g[id][i];
			dfs2(to, p, edge);
		}
	}
	void solve()
	{
		cin >> n;
		types.resize(n);
		g.resize(n);
		cnt.resize(n);
		FOR(i, n){
			int a;
			char c;
			cin >> a >> c;
			a--;
			if(c == 'B')
				types[i]++;
			if(a != -2)
				g[a].pb(i);
		}
		if(dfs1(0)){
			cout << "YES" << endl;
			vector<pair<int, int> > edge;
			types[0] = 1;
			dfs2(0, -1, edge);
			cout << sz(edge) << endl;
			for(auto it : edge){
				printf("%d %d\n", it.first + 1, it.second + 1);
			}
		}
		else{
			cout << "NO";
		}
	}
};
int main()
{
   (sol()).solve();

}
