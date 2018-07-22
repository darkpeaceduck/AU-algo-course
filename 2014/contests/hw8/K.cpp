
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
//#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
//#define eps 1e-3
#define MN 5010
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;


using namespace std;

lo LCIS(vector<lo> A, vector<lo> B)
{
    lo N = A.size(),
       M = B.size();
    vector<lo> C(M,0);
    FOR(i, N)
    {
        lo cur=0;
        FOR(j, M)
        {
            if (A[i]==B[j] && cur+1>C[j])
            {
               C[j]=cur+1;
            }
            if (B[j]<A[i] && cur<C[j])
            {
               cur=C[j];
            }
        }
    }

    lo index=-1;
	FOR(i, M)
	{
		if (index == -1 || C[i] > C[index])
		{
		   index=i;
		}
	}
	return C[index];
}


int main()
{
#ifdef MYLOCAL
	 //freopen("perm.ou	t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("lcis.in", "r", stdin);
	freopen("lcis.out", "w",stdout);
#endif
	ios::sync_with_stdio(false);
	lo n, m;
	cin >> n >> m;
	vector<lo> a(n), b(m);
	FOR(i, n)
		cin >> a[i];
	FOR(i, m)
		cin >> b[i];
	cout << LCIS(a, b);
}
