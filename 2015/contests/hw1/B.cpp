
#pragma comment(linker, "/STACK:100000000000000")
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cctype>
#include <cassert>
#include <ctime>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pi 3.14159265358979323
#define eps 1e-6
#define MN 2000
using namespace std;
const li INF= 2e18;

struct leaf
{
    lo x, y;
    leaf *l, *r;
    li sum;
    int size;
    leaf(lo x, lo y) : x(x), y(y), sum(x), size(1), l(NULL), r(NULL) {}
    leaf() {}
};

typedef leaf * tree;

li get_sum(tree cur){
	return cur ? cur->sum : 0;
}

lo get_sz(tree cur){
	return cur ? cur->size : 0;
}

void upd(tree cur){
	if(!cur)
		return;
	cur->sum = cur->x;
	cur->size = 1;
	if(cur->l)
		cur->sum += cur->l->sum,
		cur->size += cur->l->size;
	if(cur->r)
		cur->sum += cur->r->sum,
		cur->size += cur->r->size;
}


void split(tree fr, tree &l, tree &r, lo key)
{
    if(!fr)
    {
        l = r = NULL;
        return;
    }
    if(fr->x <= key)
    {
        split(fr->r, fr->r, r, key);
        l = fr;
    }
    else
    {
        split(fr->l, l, fr->l, key);
        r = fr;
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


void ins(tree &to, tree fr)
{
    tree l, r;
    split(to, l, r, fr->x - 1);
    tree l2, r2;
    split(r, l2, r2, fr->x);
    bool need = (!l2);
    merge(r, l2, r2);
    if(need)
        merge(l, l, fr);
    merge(to, l, r);
}

void del(tree &to, int el){
	tree l, r;
	split(to, l, r, el - 1);
	tree l2, r2;
	split(r, l2, r2, el);
	merge(to, l, r2);
}

int get_k(tree cur, int need){
//	cerr << cur->x << " " << need << " " << get_sz(cur->l) << endl;
	if(get_sz(cur->r) < need){
		return get_k(cur->l, need - 1 - get_sz(cur->r));
	}
	if(get_sz(cur->r) > need)
		return get_k(cur->r, need);
	return cur->x;

}
lo dfs(tree to)
{
    if(!to->l)
        return to->x;
    return dfs(to->l);
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("kthmax.in", "r", stdin);
    freopen("kthmax.out", "w", stdout);
#endif
    tree now = NULL;
    lo n;
    cin >> n;
    for(lo i = 0; i < n; i++)
    {
    	int a, b;
    	scanf("%d%d", &a, &b);
//    	cerr << a << " " << b << endl;
    	if(a > 0)
    		ins(now, new leaf(b, rand() % INF));
    	else if(a < 0)
    		del(now, b);
    	else
    	{
    		b--;
    		printf("%d\n", get_k(now, b));
//    		cerr << "fin" << endl;
    	}
    }
}
