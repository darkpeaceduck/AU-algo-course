
#include <cassert>
#include <iostream>
#include <vector>
#include <cstdio>

#define ll long long int
using namespace std;

int main()
{
#ifdef MYLOCAL
	freopen("input", "r", stdin);
#else
#define FILEI "fib"
	freopen(FILEI ".in", "r", stdin);
	freopen(FILEI ".out", "w", stdout);
#endif
	int n;
	cin >> n;
	vector<ll> fib(max(n+1, 10));
	fib[0] = fib[1] = 1;
	for(int i = 2; i <= n; i++){
		fib[i] = fib[i-1]+fib[i-2];
	}
	cout << fib[n];
    return 0;
}
