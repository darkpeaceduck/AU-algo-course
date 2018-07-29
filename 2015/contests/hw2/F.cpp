
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pi 3.14159265358979323
#define eps 1e-6
#define MN 200000
#define FOR(i, n) for(int i = 0; i < (n); i++)
using namespace std;
const li INF= 2e18;
//===============================================
    static const int buf_size = 4096 ;
    inline  int fast_readchar() {
      static char buf[buf_size];
      static int len = 0, pos = 0;
      if (pos == len)
        pos = 0, len = fread(buf, 1, buf_size, stdin);
      if (pos == len)
        return -1;
      return buf[pos++];
    }

    inline  int readUInt() {
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

    inline   void fast_flush() {
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

//==============================================
struct nd
{
    bool is_cycle;
    int swapped;
    lo y, Sz, val;
    nd *l, *r, *p;
    nd() : p(NULL), is_cycle(false), swapped(0) {}
    nd(lo val) : val(val), Sz(1), l (NULL), r(NULL),
            p(NULL), is_cycle(false), swapped(0)
    {
    	srand(clock() ^ rand() *rand());
        y = rand();
    }
};
lo get_sz(nd * go)
{
    if (!go)
        return 0;
    return go->Sz;
}

void re_parent(nd * go){
    if(!go)
        return;
    if(go->l)
        go->l->p = go;
    if(go->r)
        go->r->p = go;
}

void upd(nd * go)
{
    if (!go)
        return;
    go->Sz = 1 + get_sz(go->l) + get_sz(go->r);
    re_parent(go);
}

void push(nd *go){
    if(!go)
        return;
    if(go->swapped)
        swap(go->l, go->r);
    if(go->l)
        go->l->swapped = (go->l->swapped + go->swapped) % 2;
    if(go->r)
        go->r->swapped = (go->r->swapped + go->swapped) % 2;
    go->swapped = 0;
}

void split(nd *go, nd *&l, nd *&r, lo cur, lo key)
{
    push(go);
    if (!go)
    {
        l = r = NULL;
        return;
    }
    //========================================
    go->p = NULL;
//    go->is_cycle = false;
    //===========================================
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
void merge(nd *&go, nd *l, nd *r)
{
    push(l);
    push(r);
    //=========================================
    if(l){
        l->p = NULL;
//        l->is_cycle = false;
    }
    if(r){
        r->p = NULL;
//        r->is_cycle = false;
    }
    //============================================
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

void ins_after(nd *&go, lo pos, lo value){
    nd *l, *r, *l2, *r2;
    split(go, l, r, 0, pos);
    merge(l, l, new nd(value));
    merge(go, l, r);
}
void insb(nd *&go, lo val)
{
    merge(go, go, new nd(val));
}
void insf(nd *&go, lo val)
{
    merge(go, new nd(val), go);
}
lo del(nd *&go, lo val)
{
    nd *l, *r, *l2, *r2;
    split(go, l, r, 0, val);
    split(r, l2, r2, 0, 1);
    merge(go, l, r2);
    return l2->val;
}
lo get_k(nd *go, lo cur, lo key)
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

void pre_push(nd * go){
	if(!go)
		return;
	pre_push(go->p);
	push(go);
}
lo get_id(nd * go, bool from, nd *&root, lo cur_l = 0, lo cur_r = 0){
    //!from = left, else = right
    if(!go)
        return cur_l;
    if(!go->p)
        root = go;

    if(!from){
        return get_id(go->p, go->p ? go->p->r == go : false, root,
            cur_l,
            cur_r + get_sz(go->r) + 1);
    }else{
        return get_id(go->p, go->p ? go->p->r == go : false, root,
            cur_l + get_sz(go->l) + 1,
            cur_r);
    }
}
void print(nd *go)
{
    push(go);
    if (!go)
        return;
    print(go->l);
    cerr << go->val << " ";
    print(go->r);
    upd(go);
}

void reverse(nd * go){
    push(go);
    go->swapped = 1;
    push(go);
}
//=====================================================

nd * ptr[MN];
int run_get_id(nd *go, nd *&root){
    if(!go)
        return 0;
    pre_push(go);
    return get_id(go, true, root);
}
void connect(int a, int b){
    nd *root_a = NULL, * root_b  = NULL;
    int a_id = run_get_id(ptr[a], root_a);
    int b_id = run_get_id(ptr[b], root_b);
    if(root_a == root_b){
        root_a->is_cycle = true;
    }else{
        if(a_id != 1 && b_id == 1)
            merge(root_a, root_a, root_b);
        else if(a_id == 1 && b_id != 1)
            merge(root_b, root_b, root_a);
        else if(a_id == 1 && b_id == 1){
            reverse(root_a);
            merge(root_a, root_a, root_b);
        }else{
            reverse(root_a);
            merge(root_b, root_b, root_a);
        }
    }
}

void remove(int a, int b){
    nd *root = NULL;
    int a_id = run_get_id(ptr[a], root);
    int b_id = run_get_id(ptr[b], root);
    if(a_id > b_id){
        swap(a, b);
        swap(a_id, b_id);
    }
    if(b_id == a_id + 1) {  // not cycle edge
        nd *l2 = NULL, * r2 = NULL;
        bool yep = root->is_cycle;
        split(root, l2, r2, 0, a_id);
        if(l2)
        	l2->is_cycle = false;
        if(r2)
        	r2->is_cycle = false;
        if(yep){
            reverse(l2);
            reverse(r2);
            merge(root, l2, r2);
            root->is_cycle = false;
        }
    }else {//cycle edge
        root->is_cycle = false;
    }
}

int query(int a, int b){
	if(a == b)
		return 0;
    nd *root_a = NULL, *root_b = NULL;
    int a_id = run_get_id(ptr[a], root_a);
    int b_id = run_get_id(ptr[b], root_b);
    if(a_id > b_id){
        swap(a, b);
        swap(a_id, b_id);
    }
    if(root_a != root_b)
        return -1;
    int val = b_id - a_id - 1;
    if(root_a->is_cycle){
        val = min(val, a_id + get_sz(root_a) - b_id - 1);
    }
    return val;
}


int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
#else
    freopen("roads.in", "r", stdin);
    freopen("roads.out", "w", stdout);
#endif
    int n, m, q;
    n = readInt();
    m = readInt();
    q = readInt();
//    cin >> n >> m >> q;
    FOR(i, n){
        ptr[i] = new nd(i);
    }
        nd * root;
    FOR(i, m){
        int a = readInt();
        int b = readInt();
        a--; b--;
        connect(a, b);
//      get_id(ptr[a], true, root);
//      print(root);
//      cerr << endl;
    }
//    cerr << get_id(ptr[0], true,root ) << endl;
//    cerr << get_id(ptr[3], true,root ) << endl;
    FOR(i, q){
        char c = fast_readchar();
        int a = readInt();
        int b = readInt();
        a--; b--;
        if(c == '?'){
            query(a, b);
            writeInt(query(a, b));
            fast_writechar('\n');
        }else if(c == '+'){
            connect(a, b);
        }else{
            remove(a, b);
        }
//      cerr << "==========" << endl;
    }
    fast_flush();

}
