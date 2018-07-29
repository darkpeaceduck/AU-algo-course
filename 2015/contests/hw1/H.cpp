
//#pragma comment(linker, "/STACK:100000000000000")
//#include <typeinfo>
#include <bits/stdc++.h>

#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pb push_back
#define FOR(i, n) for (lo (i) = 0; (i) < (n); (i)++)
#define all(a) (a).begin(), (a).end()
#define DEB(...) fprintf(stderr, __VA_ARGS__)
#define what_is(x) cerr << #x << " is " << x << endl;
#define sz(n) (lo) (n).size()
#define mt make_tuple
#define eb emplace_back
// #define pi 3.14159265358979323
#define eps 1e-7
#define MN 3000000
#define SM 32
const lo INF = 2e5;

using namespace std;


const int mod = 1e9 + 7;

inline int sum(int a, int b){
	return (a + b) % mod;
}


struct PersistentTreap
{
    short link;
    int size;
    long long sum, key;
    PersistentTreap *left, *right;
    PersistentTreap()
    {
        left = NULL;
        right = NULL;
        key = sum = 0;
        size = 0;
        link = 0;
    }
    PersistentTreap(PersistentTreap* cur)
    {
        if (!cur)
        {
            return;
        }
        left = cur->left;
        right = cur->right;
        sum = cur->sum;
        key = cur->key;
        size = cur->size;
        link = 0;
    }
    PersistentTreap(int x)
    {
        left = right = NULL;
        sum = key = x;
        size = 1;
        link = 0;
    }
    void del()
    {
        link--;
        if (link <= 0)
        {
            if (left != NULL)
                left->del();
            if (right != NULL)
                right->del();
            delete this;
        }
    }
};

typedef PersistentTreap * PtrPersistentTreap;
PtrPersistentTreap copy(PtrPersistentTreap cur){
	if(!cur)
		return NULL;
	return new PersistentTreap(cur);
}
void addLink(PtrPersistentTreap root)
{
    if (!root)
        return;
    root->link++;
}

lo get_sz(PtrPersistentTreap cur){
	return cur ? cur->size : 0;
}
lo get_sum(PtrPersistentTreap cur){
	return cur ? cur->sum : 0;
}
void update(PtrPersistentTreap cur){
	if(!cur)
		return;
	cur->size = 1 + get_sz(cur->left) + get_sz(cur->right);
	cur->sum = sum(cur->key, sum(get_sum(cur->left), get_sum(cur->right)));
}
void DelNode(PtrPersistentTreap root)
{
    if (!root)
        return;
    root->del();
}

void split(PtrPersistentTreap root, PtrPersistentTreap &L, PtrPersistentTreap &R, int size)
{
    if (!root)
    {
        L = R = NULL;
        return;
    }
    PtrPersistentTreap cur = new PersistentTreap(root);
    if (get_sz(cur->left) + 1 <= size)
    {
        split(cur->right, cur->right, R, size - get_sz(cur->left) - 1);
        addLink(cur->left);
        addLink(cur->right);
        L = cur;
    }
    else
    {
        split(cur->left, L, cur->left, size);
        addLink(cur->left);
        addLink(cur->right);
        R = cur;
    }
    update(L);
    update(R);
}

PtrPersistentTreap merge(PtrPersistentTreap L, PtrPersistentTreap R)
{
    PtrPersistentTreap ptrNode = NULL;
    if (!L || !R)
    {
        ptrNode = new PersistentTreap((!L ? R : L));
        addLink(ptrNode->left);
        addLink(ptrNode->right);
        return ptrNode;
    }
    int l = get_sz(L), r = get_sz(R), rang = rand() % (l + r);
    if (rang > r)
    {
        ptrNode = new PersistentTreap(L);
        ptrNode->right = merge(ptrNode->right, R);
        addLink(ptrNode->left);
        addLink(ptrNode->right);
        update(ptrNode);
        return ptrNode;
    }
    else
    {
        ptrNode = new PersistentTreap(R);
        ptrNode->left = merge(L, ptrNode->left);
        addLink(ptrNode->left);
        addLink(ptrNode->right);
        update(ptrNode);
        return ptrNode;
    }
}

void print_me(PtrPersistentTreap go)
{
	if (!go)
		return;
	print_me(go->left);
	cerr << go->key << " ";
	print_me(go->right);
}
class input{
public:
	void assign_stream(const char * filein, const char *fileout)
	{
		#ifdef MYLOCAL
		   freopen(NULL, "w", stdout);
		   freopen("input.txt", "r", stdin);
		#else
		 freopen(filein, "r", stdin);
		 freopen(fileout, "w",stdout);
		#endif
	}

	input(){
		string filename = "plist";
		assign_stream((filename + ".in").c_str(), (filename + ".out").c_str());
		read();
	}

	virtual ~input()
	{
		fclose(stdin);
		fclose(stdout);
	}
	//==============================================================

	void read()
	{
	}
};

class sol : public input{
public:
	vector<PtrPersistentTreap >begin, end;
	vector<int> btw;
	int n;
	int m;
	void norm(){
		if(get_sz(begin.back()) > m){
			PtrPersistentTreap temp = NULL, temp2 = NULL;
			split(begin.back(), temp, temp2, m);
			begin.back() = temp;
			if(btw.back() != -1)
				btw.back() = sum(max(0, btw.back()), get_sum(temp2));
			else
				end.back() = merge( temp2, end.back());
		}
		if(get_sz(end.back()) > m){
			PtrPersistentTreap temp = NULL, temp2 = NULL;
			split(end.back(), temp, temp2, get_sz(end.back()) - m);
			btw.back() = sum(max(0, btw.back()), get_sum(temp));
			end.back() = temp2;
		}
	}
	void print(){
		norm();
		printf("%d\n", sum(get_sum(begin.back()), sum(max(0, btw.back()), get_sum(end.back()))));
	}

	void deb_print(){
//		cerr << endl;
//		print_me(begin.back());
//		cerr << endl << btw.back() << endl;
//		print_me(end.back());
//		cerr << endl;
	}
	void solve()
	{
		cin >> n;
		FOR(i, n){
			int a;
			scanf("%d", &a);
			begin.pb(new PersistentTreap(a));
			end.pb(NULL);
			btw.pb(-1);
		}
		int q;
		cin >> q;
		m = 300000;
		FOR(i, q){
			scanf("\n");
			char s[10];
			int a, b;
			scanf("%s%d", s, &a);
			a--;
			if(strcmp(s, "merge") == 0){
				scanf("%d", &b);
				b--;
				if(!end[a] && !end[b]){
					begin.pb(merge( begin[a], begin[b]));
					btw.pb(-1);
					end.pb(NULL);
				}else if(!end[a]){
					begin.pb(merge(begin[a], begin[b]));
					btw.pb(btw[b]);
					end.pb(copy(end[b]));
				}else if(!end[b]){
					begin.pb(copy(begin[a]));
					btw.pb(btw[a]);
					end.pb(merge(end[a], begin[b]));
				}else{
					begin.pb(copy(begin[a]));
					btw.pb(sum(max(0, btw[a]), sum(get_sum(end[a]), sum(get_sum(begin[b]), max(0, btw[b])))));
					end.pb(copy(end[b]));
				}
				print();
			}
			else if(strcmp(s, "head") == 0){
				PtrPersistentTreap l= NULL, r = NULL;
				split(begin[a], l, r, 1);

				begin.pb(l);
				btw.pb(-1);
				end.pb(NULL);
				print();

				begin.pb(r);
				btw.pb(btw[a]);
				end.pb(copy(end[a]));
				print();

			}
			else{
				if(end[a]){
					PtrPersistentTreap l = NULL, r = NULL;
					split(end[a], l, r, get_sz(end[a]) - 1);
					begin.pb(copy(begin[a]));
					btw.pb(btw[a]);
					end.pb(l);
					print();

					begin.pb(r);
					btw.pb(-1);
					end.pb(NULL);
					print();
				}else{
					PtrPersistentTreap l = NULL, r = NULL;
					split(begin[a], l, r, get_sz(begin[a]) - 1);
					begin.pb(l);
					btw.pb(-1);
					end.pb(NULL);
					print();

					begin.pb(r);
					btw.pb(-1);
					end.pb(NULL);
					print();
				}

			}
		}
	}
};
int main()
{
   (sol()).solve();
}
