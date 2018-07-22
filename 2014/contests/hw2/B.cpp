
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

#define ll lobng long int
using namespace std;

bool check(string s){
	vector<char > nex;
	map<char, char>  mapp{{'}','{'}, {']','['}, {')','('}};
	for(auto c : s){
		if(mapp.count(c)){
			if(nex.empty() || nex.back() != mapp[c]){
				return false;
			}
			nex.pop_back();
		} else {
			nex.push_back(c);
		}
	}
	return nex.empty();
}
int main()
{
#ifdef MYLOCAL
	freopen("input", "r", stdin);
#else
#define FILEI "check"
	freopen(FILEI ".in", "r", stdin);
	freopen(FILEI ".out", "w", stdout);
#endif
	string s;
	cin >> s;
	cout << (check(s) ? "YES" : "NO");
    return 0;
}
