
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cctype>
#include <cassert>
  
#define INF 900000000000001
#define mp make_pair
#define pb push_back
#define pi 3.1415926535
#define lo long long int
#define eps 0.00000001
using namespace std;
string s;
int o;
const bool comp(const int f,const int sec)
{
	o = max(f, sec);
	for(int i = 0; i < s.size() - o;i++)
	{
		if(s[f + i] < s[sec + i]) return true;
		if(s[f + i] > s[sec + i]) return false;
	}
	if(f > sec) return true;
	return false;
}
int main()
{
	freopen("suffarray.in", "r", stdin);
	freopen("suffarray.out", "w", stdout);
	getline(cin, s);
	vector<int> my(s.size());
	for(int i = 0; i < s.size(); i++) my[i] = i;
	sort(my.begin(), my.end(), comp);
	for(int i = 0; i < my.size(); i++) cout << my[i] + 1 << " ";
}