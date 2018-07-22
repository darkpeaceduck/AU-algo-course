
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
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
#define eps 1e-4
#define MN 2000100
#define sz(n) (lo) (n).size()
#define SM 1000100
const li INF = -1;


using namespace std;

lo pr(char a)
{
	if(a == '*')
		return 2;
	if(a == '-')
		return 1;
	return 0;
}
void doit(vector<lo> &numb, vector<char> &d)
{
	lo a = numb.back();
	numb.pop_back();
	lo b=  numb.back();
	numb.pop_back();
	swap(a, b);
	lo res= 0;
	switch(d.back())
	{
	case '+':res=a + b;break;
	case '-':res=a - b;break;
	case '*':res=a * b;break;
	}
	numb.pb(res);
	d.pop_back();
}
int main(){
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
	 //freopen("perm.out", "w", stdout);
#else
	freopen("postfix.in", "r", stdin);
	freopen("postfix.out", "w",stdout);
#endif
	string s;
	getline(cin, s);
	vector<lo> numb;
	vector<char> d;
	FOR(i, sz(s))
	{
		if(s[i] == ' ')
			continue;
		if(s[i] - '0' >= 0 && s[i] - '9' <= 0)
		{
			lo with = s[i] - '0';
			numb.pb(with);
		}
		else
		{
			d.pb(s[i]);
			doit(numb, d);
		}
	}
	cout << numb[0];
}
