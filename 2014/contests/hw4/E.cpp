
///#pragma comment(linker, "/STACK:100000000000000")
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <bitset>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cctype>

#include <cassert>


#include <ctime>
//#include <unordered_set>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
*/
//

#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 100000
#define sz(n) (lo) (n).size()
#define SM 105 * 100
const li INF = 1e9 ;
#define DEB(...) fprintf(stderr,__VA_ARGS__)

using namespace std;

lo cnt[MN], B[MN], C[MN], temp[MN];
li A[MN];
lo n;

void ss(lo * q)
{
	memset(cnt, 0, sizeof cnt);
	FOR(i, n)
	{
		cnt[q[i]]++;
	}
	for(lo i = 1; i < MN; i++)
	{
		cnt[i] += cnt[i - 1];
	}
	for(lo i = n - 1; i >= 0; i--)
	{
		temp[--cnt[q[i]]] = i;
	}
	memcpy(q, temp, sizeof (lo) * n);
}
void Order()
{
	FOR(i, n)
	{
		B[i] = (A[i] & ((1LL<<16) - 1));
	}
	ss(B);
	FOR(i, n)
	{
		C[i] = (A[B[i]] >> 16);
	}
	ss(C);
	li outp = 0;
	FOR(i, n)
	{
		outp += A[B[C[i]]] *1LL * (i + 1);
	}
	cout << outp << endl;
}
unsigned int cur = 0, a, b; //
unsigned int ra24()
{
	cur = cur * a + b;
	return cur >> 8;
}
unsigned int ra32()
{
	unsigned int A = ra24(), B = ra24();
	return (A << 8) ^ B;
}

int main(){
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
     //freopen("perm.out", "w", stdout);
#else
    freopen("buckets.in", "r", stdin);
    freopen("buckets.out", "w",stdout);
#endif
    lo T;
    cin >> T;
    FOR(TT, T)
    {
//    	cur = 0;
		cin >> n >> a >> b;
		FOR(i, n)
		{
			A[i] = ra32();
		}
		Order();
    }
}
