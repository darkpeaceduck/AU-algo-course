
#include <iostream>
#include <string>
#include <map>
#include <math.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#include <queue>
#include <sstream>
#include <deque>
#include <memory.h>
#include <cassert>
#include <ctime>


using namespace std;

#define ll long long
#define y1 _dfdfdfd



const int maxn = 100100;
const int inf = 1e9 + 7;

int n, m;
vector<int> a;
vector<int> cnt, p, pn, c, cn, lcp, o;

void print(vector<int> v) {
    for (int i = 0; i < (int)v.size(); i++) cout << v[i] << " \n"[i + 1 == (int)v.size()];
}

void getsuffixarray() {
    cnt.assign(m + 1, 0);
    p.assign(n, 0);
    pn.assign(n, 0);
    c.assign(n, 0);
    cn.assign(n, 0);
    o.assign(n, 0);
    lcp.assign(n, 0);
    
    for (int i = 0; i < n; i++) cnt[a[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) p[--cnt[a[i]]] = i;
    
    int cc = 1;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        cc += a[p[i]] != a[p[i - 1]];
        c[p[i]] = cc - 1;
    }
    
    for (int len = 1; len < n; len <<= 1) {
        cnt.assign(cc, 0);
        for (int i = 0; i < n; i++) {
            cnt[c[i]]++;
            pn[i] = (p[i] - len + n) % n;
        }
        for (int i = 1; i < cc; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        
        cc = 1;
        cn[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            cc += c[p[i]] != c[p[i - 1]] || c[(p[i] + len) % n] != c[(p[i - 1] + len) % n];
            cn[p[i]] = cc - 1;
        }
        c = cn;
    }

    for (int i = 0; i < n; i++) o[p[i]] = i;
    int z = 0;
    for (int i = 0; i < n - 1; i++) {
        int j = o[i];
        if (j == n - 1) {
            lcp[j] = z = 0;
        } else {
            while (a[i + z] == a[p[j + 1] + z]) z++;
            lcp[j] = z;
            z -= !!z;
        }
    }
}

int main() {
    freopen("refrain.in", "r", stdin);
    freopen("refrain.out", "w", stdout);
    
    cin >> n >> m;
    a.resize(n + 1);
    for (int i = 0; i < n; i++) cin >> a[i];
    a[n++] = 0;
    getsuffixarray();
    
    int len = n - 1, cnt = 1, pos = 0;
    vector<pair<int, int> > v;
    lcp.push_back(-1);
    v.push_back(make_pair(-2, -1));
    for (int i = 0; i <= n; i++) {
        while (v.back().first >= lcp[i]) {
            int nlen = v.back().first;
            v.pop_back();
            int ncnt = i - v.back().second;
            int npos = p[i];
            if (1LL * nlen * ncnt > 1LL * len * cnt) {
                len = nlen;
                cnt = ncnt;
                pos = npos;
            }
        }
        v.push_back(make_pair(lcp[i], i));
    }
    
    cout << 1LL * len * cnt << endl << len << endl;
    for (int i = pos; i < pos + len; i++) cout << a[i] << " \n"[i + 1 == pos + len];
    
    return 0;
}