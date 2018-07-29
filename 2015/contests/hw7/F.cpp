
#pragma comment(linker, "/STACK:100000000000000")
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
#include <ctime>
#define mp make_pair
#define pb push_back
#define lo int
//#define pi 3.14159265358979323
#define eps 1e-4
#define MN 1500
using namespace std;
const lo INF= 2e8;
//1
struct edge
{
   lo to, flow, maxflow, re;
   edge(lo to, lo flow, lo maxflow, lo re):to(to), flow(flow), maxflow(maxflow), re(re){};
   edge(){};
};
vector<vector<edge> > g;
void add_edge(lo v, lo to, lo maxflow)
{
   lo sz = g[v].size(), sz2 = g[to].size();
   g[v].push_back(edge(to, 0, maxflow, sz2));
   g[to].push_back(edge(v, 0, 0, sz));
}
void erase_edge(lo v, lo s)
{
    for(lo i = 0; i < (lo)g[v].size(); i++)
    {
        lo to = g[v][i].to;
        if(to == s)
        {
            lo re = g[v][i].re;
            g[s].erase(g[s].begin() + re);
            g[v].erase(g[v].begin() + i);
            break;
        }
    }
}
lo d[MN * MN], ids[MN * MN];
bool bfs(lo id, lo st, lo x)
{
   lo n = (lo) g.size();
   for(lo i = 0; i < n; i++)
   {
       d[i] = -1;
   }
   queue<lo> q;
   q.push(id);
   d[id] = 0;
   while(!q.empty())
   {
       lo now = q.front();
       q.pop();
       for(lo i = 0; i < (lo) g[now].size(); i++)
       {
           if(g[now][i].maxflow - g[now][i].flow < x) continue;
           lo to = g[now][i].to;
           if(d[to] == -1)
           {
               d[to] = d[now] + 1;
               q.push(to);
           }
       }
   }
   return d[st] != -1;
}
lo dfs(lo id, lo st, lo x, lo flow)
{
   if(!flow) return 0;
   if(id == st) return flow;
   for(; ids[id] < (lo) g[id].size(); ids[id]++)
   {
       lo i = ids[id], to = g[id][i].to;
       if(g[id][i].maxflow - g[id][i].flow < x || d[to] != d[id] + 1) continue;
       lo is = dfs(to, st, x, min(flow, g[id][i].maxflow - g[id][i].flow));
       if(is)
       {
          g[id][i].flow += is;
          g[to][g[id][i].re].flow -= is;
          return is;
       }
   }
   return 0;
}
lo try_din(lo s, lo t)
{
   lo ans = 0;
   for(lo x = (1LL << 25); x > 0; x /= 2)
   {
       if(!bfs(s, t, x)) continue;
       for(lo i = 0; i < (lo) g.size(); i++)
       {
           ids[i] = 0;
       }
       while(true)
       {
           lo te = dfs(s, t, x, INF);
           ans += te;
           if(!te)
           {
               x*= 2;
               break;
           }
       }
   }
   return ans;
}

const pair<lo, lo> gone[4] = {mp(0, 1), mp(1, 0),mp(-1, 0), mp(-1, 0)};
lo ma[MN][MN], ma2[MN][MN], color[MN * MN];
lo n, m, rocks, cans;
vector<pair<lo, lo> > outer;

void paint(lo id, lo col)
{
   color[id] = col;
   for(lo i = 0; i < (lo) g[id].size(); i++)
   {
       if(g[id][i].flow == g[id][i].maxflow)
           continue;
       lo to = g[id][i].to;
       if(color[to] != col)
           paint(to, col);
   }

}

void re_ans()
{
    outer.clear();
    memset(color, 0, sizeof color);
    paint(0, 1);
    //paint((lo) g.size() - 1, 2);
    for(lo i = 1; i < (lo) g.size() - 1; i++)
    {
        for(lo j = 0; j < (lo) g[i].size(); j++)
        {
            if(g[i][j].flow == g[i][j].maxflow && g[i][j].maxflow && color[i] != color[g[i][j].to])
            {
                lo x = ((i - 1) / 2) / m;
                lo y = ((i - 1) / 2) % m;
                outer.push_back(mp(x, y));
            }
        }
    }
}

void clear_and_build(lo to_s,lo to_t, lo fl1)
{
    //erase
    if((lo) g[0].size())
        erase_edge(0, g[0][0].to);
    for(lo i = 0; i < (lo) g.size(); i++)
    {
        for(lo j = 0; j < (lo) g[i].size(); j++)
        {
            lo to = g[i][j].to;
            g[i][j].flow = 0;
            if(to == (lo) g.size() - 1)
            {
                erase_edge(i, (lo) g.size() - 1);
                j--;
            }
        }
    }
    //go
    add_edge(0, to_s, fl1);
    add_edge(to_t, (lo) g.size() - 1, INF);
}
int main()
{
   assert((freopen("wall.in", "r", stdin)) != NULL);
   assert((freopen("wall.out", "w", stdout)) != NULL);

   cin >> n >> m >> rocks >> cans;

   memset(ma, 0, sizeof ma);
   memset(ma2, 0, sizeof ma2);

   for(lo i = 0; i < rocks; i++)
   {
       lo a, b;
       cin >> a >> b;
       a--;
       b--;
       ma[a][b]++;
   }

   for(lo i = 0 ;i < cans; i++)
   {
       lo a, b;
       cin >> a >> b;
       a--;
       b--;
       if(ma[a][b])
           continue;
       ma2[a][b]++;
   }

   lo ax, ay, bx, by;
   cin >> ax >> ay >> bx >> by;
   ax--;
   ay--;
   bx--;
   by--;
   g.resize(n * m * 2 + 20 );


   for(lo i = 0; i < n; i++)
   {
       for(lo j = 0; j < m; j++)
       {
           if(ma[i][j])
               continue;
           lo fr_id = 2 + (i * m + j) * 2;
           for(lo k = 0; k < 2; k++)
           {
               lo tox = i + gone[k].first;
               lo toy = j + gone[k].second;
               if(tox >= 0 && toy >= 0 && tox < n && toy < m && !ma[tox][toy])
               {
                   lo flow = INF;
                   lo to_id = 1 + (tox * m + toy) * 2;
                   add_edge(fr_id, to_id, flow);
                   add_edge(to_id + 1, fr_id - 1, flow);
               }
           }
           if(ma2[i][j])
               add_edge(fr_id - 1, fr_id, 1);
           else
               add_edge(fr_id - 1, fr_id, INF);
       }
   }

   lo a = 1 + (ax * m + ay) * 2;
   lo b = 1 + (bx * m + by) * 2;
   vector<pair<lo, lo> > f, s;
   //1
   clear_and_build(a, b + 1, INF);
   lo fl1 = try_din(0, (lo) g.size() - 1);
   re_ans();
   f = outer;
   //2
   clear_and_build(b, a + 1, INF);
   lo fl2 = try_din(0, (lo) g.size() - 1);
   outer.clear();
   re_ans();
   s = outer;

   if(fl1 == fl2 && fl1 == INF)
   {
       cout << -1;
       return 0;
   }

   if(f.size() > s.size())
       f = s;

   cout << (lo) f.size() << endl;

   for(lo i = 0; i < (lo) f.size(); i++)
   {
       cout << f[i].first + 1 << " " << f[i].second + 1 << endl;
   }
   return 0;
}

