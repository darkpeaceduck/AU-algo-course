
//#pragma comment(linker, "/STACK:100000000000000")
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <bitset>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cctype>

#include <cassert>


#include <ctime>
//#include <unordered_set>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <functional>
*/
//

#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-7
#define MN 300000
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;

using namespace std;

//#include <memory>
//#include <pthread.h>
int n, bridges, par[MN], bl[MN], comp[MN], size[MN];


void init() {
	for (int i=0; i<n; ++i) {
		bl[i] = comp[i] = i;
		size[i] = 1;
		par[i] = -1;
	}
	bridges = 0;
}


int get (int v) {
	if (v==-1)  return -1;
	return bl[v]==v ? v : bl[v]=get(bl[v]);
}

int get_comp (int v) {
	v = get(v);
	return comp[v]==v ? v : comp[v]=get_comp(comp[v]);
}

void make_root (int v) {
	v = get(v);
	int root = v,
		child = -1;
	while (v != -1) {
		int p = get(par[v]);
		par[v] = child;
		comp[v] = root;
		child=v;  v=p;
	}
	size[root] = size[child];
}


int cu, u[MN];

void merge_path (int a, int b) {
	++cu;

	vector<int> va, vb;
	int lca = -1;
	for(;;) {
		if (a != -1) {
			a = get(a);
			va.pb (a);

			if (u[a] == cu) {
				lca = a;
				break;
			}
			u[a] = cu;

			a = par[a];
		}

		if (b != -1) {
			b = get(b);
			vb.pb (b);

			if (u[b] == cu) {
				lca = b;
				break;
			}
			u[b] = cu;

			b = par[b];
		}
	}

	for (size_t i=0; i<va.size(); ++i) {
		bl[va[i]] = lca;
		if (va[i] == lca)  break;
		--bridges;
	}
	for (size_t i=0; i<vb.size(); ++i) {
		bl[vb[i]] = lca;
		if (vb[i] == lca)  break;
		--bridges;
	}
}


void add_edge (int a, int b) {
	a = get(a);   b = get(b);
	if (a == b)  return;

	int ca = get_comp(a),
		cb = get_comp(b);
	if (ca != cb) {
		++bridges;
		if (size[ca] > size[cb]) {
			swap (a, b);
			swap (ca, cb);
		}
		make_root (a);
		par[a] = comp[a] = b;
		size[cb] += size[a];
	}
	else
		merge_path (a, b);
}
int main()
{
#ifdef MYLOCAL
     //freopen("perm.ou t", "w", stdout);
    freopen("input.txt", "r", stdin);
#else
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w",stdout);
#endif
    lo m;
    cin >> n >>  m;
    init();
    FOR(i, m)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	add_edge(a, b);
    }
    lo k;
    cin >> k;
    FOR(i, k)
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	b--;
    	add_edge(a, b);
    	printf("%d\n", bridges);
    }
}
