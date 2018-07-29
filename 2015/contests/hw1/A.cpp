
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
    leaf(lo x, lo y) : x(x), y(y), sum(x), l(NULL), r(NULL) {}
    leaf() {}
};

typedef leaf * tree;

void upd(tree cur){
	if(!cur)
		return;
	cur->sum = cur->x;
	if(cur->l)
		cur->sum += cur->l->sum;
	if(cur->r)
		cur->sum += cur->r->sum;
}

li get_sum(tree cur){
	return cur ? cur->sum : 0;
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

lo dfs(tree to)
{
    if(!to->l)
        return to->x;
    return dfs(to->l);
}
li query(tree &to, li a, li b)
{
    tree l, r;
    split(to, l, r, a - 1);
    tree l2, r2;
    split(r, l2, r2, b);
    li ans = get_sum(l2);
    merge(r, l2, r2);
    merge(to, l, r);
    return ans;
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("sum2.in", "r", stdin);
    freopen("sum2.out", "w", stdout);
#endif
    tree now = NULL, newo = NULL;
    lo n;
    cin >> n;
    li last = 0;
    li mod = 1000000000;
    for(lo i = 0; i < n; i++)
    {
    	scanf("\n");
        char c;
        li a;
        scanf("%c %I64d", &c, &a);
        if(c == '+')
        {
            srand(rand() % 100500 * clock() + 123456);
            newo = new leaf((a + last + mod) % mod, rand() % 12345121);
            ins(now, newo);
            last = 0;
        }
        else
        {
        	li b;
        	scanf("%I64d", &b);
            last = query(now, a, b);
            printf("%I64d\n", last);
        }
    }
}
