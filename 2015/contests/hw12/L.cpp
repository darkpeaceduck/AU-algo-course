
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int t;
int n;

int getVal(int x)
{
	if (x % 4 == 3) return x + 1;
	if (x % 4 == 0) return x - 1;
	return x;
}

void solve()
{
	scanf("%d", &n);
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		int x;
		scanf("%d", &x);
		ans ^= getVal(x);
	}
	if (ans == 0)
		printf("SECOND\n");
	else
		printf("FIRST\n");
	return;
}

int main()
{
	freopen("varnim.in", "r", stdin);
	freopen("varnim.out", "w", stdout);

	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		solve();


	return 0;
}