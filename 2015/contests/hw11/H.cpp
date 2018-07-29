
#include <bits/stdc++.h>
using namespace std;

#define TASK "suffix"

struct suffix_automaton
{
	struct state
	{
		int len=0, link=-1, is_term=0;
		map<int,int> to;
	};
	
	vector<state> st;
	int last=0,sz=1;
	
	void add_letter(int c)
	{
		int cur=sz++;
		int p=last;
		last=cur;
		st[cur].len=st[p].len+1;
		for(;p!=-1 && !st[p].to[c];p=st[p].link) st[p].to[c]=cur;
		if(p==-1)
		{
			st[cur].link=0;
			return;
		}
		int q=st[p].to[c];
		if(st[q].len==st[p].len+1)
		{
			st[cur].link=q;
			return;
		}
		int cl=sz++;
		st[cl]=st[q];
		st[cl].len=st[p].len+1;
		st[q].link=st[cur].link=cl;
		for(;p!=-1 && st[p].to[c]==q;p=st[p].link) st[p].to[c]=cl;
	}
	
	void build(string s)
	{
		int n=s.size();
		st.resize(3*n+5);
		for(int i=0;i<n;i++)
			add_letter(s[i]);
		while(last!=-1)
			st[last].is_term=1, last=st[last].link;
	}
};

bool on_c(int x, vector<map<int,int>> &G, vector<int> &used, vector<int> &on_cycle)
{
	if(used[x]==1) return 0;
	if(used[x]==2) return 1;
	used[x]=1;
	for(auto it:G[x])
	{
		if(!on_c(it.second,G,used,on_cycle)) 
		{
			on_cycle[it.second]=1;
		}
	}
	used[x]=2;
	return 1;
}

int pre_dfs(int x, vector<map<int,int>> &G, vector<int> &used, vector<int> &is_term, vector<int> &cnt)
{
	if(used[x]) return cnt[x];
	int ret=is_term[x];
	used[x]=1;
	vector<pair<int,int>> to_er;
	for(auto it:G[x])
	{
		int pl=pre_dfs(it.second,G,used,is_term,cnt);
		if(!pl) to_er.push_back(it);
		ret+=pl;
	}
	for(auto it:to_er)
	{
		G[x].erase(it.first);
	}
	return cnt[x]=ret;
}

bool dfs(int x,int y, vector<map<int,int>> &G, suffix_automaton &me, vector<int> &is_term, vector<int> &corr, vector<int> &used,vector<int> &cnt, vector<int> &on_cycle)
{
	if(on_cycle[x] && cnt[x]) return 0;
	if(used[x])
		if(corr[x]==y) return 1;
		else return 0;
	used[x]=1;
	corr[x]=y;
	if(G[x].size()!=me.st[y].to.size()) return 0;
	for(auto it:G[x])
	{
		if(!me.st[y].to[it.first]) return 0;
		if(!dfs(it.second, me.st[y].to[it.first], G, me, is_term, corr, used,cnt,on_cycle)) return 0;
	}
	if(is_term[x] ^ me.st[y].is_term) return 0;
	return 1;
}

int main ()
{
  freopen (TASK ".in", "r", stdin);
  freopen(TASK ".out","w",stdout); 
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n,m,t;
  int cnt=0;
  while(cin>>n>>m>>t)
  {
	  if(n==0 && m==0 && t==0) return 0;
	  vector<int> is_term(n);
	  for(int i=0;i<t;i++) 
	  {
		  int t;
		  cin>>t;
		  t--;
		  is_term[t]=1;
	  }
	  vector<map<int,int>> G(n);
	  for(int i=0;i<m;i++)
	  {
		  int a,b;
		  char c;
		  cin>>a>>b>>c;
		  a--, b--;
		  G[a][c]=b;
	  }
	  string s;
	  cin>>s;
	  suffix_automaton me;
	  me.build(s);
	  vector<int> corr(n), used(n), USED(n),ct(n),on_cycle(n);
	  on_c(0,G,USED,on_cycle);
	  USED.assign(n,0);
	  pre_dfs(0,G,USED,is_term, ct);
	  int t = bool(ct[0]-1==s.size());
	  if(t && dfs(0,0,G,me,is_term,corr,used,ct,on_cycle))
		cout<<"Automaton "<<++cnt<<" is a machinegun."<<endl;
	else
		cout<<"Automaton "<<++cnt<<" is not a machinegun."<<endl;
  }
  
  
  return 0;
}