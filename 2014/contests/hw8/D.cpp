
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
#define MN 110
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e9;


using namespace std;

lo dp[MN][MN];
pair<lo, lo> fr[MN][MN];
char simv[MN][MN];

bool Isalpha(char a)
{
	return isalpha(a) || a == '.';
}
int comp(char a, char b, char &res)
{
	if(Isalpha(a) && Isalpha(b) && a != b)
		return -1;
	lo val = 0;
	if(a == '*' && b == '*')
	{
		val = 0;
		res = -1;
	}
	else
	{
		if(Isalpha(a))
			res = a;
		else if(Isalpha(b))
			res = b;
		else
			res = 'a';
		val = 1;
	}
	return val;
}

char getsimb(char a)
{
	return a == '?' ? 'a' : a;
}
void relax(lo a, lo b, lo val, char go, lo toa, lo tob)
{
	if(dp[toa][tob] > val)
	{
		dp[toa][tob] = val;
		simv[toa][tob] = go;
		fr[toa][tob] = mp(a, b);
	}
}

void cnt(string &f, string &s)
{
	FOR(i, MN) FOR(j, MN)
	{
		dp[i][j] = INF;
		fr[i][j] = mp(-1, -1);
		simv[i][j] = -1;
	}
	dp[0][0] = 0;
	FOR(i, sz(f) ) FOR(j, sz(s))
	{
		char res;
		int val = comp(f[i], s[j], res);
		if(val != -1)
		{
			relax(i, j, dp[i][j] + val, res, i + 1, j + 1);
		}
		if(f[i] == '*' && i  + 1 < sz(f))
		{
			relax(i, j, dp[i][j], -1, i + 1, j);
		}
		if(f[i] == '*')
			relax(i, j, dp[i][j] + val, res, i, j + 1);
		if(s[j] == '*' && j + 1 < sz(s))
		{
			relax(i, j, dp[i][j], -1, i, j + 1);
		}
		if(s[j] == '*')
			relax(i, j, dp[i][j] + val, res, i + 1, j);
	}
	lo lenf = sz(f);
	lo lens = sz(s);
	if(s[lens - 1] == '*')
	for(int i = 0; i < lenf; i++)
	{
		if(f[i] == '*')
			relax(i, lens, dp[i][lens], -1, i + 1, lens);
		else
			relax(i, lens, dp[i][lens] + 1, getsimb(f[i]), i + 1, lens);
	}

	if(f[lenf - 1] == '*')
	for(int j = 0; j < lens; j++)
	{
		if(s[j] == '*')
			relax(lenf , j, dp[lenf][j], -1, lenf, j + 1);
		else
			relax(lenf, j, dp[lenf][j] + 1, getsimb(s[j]), lenf, j + 1);
	}
	if(f[lenf - 1] == '*')
	{
		relax(lenf - 1, lens, dp[lenf -1][lens], -1, lenf, lens);
	}
	if(s[lens - 1] == '*')
	{
		relax(lenf, lens - 1, dp[lenf][lens - 1], -1, lenf, lens);
	}
}

void get_ans(lo a, lo b)
{
//	printf("%d %d\n", a, b);
	if(a == -1)
		return;
	lo toa = fr[a][b].first;
	lo tob = fr[a][b].second;
	get_ans(toa, tob);
	if(simv[a][b] != -1)
	{
		printf("%c", simv[a][b]);
	}
}
void norm(string &f)
{
	string res = "";
	FOR(i, sz(f))
	{
		if(f[i] == '*' && sz(res) && res[sz(res) - 1] == f[i])
			continue;
		res += f[i];
	}
	f = res;
}
char * tempa, *tempb;
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou	t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("patterns2.in", "r", stdin);
	freopen("patterns2.out", "w",stdout);
#endif
	lo T;
	cin >> T;
	tempa = new char[MN];
	tempb = new char[MN];
	gets(tempa);
	FOR(Q, T)
	{
		string f, s;
		gets(tempa);
		gets(tempb);
		lo lena = strlen(tempa);
		FOR(i, lena)
			f += tempa[i];
		lo lenb = strlen(tempb);
		FOR(i, lenb)
			s += tempb[i];
		if(sz(f) == 0 )
		{
			if(s == "*" || sz(s) == 0)
				cout << endl;
			else
				cout << "NO" << endl;
			continue;
		}
		if(sz(s) == 0 )
		{
			if(f == "*" || sz(f) == 0)
				cout << endl;
			else
				cout << "NO" << endl;
			continue;
		}
		norm(f); norm(s);
		cnt(f, s);
		if(dp[sz(f) ][sz(s) ] == INF)
		{
			printf("NO\n");
		}
		else
		{
			get_ans(sz(f) , sz(s) );
			printf("\n");
		}
	}
}

