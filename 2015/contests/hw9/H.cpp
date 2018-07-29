
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


#define INF 9000000001
#define mp make_pair
#define pb push_back
#define pi 3.1415926535
#define lo long long int
#define eps 0.00000001
using namespace std;
struct automato
{

  struct leaf
  {
	  map<char, int> next;
	  int len, link;
	  leaf(){};
  };
  vector<leaf> st;
  int sz, last;
  automato(int siz)
  {
	  st.resize(siz);
	  sz = 1;
	  last = 0;
	  st[0].len = 0;
	  st[0].link = -1;
  };
  int cur, p, q, cl;
  void add(char c)
  {
	  cur = sz++;
	  st[cur].len = st[last].len + 1;
	  for(p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
	  {
		  st[p].next[c] = cur;
	  }
	  if(p == -1)
	  {
		  st[cur].link = 0;
		  last = cur;
		  return;
	  }
	  q = st[p].next[c];
	  if(st[q].len == st[p].len + 1)
	  {
		  st[cur].link = q;
		  last = cur;
		  return;
	  }
	  cl = sz++;
	  st[cl].next = st[q].next;
	  st[cl].len = st[p].len + 1;
	  st[cl].link = st[q].link;
	  for(; p != -1 && st[p].next[c] == q; p = st[p].link)
	  {
		  st[p].next[c] = cl;
	  }
	  st[cur].link = st[q].link = cl;
	  last = cur;
  };
  void add_str(string s)
  {
	  for(int i = 0; i < s.size(); i++)
		  add(s[i]);
  };
  void find(string s)
  {
	 p = 0;
	 q = 0;
	 int v = 0,  l = 0,
		temp = 0,  ans = 0;
	 char c;
	for (int i=0; i<(int)s.length(); ++i) {
		c = s[i];
		while (v && ! st[v].next.count(c)) {
			v = st[v].link;
			l = st[v].len;
		}
		if (st[v].next.count(c)) {
			v = st[v].next[c];
			++l;
		}
		if (l > temp)
			temp = l,  ans = i;
	}
	cout << s.substr (ans - temp +1, temp);
  };
};
int main()
{
	freopen("freedom.in", "r", stdin);
	freopen("freedom.out", "w", stdout);
	int n;
	cin >> n;
	string s, f;
	cin >> f >> s;
	automato at = automato(f.size()* 2);
	at.add_str(f);
	at.find(s);
}
