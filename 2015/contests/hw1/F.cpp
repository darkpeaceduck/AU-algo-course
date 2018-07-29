
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <sstream>
#include <ctime>
#include <iostream>
#define lo int
#define li long long int
#define db double
#define mp make_pair
#define MN 500
using namespace std;
const lo INF = 1e9;

struct leaf
{
	lo x, y, sz, emp;
	leaf *l, *r;
	leaf() {}
	leaf(lo x, lo y) : x(x), y(y), sz(1), l(NULL), r(NULL), emp((x == -1 ? 1 : INF)) {}
};
typedef leaf * tree;
lo maxi = INF;
void upd(tree to)
{
	if(!to)
		return;
	to->sz = 1;
	to->emp = maxi;
	lo he = 1 + (to->l ? to->l->sz : 0);
	if(to->x == -1)
	{
		to->emp = he;
	}
	if(to->l)
	{
		to->sz += to->l->sz;
		to->emp = min(to->emp, to->l->emp);
	}
	if(to->r)
	{
		to->sz += to->r->sz;
		to->emp = min(to->emp, to->r->emp + he);
	}
}
void split(tree fr, tree &l, tree &r, lo cur, lo x)
{
	if(!fr)
	{
		l = r = NULL;
		return;
	}
	lo now = cur + (fr->l ? fr->l->sz : 0) + 1;
	if(now > x)
	{
		split(fr->l, l, fr->l, cur, x);
		r = fr;
	}
	else
	{
		split(fr->r, fr->r, r, now, x);
		l = fr;
	}
	upd(l);
	upd(r);
}
void merge(tree &to, tree l, tree r)
{
	if(!l || !r)
	{
		to = (l ? l : r);
		return;
	}
	if(r->y > l->y)
	{
		merge(r->l, l, r->l);
		to = r;
	}
	else
	{
		merge(l->r, l->r, r);
		to = l;
	}
	upd(to);
}
void dfs(tree to, lo cur, lo maxval)
{
	if(!to)
		return;
	lo szi = (to->l ? to->l->sz : 0) + 1 + cur;

	dfs(to->l, cur, maxval);
	if(szi <= maxval)
	cout << (to->x == -1 ? 0 : to->x)<< " ";
	dfs(to->r, szi, maxval);
}
void query(lo wh, lo val, tree &to)
{
	//1
	tree l = NULL, r = NULL, l2 = NULL, r2 = NULL;
	split(to, l, r, 0, wh - 1);
	split(r, l2, r2, wh - 1, wh);
	bool need = false;
	if(l2->x == -1)
	{
		l2->x = val;
		need = true;
	}
    upd(l2);
	merge(to, l, l2);
	merge(to, to, r2);
	if(need)
		return;
	//2
	split(to, l, r, 0, wh - 1);
	lo toto = r->emp + (l ? l->sz : 0);
    //cout << " " << toto << endl;
	split(r, l2, r2, wh - 1, toto - 1);
    tree l3 = NULL, r3 = NULL;
    split(r2, l3, r3, toto - 1, toto);
	srand(rand() % 100500 * clock() + 10500);
	tree newo = new leaf(val, rand() % 1000000007);
    merge(to, l, newo);
	merge(to, to, l2);
	merge(to, to, r3);
}
lo dfs2(tree to, lo cur)
{
	if(!to)
		return 0;
	lo szi = (to->l ? to->l->sz : 0) + 1 + cur;
	lo ma = 0;
	if(to->x != -1)
		ma = szi;
	ma = max(ma, dfs2(to->l, cur));
	ma = max(ma, dfs2(to->r, szi));
	return ma;
}
int main()
{
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
#else
	freopen("key.in", "r", stdin);
	freopen("key.out", "w", stdout);
#endif
	tree now = NULL, newo = NULL;
	lo n, m;
	cin >> n >> m;
	for(lo i = 0; i < m; i++)
	{
		srand(rand() % 100500 * clock() + 10500);
		newo = new leaf(-1, rand() % 1000000007);
		merge(now, now, newo);
	}
	for(lo i = 1; i <= n; i++)
	{
		lo a, b;
		scanf("%d", &a);
		query(a, i, now);
        //dfs(now, 0, INF);
        //cout << endl;
	}
	lo he = dfs2(now, 0);
	cout << he << endl;
	dfs(now, 0, he);
}
