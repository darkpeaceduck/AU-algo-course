
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
#define lo long long int
#define li long long int
#define db double
#define mp make_pair
#define MN 500
using namespace std;

struct leaf
{
	lo x, y, sz;
	leaf *l, *r;
	leaf() {}
	leaf(lo x, lo y) : x(x), y(y), sz(1), l(NULL), r(NULL) {}
};
typedef leaf * tree;
void upd(tree to)
{
	if(!to)
		return;
	to->sz = 1;
	if(to->l)
		to->sz += to->l->sz;
	if(to->r)
		to->sz += to->r->sz;
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
		upd(to);
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
void dfs(tree to)
{
	if(!to)
		return;
	dfs(to->l);
	cout << to->x << " ";
	dfs(to->r);
}
void query(lo l0, lo r0, tree &to)
{
	tree l = NULL, r = NULL, l2 = NULL, r2 = NULL;
	split(to, l, r, 0, l0 - 1);
	split(r, l2, r2, l0 - 1, r0 );
	merge(to, l2, l);
	merge(to, to, r2);
}
int main()
{
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
#else
	freopen("movetofront.in", "r", stdin);
	freopen("movetofront.out", "w", stdout);
#endif
	tree now = NULL, newo = NULL;
	lo n, m;
	cin >> n >> m;
	for(lo i = 0; i < n; i++)
	{
		srand(rand() % 100500 * clock() + 10500);
		newo = new leaf(i + 1, rand() % 1000000007);
		merge(now, now, newo);
	}
	for(lo i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		query(a, b, now);
	}
	dfs(now);
}

