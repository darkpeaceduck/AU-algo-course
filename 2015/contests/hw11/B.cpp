
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
int n, suf[111111], suf2[111111], lcp[111111];
char s[111111];
int main(){
	ifstream cin("sufflcp.in");
	ofstream cout("sufflcp.out");
	cin >> n >> s;
	for (int i=0; i<n; i++) cin >> suf[i], suf[i]--, suf2[suf[i]]=i;
	for (int i=0, j=0; i<n; i++, j=max(j-1, 0)) if (suf2[i]) {
		int a=suf[suf2[i]-1];
		while(a+j<n&&i+j<n&&s[a+j]==s[i+j]) j++;
		lcp[suf2[i]]=j;
	}
	for (int i=1; i<n; i++) cout << lcp[i] << ' ';
	return 0;
}