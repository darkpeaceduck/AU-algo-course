
#include <bits/stdc++.h>

using namespace std;

#define fpos asdlaskl

#define fpos asdlaskl

const int maxn = 5e5;

int len[maxn], link[maxn], cnt[maxn], used[maxn], fpos[maxn], check[maxn][2];
map<char, int> to[maxn];
int sz = 1, last;

void add_letter(char c)
{
    int p = last;
    last = sz++;
    len[last] = fpos[last] = len[p] + 1;
    for(; p != -1 && !to[p][c]; p = link[p]) to[p][c] = last;
    if(p == -1) return;
    int q = to[p][c];
    if(len[q] == len[p] + 1)
    {
        link[last] = q;
        return;
    }
    int cl = sz++;
    to[cl] = to[q];
    fpos[cl] = fpos[q];
    link[cl] = link[q];
    len[cl] = len[p] + 1;
    link[q] = link[last] = cl;
    for(; p != -1 && to[p][c] == q; p = link[p]) to[p][c] = cl;
}

void dfs(int x)
{
    if(used[x]) return;
    used[x] = 1;
    for(auto it: to[x])
    {
        if(it.first == '#')
        {
            check[x][0] = 1;
            continue;
        }
        if(it.first == '$')
        {
            check[x][1] = 1;
            continue;
        }
        dfs(it.second);
        check[x][0] |= check[it.second][0];
        check[x][1] |= check[it.second][1];
        cnt[x] += cnt[it.second];
    }
    cnt[x] += check[x][0] & check[x][1];
}

string rec(int x, int k)
{
    if(!k) return "";
    for(auto it: to[x])
    {
        k -= cnt[it.second];
        if(k <= 0)
        {
            k += cnt[it.second] - 1;
            return rec(it.second, k) + it.first;
        }
    }
}

#define TASK "common"
//#define LOCAL

main()
{
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    link[0] = -1;
    string a, b;
    cin >> a >> b;
    int k;
    cin >> k;
    for(auto c: a) add_letter(c);
    add_letter('#');
    for(auto c: b) add_letter(c);
    add_letter('$');
    dfs(0);
    string s = rec(0, k);
    reverse(s.begin(), s.end());
    cout << s << "\n";
    return 0;
}