
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
#define lo long long  int
#define li unsigned long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define pi 3.14159265358979323
#define eps 1e-9
#define MN 1<<24
#define sz(n) (lo) (n).size()
#define SM 32
#define DEB(...) fprintf(stderr,__VA_ARGS__)
const li INF = (1LL<<62) ;

using namespace std;


bool isdigit(char a)
{
	return a - '0' >= 0 && '9' - a >= 0;
}

lo priority(char a)
{
	if(a == '/' || a == '*')
		return 2;
	if(a == '-')
		return 1;
	if(a == '+')
		return 0;
	return -1;
}

void doexpr(vector<char> &Do, vector<lo> &Numb)
{
	lo r = Numb.back();
	Numb.pop_back();
	lo l = Numb.back();
	Numb.pop_back();
	char with = Do.back();
	Do.pop_back();
	lo res;
	switch(with)
	{
		case '+': res = l + r; break;
		case '-': res = l - r; break;
		case '*': res = l * r; break;
		case '/': res = l / r; break;
	}
	Numb.pb(res);
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
    // freopen("perm.out", "w", stdout);
#else
    freopen("evalhard.in", "r", stdin);
    freopen("evalhard.out", "w",stdout);
#endif
    string s;
    cin >> s;
    s = "(" + s +")";
    vector<char> Do;
    vector<lo> Numb;
    FOR(i, sz(s))
    {
    	if(isdigit(s[i]))
    	{
    		lo val = 0;
    		for(; i < sz(s) && isdigit(s[i]); i++)
    		{
    			val *= 10;
    			val += s[i] - '0';
    		}
    		i--;
    		Numb.pb(val);
    	}
    	else if(s[i] == ')')
    	{
    		/*FOR(i, sz(Do))
				DEB("%c ", Do[i]);
    		DEB("\n");
    		FOR(i, sz(Numb))
					DEB("%d ", Numb[i]);
    		DEB("\n");
    		*/
    		while(Do.back() != '(')
    		{
    			doexpr(Do, Numb);
    		}
    		Do.pop_back();
    	}
    	else
    	{

    		if(s[i] != '(')
    		{
    			/*DEB("here\n");
    			FOR(i, sz(Do))
					DEB("%c ", Do[i]);
				DEB("\n");
				FOR(i, sz(Numb))
						DEB("%d ", Numb[i]);
				DEB("\n");
				*/
				while(!Do.empty() && Do.back()!= '(' && priority(Do.back()) >= priority(s[i]))
				{
					doexpr(Do, Numb);
				}
    		}
    		Do.pb(s[i]);
    	}
    }
    cout << Numb.back();
}
