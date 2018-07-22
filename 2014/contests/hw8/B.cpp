
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
#define li unsigned long long int
#define db double
#define pb push_back
#define FOR(i, n) for(lo (i) = 0; (i) < (n); (i)++)
//#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr,__VA_ARGS__)
#define pi 3.14159265358979323
//#define eps 1e-3
#define MN 501
#define sz(n) (lo) (n).size()
#define SM 40
const li INF = 2e12;


using namespace std;

string int_to_str(int o)
{
	stringstream ss;
	ss << o;
	string my = "";
	ss >> my;
	return my;
}
int base = 1000*1000*1000;
struct lnum
{
	vector<int> a;
	bool minus;
	lnum(){};
   lnum(string s)
   {
	minus = false;
	if(s[0] == '-')
	{
	   minus = true;
	   s.erase(s.begin());
	}
	for (int i=(int)s.length(); i>0; i-=9)
	if (i < 9)
		a.push_back (atoi (s.substr (0, i).c_str()));
	else
		a.push_back (atoi (s.substr (i-9, 9).c_str()));
   }
   string to_string()
   {
	   string res = "";
	   if(minus) res += "-";
	   res += a.empty() ? "0" : int_to_str(a.back());
       for (int i=(int)a.size()-2; i>=0; --i)
	   res += int_to_str(a[i]);
	   return res;
   }
   bool operator<(const lnum other) const
   {
	   if (a.size() < other.a.size()) return true;
	   if(a.size() > other.a.size()) return false;
	   for(int i = a.size() - 1 ; i >= 0; i--)
	   {
		   if(a[i] < other.a[i]) return true;
		   if(a[i] > other.a[i]) return false;
	   }
	   return false;
   }
   lnum operator -(const lnum temp) const
   {
	   lnum a = *this;
	   lnum b = temp;
	   if(minus && b.minus)
	   {
		   a.minus = true;
		   b.minus = false;
		   return a + b;
	   }
	   else if(!minus && b.minus)
	   {
		   b.minus = false;
		   a.minus = false;
		   return a + b;
	   }
	   else if(minus && !b.minus)
	   {
		   a.minus = false;
		   b.minus = false;
		   a = a + b;
		   a.minus = true;
		   return a;
	   }
	   else a.minus = false;
	   if(a < b) {swap(a, b); a.minus = true;};
	   int carry = 0;
       for (size_t i=0; i<b.a.size() || carry; ++i) {
	   a.a[i] -= carry + (i < b.a.size() ? b.a[i] : 0);
	   carry = a.a[i] < 0;
	   if (carry)  a.a[i] += base;
       }
       while (a.a.size() > 1 && a.a.back() == 0)
	   a.a.pop_back();
	   return a;
   }
   lnum operator + (const lnum b) const
   {
	 lnum a = *this;
	 lnum temp = b;
	 if(b.minus && minus) a.minus = true;
	 else if(b.minus && !minus)
	 {
		a.minus = false;
		temp.minus = false;
		return a - temp;
	 }
	 else if(!b.minus && minus)
	 {
		 a.minus = false;
		 temp.minus = false;
		 return temp - a;
	 }
	 else
	 a.minus = false;
	 int carry = 0;
     for (size_t i=0; i<max(a.a.size(),b.a.size()) || carry; ++i) {
	 if (i == a.a.size())
		a.a.push_back (0);
	  a.a[i] += carry + (i < b.a.size() ? b.a[i] : 0);
	  carry = a.a[i] >= base;
	  if (carry)  a.a[i] -= base;
      }
	  return a;
   }
   lnum operator * (const lnum b) const
   {
	   lnum a = (*this);
	   lnum c; c.a.resize(a.a.size()+b.a.size());
	   if((!minus && b.minus) || ( minus && !b.minus)) c.minus = true;
	   else c.minus = false;
      for (size_t i=0; i<a.a.size(); ++i)
	   for (int j=0, carry=0; j<(int)b.a.size() || carry; ++j) {
		  long long cur = c.a[i+j] + a.a[i] * 1ll * (j < (int)b.a.size() ? b.a[j] : 0) + carry;
		  c.a[i+j] = int (cur % base);
		  carry = int (cur / base);
	   }
        while (c.a.size() > 1 && c.a.back() == 0)
	       c.a.pop_back();
		return c;
   }
   bool operator ==(const lnum b) const
   {
	   if(minus != b.minus) return false;
	   if(a.size() != b.a.size() && !((a.size() == 0 && b.a.size() == 1 && b.a[0] == 0) || (a.size() == 1 && a[0] == 0 && b.a.size() == 0))) return false;
	   for(int i = 0; i < a.size(); i++)
	   {
		   if(a[i] != b.a[i]) return false;
	   }
	   return true;
   }
   void print()
   {
	if(minus)cout << "-";
    printf ("%d", a.empty() ? 0 : a.back());
    for (int i=(int)a.size()-2; i>=0; --i)
	printf ("%09d", a[i]);
   }
   lnum anti()
   {
	   lnum out;
	   out.a = a;
	   out.minus = !minus;
	   return out;
   }
};
const pair<lo, lo> go[4] = {mp(-1, 2),mp(1, 2), mp(2, 1), mp(2, -1)};
lnum dp[MN][MN];
lo n, m;
bool cor(lo x, lo y)
{
	return x >= 0 && y >= 0 && x < n && y < m;
}
int main(){
#ifdef MYLOCAL
	 //freopen("perm.ou	t", "w", stdout);
	freopen("input.txt", "r", stdin);
#else
	freopen("knight2.in", "r", stdin);
	freopen("knight2.out", "w",stdout);
#endif
	FOR(i, MN) FOR(j, MN)
	{
		dp[i][j] = lnum("0");
	}
	cin >> n >> m;
	dp[0][0] = lnum("1");
	for(lo i = 0; i < (n + m) - 1; i++)
	{
		FOR(j, m)
		{
			lo fri = i - j;
			if(cor(fri, j))
			{
				FOR(k, 4)
				{
					lo toi = fri + go[k].first;
					lo toj = j + go[k].second;
					if(cor(toi, toj))
						dp[toi][toj] =dp[toi][toj] + dp[fri][j];
				}
			}
		}
	}
	dp[n - 1][m - 1].print();
}

