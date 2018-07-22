
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>



#define INF 9000000001
#define eps 0.1
#define mp make_pair
#define pb push_back
#define pi 3.1415926535
//#define l long long double
#define eps2 0.000001

using namespace std;

double get(double f, double s)
{
	return sqrt(f * f + s * s);
}
int main()
{
freopen("unionday.in", "r", stdin);
freopen("unionday.out", "w", stdout);
	double n;
	cin  >> n;
	vector<pair<double, double> > my(n);
	double f, s;
	for (double i = 0 ; i < n ; i ++)
	{
		cin >> f >> s;
		my[i] = make_pair(f, s);
	}
	vector<bool> used(n, false);
	vector<double> mini(n, INF);
	mini[0] = 0;

	double v;
	double temp = 0;
	double sum = 0;
	for(double i = 0 ; i < n ; i ++)
	{
		v = -1;
		for (double j = 0 ; j < n; j ++)
		{
			if (!used[j] && (v == -1 || mini[j] < mini[v]))
			   v = j;
		}
		used[v] = true;
        sum += mini[v];
		for (double to = 0; to < n ; to ++)
		{
			temp = get(my[v].first - my[to].first, my[v].second - my[to].second);
			mini[to] = min(temp, mini[to]);

		}
	}
	cout <<fixed << setprecision(6)<< sum;
}
