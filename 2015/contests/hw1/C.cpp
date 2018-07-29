
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

struct nd
{
	lo y, Sz, val;
	nd *l, *r;
	nd() {}
	nd(lo val) : val(val), Sz(1), l (NULL), r(NULL)
	{
		//srand(clock() ^ rand() * rand());
		y = rand();
	}
};
lo get_sz(nd * go)
{
	if (!go)
		return 0;
	return go->Sz;
}
void upd(nd * go)
{
	if (!go)
		return;
	go->Sz = 1 + get_sz(go->l) + get_sz(go->r);
}
void split(nd *go, nd *&l, nd *&r, lo cur, lo key)
{
	if (!go)
	{
		l = r = NULL;
		return;
	}
	lo with = cur + get_sz(go->l);
	if (with < key)
	{
		split(go->r, go->r, r, with + 1, key);
		l = go;
	}
	else
	{
		split(go->l, l, go->l, cur, key);
		r = go;
	}
	upd(l);
	upd(r);
}
void merge(nd *&go, nd *l, nd *r)
{
	if (!l || !r)
	{
		go = l ? l : r;
		return;
	}
	if (l->y > r->y)
	{
		merge(l->r, l->r, r);
		go = l;
	}
	else
	{
		merge(r->l, l, r->l);
		go = r;
	}
	upd(go);
}

void ins_after(nd *&go, lo pos, lo value){
	nd *l, *r, *l2, *r2;
	split(go, l, r, 0, pos);
	merge(l, l, new nd(value));
	merge(go, l, r);
}
void insb(nd *&go, lo val)
{
	merge(go, go, new nd(val));
}
void insf(nd *&go, lo val)
{
	merge(go, new nd(val), go);
}
lo del(nd *&go, lo val)
{
	nd *l, *r, *l2, *r2;
	split(go, l, r, 0, val);
	split(r, l2, r2, 0, 1);
	merge(go, l, r2);
	return l2->val;
}
lo get_k(nd *go, lo cur, lo key)
{
	lo with = cur + get_sz(go->l);
	if (with == key)
	{
		return go->val;
	}
	if (with < key)
	{
		return get_k(go->r, with + 1, key);
	}
	return get_k(go->l, cur, key);
}
void print(nd *go)
{
	if (!go)
		return;
	print(go->l);
	cout << go->val << " ";
	print(go->r);
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("implicitkey.in", "r", stdin);
    freopen("implicitkey.out", "w", stdout);
#endif
    nd * now = NULL;
    lo n, m;
    cin >> n >> m;
    for(lo i = 0; i < n; i++)
    {
    	int a;
    	scanf("%d", &a);
    	insb(now, a);
    }
    for(int i = 0; i < m; i++){
    	string s;
    	int a, b;
    	cin >> s >> a ;
    	a--;
    	if(s == "del"){
    		del(now, a);
    	}else if(s == "add"){
    		cin >> b;
    		a++;
    		ins_after(now, a, b);
    	}
    }
    cout << get_sz(now) << endl; print(now);
}
