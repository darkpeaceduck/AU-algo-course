
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

typedef long long int64;

const int N = 100000;

int n;
int s[N];
int p[N], c[N], pn[N], cn[N], cnt[N], pInv[N];

void solve()
{
	fill(cnt, cnt + N, 0);
	for (int i = 0; i < n; i++)
		cnt[s[i]]++;
	for (int i = 1; i < N; i++)
		cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--)
		p[--cnt[s[i]]] = i;
	int cls = 1;
	c[p[0]] = 0;
	for (int i = 1; i < n; i++)
	{
		if (s[p[i]] != s[p[i - 1]])
			cls++;
		c[p[i]] = cls - 1;
	}

	for (int h = 0; (1 << h) < n; h++)
	{
		for (int i = 0; i < n; i++)
			pn[i] = (p[i] - (1 << h) + n) % n;
		fill(cnt, cnt + cls, 0);
		for (int i = 0; i < n; i++)
			cnt[c[pn[i]]]++;
		for (int i = 1; i < cls; i++)
			cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--)
			p[--cnt[c[pn[i]]]] = pn[i];
		cls = 1;
		cn[p[0]] = 0;
		for (int i = 1; i < n; i++)
		{
			int m1 = (p[i] + (1 << h)) % n;
			int m2 = (p[i - 1] + (1 << h)) % n;
			if (c[p[i]] != c[p[i - 1]] || c[m1] != c[m2])
				cls++;
			cn[p[i]] = cls - 1;
		}
		copy(cn, cn + n, c);
	}

	int lstPos = 0;
	for (int i = 0; i <= n; i++)
		if (i == n || c[p[i]] != c[p[i - 1]])
		{
			sort(p + lstPos, p + i, greater<int>());
			lstPos = i;
		}

	for (int i = 0; i < n; i++)
		pInv[p[i]] = i;
	int64 sum = 0;
	int lcp = 0;
	for (int i = 0; i < n; i++)
	{
		if (pInv[i] == n - 1)
		{
			lcp = 0;
			continue;
		}
		int j = p[pInv[i] + 1];
		while (lcp < n && s[(i + lcp) % n] == s[(j + lcp) % n])
			lcp++;
		sum += lcp;
		if (lcp > 0)
			lcp--;
	}

	printf("%lld\n", sum);
}

int main()
{
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	freopen("towers.in", "r", stdin);
	freopen("towers.out", "w", stdout);
#endif

		scanf("%d\n", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &s[i]);
		solve();
}
