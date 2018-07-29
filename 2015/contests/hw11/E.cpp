
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define lo int
struct automato
{
	struct leaf
	{
		lo link, len;
		map<char, lo> nex;
		leaf() {}
	};
	vector<leaf> tree;
	lo sz, pre;
	automato() {
		sz = 1;
		pre = 0;
		tree = vector<leaf>(1);
		tree[0].link = -1;
		tree[0].len = 0;
	}
	void add_s(char c)
	{
		lo cur = sz++;
		tree.push_back(leaf());
		tree[cur].len = tree[pre].len + 1;
		lo temp = pre;
		for (; temp != -1 && !tree[temp].nex.count(c); temp = tree[temp].link)
		{
			tree[temp].nex[c] = cur;
		}
		if (temp == -1)
		{
			tree[cur].link = 0;
		}
		else
		{
			lo p = tree[temp].nex[c];
			if (tree[p].len == tree[temp].len + 1)
			{
				tree[cur].link = p;
			}
			else
			{
				lo clone = sz++;
				tree.push_back(leaf());
				tree[clone].nex = tree[p].nex;
				tree[clone].len = tree[temp].len + 1;
				tree[clone].link = tree[p].link;
				tree[p].link = clone;
				tree[cur].link = clone;

				for (; temp != -1 && tree[temp].nex.count(c) && tree[temp].nex[c] == p; temp = tree[temp].link)
				{
					tree[temp].nex[c] = clone;
				}
			}
		}
		pre = cur;
	};

} text;

char s[200000];
int main() {
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#else
	freopen("nenokku.in", "r", stdin);
	freopen("nenokku.out", "w", stdout);
#endif
	while (gets(s))
	{
		int n = strlen(s);
		if (s[0] == 'A') {
			for (int i = 2; i < n; i++)  {
				text.add_s(tolower(s[i]));
			}
		}
		else
		{
			int id = 0;
			bool ok = true;
			for (int i = 2; i < n; i++)
			{
				if(!text.tree[id].nex.count(tolower(s[i]))){
					ok = false;
					break;
				}
				id = text.tree[id].nex[tolower(s[i])];
			}
			puts(ok ? "YES" : "NO");
		}
	}
}
