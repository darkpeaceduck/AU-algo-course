
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
//#include <unordered_map>
//expr
/*#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
*/
//

#define mp make_pair
#define pb push_back
#define lo unsigned int
#define li unsigned long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 1024
#define sz(n) (lo) (n).size()
#define SM 32
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = (1LL<<62) ;

using namespace std;



char mo[MN][MN];
int ma[MN][MN];
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
    // freopen("perm.out", "w", stdout);
#else
    freopen("plusminus.in", "r", stdin);
    freopen("plusminus.out", "w",stdout);
#endif
    lo n, m;
    cin >> n >> m;
    scanf("\n");
    FOR(i, n)
    {
        scanf("%s", &mo[i]);
        FOR(j ,m)
            ma[i][j]= (mo[i][j] == '+');
    }
    FOR(i, n - 1)
    {
        FOR(j, m - 1)
        {
            if(ma[i][j] == 0)
            {
                ma[i][j] = 1- ma[i][j];
                ma[i][j + 1] = 1 - ma[i][j + 1];
                ma[i + 1][j] = 1- ma[i + 1][j];
                ma[i + 1][j + 1] = 1 - ma[i + 1][j + 1];

            }
        }
    }
    FOR(i, n) FOR(j, m)
        {
            if(ma[i][j] != 1)
            {
                cout << "No";
                return 0;
            }

        }
    cout << "Yes";
}
