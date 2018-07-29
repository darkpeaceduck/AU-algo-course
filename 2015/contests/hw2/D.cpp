
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <string.h>
#include <string>

using namespace std;

struct node
{
   node *l, *r;
   int x, size;
   __int64 sum;
   void upd();
};

const int MAXN = 1e6 + 10;
const int MAXM = 5e6;
int n, k, cnt, X, A, B, M, l, r, len, p;
__int64 a[MAXN];
node nodes[MAXM];
node *root, *L, *C, *R;
char s[12];
bool sign;

node* new_node(int x, node *l, node *r)
{
   nodes[cnt].x = x;
   nodes[cnt].l = l;
   nodes[cnt].r = r;
   nodes[cnt].upd();
   return &nodes[cnt++];
}

void node::upd()
{
   size = (l ? l->size : 0) + (r ? r->size : 0) + 1;
   sum = (l ? l->sum : 0) + (r ? r->sum : 0) + x;
}

int readChar()
{
   int c = 0;
   do
       c = getchar();
   while (c <= 32);
   return c;
}

void printInt64(__int64 x)
{
   int n = 0;
   s[n++] = '\n';
   sign = 0;
   if (x < 0) sign = 1, x *= -1;
   if (x == 0) s[n++] = '0';
   while (x)
       s[n++] = '0' + x % 10, x /= 10;
   if (sign) s[n++] = '-';
   while (n--)
       putchar(s[n]);
}

__int64 readInt64()
{
   __int64 x = 0;
   int c = readChar();
   sign = 0;
   if (c == '-') sign = 1, c = readChar();
   for (; c >= '0' && c <= '9'; c = getchar())
       x = x * 10 + c - '0';
   if (sign) x *= -1;
   return x;
}


node* merge(node* l, node *r)
{
   if (!l || !r)
       return l ? l : r;
   int size1 = l->size;
   int size2 = r->size;
   if (rand() % (size1 + size2) < size1)
       return new_node(l->x, l->l, merge(l->r, r));
   else
       return new_node(r->x, merge(l, r->l), r->r);
}

void split(node* t, int x, node* &l, node* &r)
{
   if (!t)
       l = r = NULL;
   else
   {
       node* v = new_node(t->x, t->l, t->r);
       if (x <= (v->l ? v->l->size : 0))
       {
           split(v->l, x, l, v->l);
           r = v;
       }
       else
       {
           split(v->r, x - (v->l ? v->l->size : 0) - 1, v->r, r);
           l = v;
       }
       v->upd();
   }
}

void print(node* t)
{
   if (!t) return;
   print(t->l);
   if (++p == 1)
       printf("%d", t->x);
   else
       printf(" %d", t->x);
   print(t->r);
}

void restore(node* t)
{
   if (!t) return;
   restore(t->l);
   a[cnt++] = t->x;
   restore(t->r);
}

node* get(int l, int len)
{
   split(root, l - 1, L, R);
   split(R, len, C, R);
   return C;
}

node* build(int l, int r)
{
   if (l > r) return NULL;
   int m = l + (r - l) / 2;
   return new_node(a[m], build(l, m - 1), build(m + 1, r));
}

void cpy(int l, int r, int len)
{
   node* v = get(l, len);
   get(r, len);
   root = merge(merge(L, v), R);
}

int main()
{
   freopen("memory.in", "r", stdin);
   freopen("memory.out", "w", stdout);
   scanf("%d", &n);
   scanf("%d %d %d %d", &X, &A, &B, &M);
   a[0] = X;
   for (int i = 1; i < n; ++i)
       a[i] = (A * a[i - 1] * 1LL + B) % M;
   root = build(0, n - 1);
   scanf("%d", &k);
   while (k--)
   {
       scanf("%s %d %d", s, &l, &r);
       if (strcmp(s, "cpy") == 0)
       {
           scanf("%d", &len);
           cpy(l, r, len);
       }
       else
       {
           node* v = get(l, r - l + 1);
           if (strcmp(s, "out") == 0)
               print(v), p = 0, printf("\n");
           else
               printf("%I64d\n", v ? v->sum : 0);
       }
       if (MAXM - cnt < 3e2)
       {
           cnt = 0;
           restore(root);
           cnt = 0;
           root = build(0, n - 1);
       }
   }
}
