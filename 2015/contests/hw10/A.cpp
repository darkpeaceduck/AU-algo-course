
//WOHOOOO I FOUND IT!
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

#define NAME "dictionary"

const int textLen = (int)1e6 + 10;
const int maxV = (int)1e5 + 10;
const int wordLen = 30;

int n, m, root = 0, vn = 1, nex[maxV][26];
char text[textLen], word[wordLen + 1];
int en[maxV], is[maxV];

void Add( char *s, int i )
{
  int v = root;
  while (*s)
  {
    int i = *s++ - 'a';
    assert(0 <= i && i < 26);
    if (!nex[v][i])
      assert(vn < maxV), nex[v][i] = vn++;
    v = nex[v][i];
  }
  en[v] = i + 1;
}

void add( char *s, int n )
{
  int v = root;
  forn(j, n)
  {
    v = nex[v][s[j] - 'a'];
    if (!v)
      break;
    is[en[v]] = 1;
  }
}

int main()
{
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  assert(gets(text));
  assert(scanf("%d ", &m) == 1);
  n = strlen(text);
  forn(i, m)
    gets(word), Add(word, i);
  forn(i, n)
    add(text + i, min(n - i, 30));
  forn(i, m)
    puts(is[i + 1] ? "Yes" : "No");
  return 0;
}
