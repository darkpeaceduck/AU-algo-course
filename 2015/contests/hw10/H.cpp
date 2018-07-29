
#include <bits/stdc++.h>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <vector>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double

//#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FORN(i, j, n) for(int i = (j); i <(n); i++)
#define all(a) (a).begin(), (a).end()
using namespace std;
#define DEB(...) fprintf(stderr, __VA_ARGS__)
//=======================
//======================

//=======================
//#define pi 3.14159265358979323
#define eps 1e-9
#define INF 2e9
#define MN 40000
#define SM 26
//================================
struct vertex {
	unordered_map<char, int> next, go;
	bool leaf;
	int p;
	char pch;
	int link;
};

vertex t[MN];
int used[MN];
int sz;

void init() {
	t[0].p = t[0].link = -1;
	sz = 1;
}

void add_string (char *s) {
	size_t n =strlen(s);
	int v = 0;
	for (size_t i=0; i< n; ++i) {
		char c = s[i];
		if (!t[v].next.count(c)) {
			t[sz].link = -1;
			t[sz].p = v;
			t[sz].pch = c;
			t[v].next[c] = sz++;
		}
		v = t[v].next[c];
	}
	t[v].leaf = true;
}

int go (int v, char c);

int get_link (int v) {
	if (t[v].link == -1) {
		if (v == 0 || t[v].p == 0)
			t[v].link = 0;
		else
			t[v].link = go (get_link (t[v].p), t[v].pch);
	}
	if(t[t[v].link].leaf)
		t[v].leaf = 1;
	return t[v].link;
}

int go (int v, char c) {
	if (!t[v].go.count(c)) {
		if (t[v].next.count(c))
			t[v].go[c] = t[v].next[c];
		else
			t[v].go[c] = v==0 ? 0 : go (get_link (v), c);
	}
	return t[v].go[c];
}
void bfs(){
	queue<int> q;
	q.push(0);
	while(!q.empty()){
		int id = q.front();
		used[id]++;
		q.pop();
		int suff = get_link(id);
		if(t[suff].leaf){
			t[id].leaf = 1;
		}
		for(auto it : t[id].next){
			int to = it.second;
			if(!used[to]){
				q.push(to);
			}
		}
	}
}

bool dfs(int id){
	used[id] = 1;
	FOR(i, 2){
		int to = go(id, '0' + i);
		if(t[to].leaf)
			continue;
		if(used[to] == 1){
			return true;
		}
		if(!used[to] && dfs(to)){
			return true;
		}
	}
	used[id] = 2;
	return false;
}
char s[MN];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("virus.in", "r", stdin);
    freopen("virus.out", "w", stdout);
#endif
    init();
    int n;
    scanf("%d", &n);
    FOR(i, n){
    	scanf("%s", s);
    	add_string(s);
    }
    bfs();
    memset(used, 0, sizeof used);
    cout << (dfs(0) ? "TAK" : "NIE");
};
