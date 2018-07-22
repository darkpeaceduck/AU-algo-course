
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

#define INF -90000000
#define mp make_pair
#define pb push_back
#define lo intng intng int
#define pi 3.141592653589793238
#define eps 0.00000001
#define MN 100
using namespace std;
int main()
{
    freopen("casino.in", "r", stdin);
    freopen("casino.out", "w", stdout);
    int k0, n, w;
    string s, t;
    cin >> k0;
    vector<int> sol(30, 0);
    char c;
    for(int i = 0; i < k0; i++)
    {
        cin >> c >> w;
        sol[c - 'a'] = w;
    }
    cin >> s;
    cin >> n;
    vector<int> fo(n, 0);
    vector< vector< pair<int, int> > > pos(30);
    vector<string> str(n);
    for(int i = 0; i < n; i++)
    {
        cin >> t;
        for(int j = 0; j < t.size(); j++)
        {
            fo[i] += (sol[t[j] - 'a']);
            pos[t[j] - 'a'].push_back(mp(i, j));
        }
        str[i] = t;
    }
    vector<vector<vector<vector<int> > > > d(n, vector<vector<vector<int> > > (s.size(), vector<vector<int> > (s.size())));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < s.size(); j++)
            for(int k = 0; k < s.size(); k++)
            {
                d[i][j][k].resize(str[i].size(), -1);
            }
    vector<int> all(s.size(), 0);
    int num, id, val, to, num1, id1, ans = 0;
    for(int i = 0; i < s.size(); i++)
    {
        int k = s[i] - 'a';
        //1
        all[i] = ans;
        for(int beg = 0; beg <= i; beg++)
        {
                for(int q = 0; q < pos[k].size(); q++)
                {
                    num = pos[k][q].first;
                    id = pos[k][q].second;
                    if(id == 0 && beg == i)
                    {
                        d[num][i][beg][id] = 0;
                    }
                    else if(i > 0 && id > 0  && d[num][i - 1][beg][id - 1] > -1)
                    {
                        d[num][i][beg][id] = max(d[num][i][beg][id], d[num][i - 1][beg][id - 1]);
                    }
                    if(i > 0 && id == str[num].size() - 1 && d[num][i][beg][id] > -1)
                    {
                        d[num][i][beg][id] += fo[num];
                        val = d[num][i][beg][id];
                        all[i] = max(all[i], d[num][i][beg][id] + (beg == 0 ? 0 :all[beg - 1]));
                        if(beg == 0) continue;
                        to = beg - 1;
                        for(int k1 = 0 ; k1 < pos.size(); k1++)
                        {
                            for(int q1 = 0; q1 < pos[k1].size(); q1++)
                            {
                                num1 = pos[k1][q1].first;
                                id1 = pos[k1][q1].second;
                                for(int beg1 = 0; beg1 <= to; beg1++)
                                {
                                    if(d[num1][to][beg1][id1] > -1)
                                    {
                                        d[num1][i][beg1][id1] = max(d[num1][i][beg1][id1], d[num1][to][beg1][id1] + val);
                                    }
                                }
                            }
                        }
                    }
                }
        }
        ans = max(ans, all[i]);
    }
    cout << ans;
}
