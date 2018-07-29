
#pragma comment(linker, "/STACK:100000000000000")
#include <bits/stdc++.h>
//#include <unordered_map>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pi 3.14159265358979323
#define eps 1e-6
#define MN 200000
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FORI(i, a, b) for(int i = (a); i < b; i++)
#define sz(a) (int)(a).size()
using namespace std;
const li INF= 2e9;


const int simb = 'j' - 'a' + 1;
const int mod = 1e9 + 7;

inline int sum(int a, int b){
	return (a + b) % mod;
}

inline int mult(li a, li b){
	return (a * b) % mod;
}
inline int sum_simb(int a, int b){
	return (a + b) % simb;
}

int fac[MN];

inline int binpow(int a, int b){
	if(!b)
		return 1;
	if(b & 1){
		return mult(a, binpow(a, b - 1));
	}
	int val = binpow(a, b / 2);
	return mult(val, val);
}
bool ya = false;
inline void cntC(){
	if(!ya)
	{
		fac[0] = 1;
		for(int i = 1; i < MN;i++){
			fac[i] = mult(i, fac[i - 1]);
		}
	}
	ya = true;
}


inline int C(int a, int b)
{
	return mult(fac[a], mult(binpow(fac[b], mod - 2),
			binpow(fac[a - b], mod - 2)));
}

struct nd
{
	lo y, Sz, val;
	nd *l, *r;
	vector<int> cnt;
	int swapped;
	int change;
	nd() {}
	nd(lo val) : val(val), Sz(1), l (NULL), r(NULL),
			swapped(0), change(0)
	{
		y = rand();
		cnt = vector<int>(simb, 0);
		cnt[val]++;
	}
};

inline void push(nd *& go){
	if(!go)
		return;
	if(go->change){
	go->val = sum_simb(go->val, go->change);
	vector<int> temp = go->cnt;
	for(int i = 0; i < (int)temp.size(); i++){
		go->cnt[sum_simb(i, go->change)] = temp[i];
	}
	}

	if(go->swapped)
		swap(go->l, go->r);
	if(go->l)
		go->l->swapped = (go->l->swapped + go->swapped) % 2,
		go->l->change = sum_simb(go->l->change, go->change);
	if(go->r)
		go->r->swapped = (go->r->swapped + go->swapped) % 2,
		go->r->change = sum_simb(go->r->change, go->change);
	go->swapped = 0;
	go->change = 0;
}

inline lo get_sz(nd * go)
{
	push(go);
	if (!go)
		return 0;
	return go->Sz;
}

inline lo get_cnt(nd *go, lo id){
	push(go);
	if(!go)
		return 0;
	return go->cnt[id];
}

inline lo get_perm(nd *&go){
	push(go);
	cntC();
	int delta = get_sz(go);
	int ans = 1;
	FOR(i, sz(go->cnt)){
		ans = mult(ans, C(delta, go->cnt[i]));
		delta -= go->cnt[i];
	}
	return ans;
}



inline void upd(nd *& go)
{
	if (!go)
		return;
	go->Sz = 1 + get_sz(go->l) + get_sz(go->r);
	go->cnt = vector<int>(simb, 0);
	go->cnt[go->val]++;
	if(go->l || go->r)
	{
		for(int i = 0; i < (int)go->cnt.size(); i++){
			go->cnt[i] = sum(go->cnt[i], sum(get_cnt(go->l, i),
					get_cnt(go->r, i)));
		}
	}
}
inline void split(nd *go, nd *&l, nd *&r, lo cur, lo key)
{
	push(go);
	if (!go)
	{
		l = r = NULL;
		return;
	}
	lo with = cur + get_sz(go->l);
	if (with < key)
	{
		split(go->r, go->r, r, with + 1, key);
		l = go;
	}
	else
	{
		split(go->l, l, go->l, cur, key);
		r = go;
	}
	upd(l);
	upd(r);
}
inline void merge(nd *&go, nd *l, nd *r)
{
	push(go);
	if (!l || !r)
	{
		go = l ? l : r;
		return;
	}
	if (l->y > r->y)
	{
		merge(l->r, l->r, r);
		go = l;
	}
	else
	{
		merge(r->l, l, r->l);
		go = r;
	}
	upd(go);
}

inline void ins_after(nd *&go, lo pos, lo value){
	nd *l, *r, *l2, *r2;
	split(go, l, r, 0, pos);
	merge(l, l, new nd(value));
	merge(go, l, r);
}
inline void insb(nd *&go, lo val)
{
	merge(go, go, new nd(val));
}
void insf(nd *&go, lo val)
{
	merge(go, new nd(val), go);
}
inline lo del(nd *&go, lo val)
{
	nd *l, *r, *l2, *r2;
	split(go, l, r, 0, val);
	split(r, l2, r2, 0, 1);
	merge(go, l, r2);
	return l2->val;
}
inline lo get_k(nd *go, lo cur, lo key)
{
	lo with = cur + get_sz(go->l);
	if (with == key)
	{
		return go->val;
	}
	if (with < key)
	{
		return get_k(go->r, with + 1, key);
	}
	return get_k(go->l, cur, key);
}
void print(nd *go)
{
	push(go);
	if (!go)
		return;
	print(go->l);
//	cerr << go->val << " ";
	print(go->r);
}

inline int readInt();
inline int readUInt();
inline void readWord( char *s );
inline int fast_readchar(); // you may use readchar() instead of it

inline void writeInt( int x );
inline void fast_writechar( int x ); // you may use putchar() instead of it
inline void writeWord( const char *s );
inline void fast_flush();

int main()
{
#ifdef MYLOCAL
	freopen("input.txt", "r", stdin);
#else
	freopen("permutations.in", "r", stdin);
	freopen("permutations.out", "w", stdout);
#endif
	int n;
	nd * now = NULL;
	n = readInt();
	FOR(i, n)
	{
		char c= fast_readchar();
		int add = (c -'a');
		insb(now, add);
	}
	n = readInt();
	FOR(i, n){
		int t, a, b, c;
		t = readInt();
		a = readInt();
		b = readInt();
		nd *l, *r, *l2, *r2;
		split(now, l, r, 0, a - 1);
		split(r, l2, r2, 0, b - a + 1);
		if(t == -1){
			l2->swapped = (l2->swapped + 1) % 2;
		}
		else if(t == 0){
			c = readInt();
			l2->change = sum_simb(l2->change, c);
		}
		else
		{
			int ans = get_perm(l2);
			writeInt(ans);
			fast_writechar('\n');
			fast_flush();
		}
		push(l2);
		merge(r, l2, r2);
		merge(now, l, r);
//		print(now);
//		cerr << endl;
	}
}

static const int buf_size = 4096;

inline int fast_readchar() {
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len)
    pos = 0, len = fread(buf, 1, buf_size, stdin);
  if (pos == len)
    return -1;
  return buf[pos++];
}

inline int readUInt() {
  int c = fast_readchar(), x = 0;
  while (c <= 32)
    c = fast_readchar();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = fast_readchar();
  return x;
}

inline int readInt() {
  int s = 1, c = fast_readchar();
  int x = 0;
  while (c <= 32)
    c = fast_readchar();
  if (c == '-')
    s = -1, c = fast_readchar();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = fast_readchar();
  return x * s;
}

inline void readWord( char *s ) {
  int c = fast_readchar();
  while (c <= 32)
    c = fast_readchar();
  while (c > 32)
    *s++ = c, c = fast_readchar();
  *s = 0;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void fast_writechar( int x ) {
  if (write_pos == buf_size)
    fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
  write_buf[write_pos++] = x;
}

inline void fast_flush() {
  if (write_pos)
    fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
}

inline void writeInt( int x ) {
  if (x < 0)
    fast_writechar('-'), x = -x;

  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    fast_writechar(s[n]);
}

inline void writeWord( const char *s ) {
  while (*s)
    fast_writechar(*s++);
}



