
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
//#include <unordered_set>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
*/
//

#define mp make_pair
#define pb push_back
#define lo long long int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-4
#define MN 2000100
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = 1e15;


using namespace std;

struct Table
{
	vector<vector<pair<lo, lo> > > a;
	Table(){}
	Table(lo Size)
	{
		a.resize(Size);
	}
	lo get(lo el)
	{
		lo at = el % sz(a);
		FOR(i, sz(a[at]))
		{
			if(a[at][i].first == el)
				return a[at][i].second;
		}
		return -1;
	}
	void set(lo el, lo val)
	{
		lo at = el % sz(a);
		a[at].pb(mp(el, val));
	}
	void del(lo el, lo val)
	{
		lo at = el % sz(a);
		FOR(i, sz(a[at]))
		{
			if(a[at][i] == mp(el, val))
			{
				swap(a[at][i], a[at].back());
				a[at].pop_back();
				return;
			}
		}
	}
};

struct Heap
{
	vector<lo> v;
	Table hash;
	lo ptr;
	bool (*cmp)(lo, lo);
	Heap(lo Size, bool (*with)(lo, lo))
	{
		hash = Table(99971);
		ptr = 1;
		v.resize(Size, INF);
		cmp = with;
	}
	void Swap(lo i, lo j)
	{
		if(v[i] != INF)
		{
			hash.del(v[i], i);
			hash.set(v[i], j);
		}
		if(v[j] != INF)
		{
			hash.del(v[j], j);
			hash.set(v[j], i);
		}
		swap(v[i], v[j]);
	}
	void ins(lo a)
	{
		hash.set(a, ptr);
		v[ptr++] = a;
		lo at = ptr - 1;
		while(at > 1 && (v[at / 2] == INF || (*cmp)(v[at],v[at / 2])))
		{
			Swap(at / 2, at);
			at /= 2;
		}
	}
	void correct(lo in)
	{
		while(!(v[in * 2] == INF && v[in * 2 + 1] == INF))
		{
			lo with = in * 2;
			if(v[in * 2] == INF || (v[in * 2 + 1] != INF
					&& cmp(v[in * 2 + 1], v[in * 2 ])))
				with = in * 2 + 1;
			Swap(in, with);
			in = with;
		}
	}
	lo getmin()
	{
		return v[1];
	}
	void del(lo el)
	{
		lo in = hash.get(el);
		hash.del(el, in);
		v[in] = INF;
		correct(in);
	}
	void print()
	{
		FOR(i, ptr)
		{
			if(i)
			cout << v[i] << " ";
		}
		cout << endl;
	}
};

bool Less(lo a, lo b){ return a < b; }
bool More(lo a, lo b){ return a > b; }
char s[MN];
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("minmax.in", "r", stdin);
	freopen("minmax.out", "w",stdout);
#endif
	lo n;
	cin >> n;
	Heap a(n * 10, Less), b(n * 10, More);
	scanf("\n");
	FOR(i, n)
	{
//    	a.print();
//    	b.print();
		char c;
		scanf("%c", &c);
		if(c == 'I')
		{
			int val;
			scanf("nsert(%d)\n", &val);
//    		DEB("he");
			a.ins(val);
			b.ins(val);
		}
		else
		{
			scanf("%s\n", &s);
			lo val;
			if(!strcmp(s, "etMin"))
			{
				val = a.getmin();
			}
			else
			{
				val = b.getmin();
			}
			printf("%d\n", (int)val);
			a.del(val);
			b.del(val);
		}
	}

}
