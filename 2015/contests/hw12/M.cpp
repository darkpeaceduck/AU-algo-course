
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 100100;
int n;
int a[N];
int b;

int main()
{
	freopen("coins.in", "r", stdin);
	freopen("coins.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for (int i = n - 1; i > 0; i--)
		a[i] -= a[i - 1];
	b = 0;
	for (int i = n - 1; i >= 0; i -= 2)
		b ^= a[i];
	if (b == 0)
		printf("Katya\n");
	else
		printf("Sergey\n");

	return 0;
}