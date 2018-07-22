
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
#define lo long long  int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 10000
#define sz(n) (lo) (n).size()
#define SM 105 * 100
const li INF = 1e9 ;


using namespace std;

lo Order(vector<lo> &a, lo l, lo r, lo k)
{
	if(l == r)
		return a[l];
	lo mid = a[l + rand() % (r - l + 1)];
	lo L = l, R = r;
	while(1)
	{
		while(a[l] < mid)
			l++;
		while(a[r] > mid)
			r--;
		if(l > r)
			break;
		swap(a[l], a[r]);
		l++;
		r--;
	}
	/*printf("MID %d L %d R %d K %d\n", mid, l, r, k);
	for(lo i = L; i <= R; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	*/
	r = max(r, L - 1);
	l = min(l, R + 1);
	if(r - L + 1 >= k)
		return Order(a, L, r, k);
	return Order(a, r + 1, R, k - (r - L + 1));
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
void print(vector<lo> &a)
{
	FOR(i, sz(a))
		{
		cout << a[i] << " ";
		}
	cout << endl;
}
int main(){
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
     //freopen("perm.out", "w", stdout);
#else
    freopen("qstat.in", "r", stdin);
    freopen("qstat.out", "w",stdout);
#endif
    lo n, q;
    cin >> n >> q >> a >> b;
    vector<lo> vec(n);
    FOR(i, n)
    {
		vec[i] = ra32();
	}
    cout << Order(vec, 0, sz(vec) - 1, q);

}


#include <vector>
RUSSIAN
#include <вектор>
EXTENSION OPTIONSMORE »
