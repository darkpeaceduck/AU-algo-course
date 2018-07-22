
///#pragma comment(linker, "/STACK:100000000000000")
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
//#include <unordered_map>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
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
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 1000100
#define sz(n) (lo) (n).size()
#define SM 32
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = (1LL<<62) ;

using namespace std;


struct Set
{
	lo  *a;
	lo NUMS;
	lo SIZE;
	Set():NUMS(0), SIZE(2) {a = new int [SIZE]; FOR(i, SIZE) a[i] = -1;}

	void x2()
	{
		lo NEWSIZE = SIZE * 2;
		lo  *b = new int [NEWSIZE];
		FOR(i, NEWSIZE)
			b[i] = -1;
		FOR(i, SIZE)
		{
			if(a[i] == -1)
				continue;
			lo at = a[i] % NEWSIZE;
			while(b[at] != -1)
			{
				at++;
				if(at == NEWSIZE)
					at = 0;
			}
			b[at] = a[i];
		}
		clear();
		a = b;
		SIZE =NEWSIZE;
	}
	void insert(lo el)
	{
		lo in = el % SIZE;
		while(a[in] != -1)
		{
			if(a[in] == el)
				return;
			in++;
			if(in == SIZE)
				in = 0;
		}
		a[in] = el;
		NUMS++;
		while(NUMS * 2== SIZE)
			x2();
	}

	lo size()
	{
		return NUMS;
	}
	lo realsize()
	{
		return SIZE;
	}
	void clear()
	{
		delete [](a);
	}
};
vector<lo> g[MN];
lo color[MN];
lo ans[MN];
Set * in[MN];
Set* merge(Set *f, Set *s)
{
	if(sz((*f)) > sz((*s)))
		swap(f, s);
	FOR(i, f->realsize())
	{
		if((f->a)[i] != -1)
			s->insert((f->a)[i]);
	}
	//f->clear();
	//delete(f);
	return s;
}

void dfs(lo id, lo p)
{
	in[id] = new Set();
	in[id]->insert(color[id]);
	FOR(i, sz(g[id]))
	{
		lo to = g[id][i];
		if(to == p)
			continue;
		dfs(to, id);
		in[id] = merge(in[id], in[to]);
	}

	ans[id] = sz(*in[id]);
}


int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
    // freopen("perm.out", "w", stdout);
#else
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w",stdout);
#endif
    lo n;
    cin >> n;
    lo root = 0;
    FOR(i, n )
    {
    	lo a, b;
    	scanf("%d%d", &a, &b);
    	a--;
    	if(a == -1)
    	{
    		root = i;
    	}
    	else
    		g[a].pb(i);
    	color[i] = b;
    }
    dfs(root, -1);
    FOR(i, n)
    {
    	printf("%d ", ans[i]);
    }

}
