
#include <bits/stdc++.h> 

using namespace std;
 
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define fst first
#define snd second
#define sz(x) (int) ((x).size()) 
#define forn(i, n) for (int i = 0; (i) < (n); ++i)
#define fornr(i, n) for (int i = (n) - 1; (i) >= 0; --i)
#define forab(i, a, b) for (int i = (a); (i) < (b); ++i)
#define forba(i, a, b) for (int i = (b) - 1; (i) >= (a); --i)
#define forit(it, c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define all(c) (c).begin(), (c).end() 

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) static_cast<void>(0)   
#endif

#ifdef _WIN32
	#define I64 "%I64d"
#else
	#define I64 "%lld"
#endif

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;
typedef vector <int> vi;
typedef pair <int, int> pii;

#define FNAME "roadtimes"

const int MAX_N = 1005, INF = 1e9, MAX_M = 1005;
const double INF_DBL = 1e300, EPS = 1e-8;

int d[MAX_N][MAX_N], pr[MAX_N][MAX_N], var[MAX_N][MAX_N], dist[MAX_N][MAX_N], used[MAX_N], p[MAX_N], p0[MAX_N];
int curVariable = 0;
int curRestriction = 0;
double a[MAX_N][MAX_N], b[MAX_N], c[MAX_N], aCopy[MAX_N][MAX_N], bCopy[MAX_N];

void addRestriction(vector<pair<int, double>> variables, double upperBound) {
	for (auto np : variables)
		a[curRestriction][np.fs] = np.sc;
	b[curRestriction++] = upperBound;
}

//n*m
//a, 0 < i1 < n, i2 >= n
void change(int i1, int i2, int n, int m) {
    double val = a[i1][i2];
    forn (i, m)
    	a[i1][i] /= val;
    b[i1] /= val;
    swap(a[i1][i1], a[i1][i2]);
    forn (i, n + 1)
    	if (i != i1) {
    	    double coef = a[i][i2];
    	    a[i][i2] = 0;
    		forab (j, n, m) {
    		 	a[i][j] -= a[i1][j] * coef;
    		}
    		if (i < n)
    			b[i] -= coef * b[i1];
    		else
    			a[n][m] += coef * b[i1];
    	}
	swap(p[i1], p[i2]);
}

void toStandard() {
	//change all x_i to x_i' - x_i''
 	forn (i, curRestriction)
 		forn (j, curVariable)
 			a[i][j + curVariable] = -a[i][j];
}

//canonical form ("= b")
//a=(E|C), n * m, n-th row -- function we want to maximize
double simplex(int n, int m) {
	while (1) {
	 	int indN = -1;
	 	forab (i, n, m)
	 		if (a[n][i] > EPS) {
				indN = i;
				break;
			}
		if (indN == -1)
			break;
		double curMin = INF_DBL;
		int indB = -1;
		forn (i, n)
			if (a[i][indN] > EPS && b[i] / a[i][indN] < curMin)
				curMin = b[i] / a[i][indN], indB = i;
		change(indB, indN, n, m); 			
	}
	double res = 0;
	forn (i, n)
		res += a[n][i] * b[i];
	return res + a[n][m];
}

//standard form ("<= b")
//a, n*m, n-th row -- function we want to maximize
pii initialize(int n, int m) {
    forn (i, n + 1) {
		for (int j = n + m - 1; j >= n; j--)
			a[i][j] = a[i][j - n];
		forn (j, n)
			a[i][j] = 0;
		if (i < n)
			a[i][i] = 1;
	}			 
    int minInd = 0;
	forab (i, 1, n)	 	
		if (b[i] < b[minInd])
			minInd = i;
	if (b[minInd] >= -EPS) {
		return mp(n, n + m);
	}
	forn (i, n)
		a[i][n + m] = -1;
	forn (i, n + m + 2)
		a[n][i] = 0;
	a[n][n + m] = -1;
	
	forn (i, n + m + 1)
		p[i] = i;
	
	change(minInd, n + m, n, n + m + 1);	
	simplex(n, n + m + 1);
	bool wasChange = 0;		    
	forn (i, n) 
		if (p[i] == n + m) {
			forab (j, n, n + m + 1)
		    	if (abs(a[i][j]) > EPS) {
		    	 	change(i, j, n, n + m + 1);
		    	 	wasChange = 1;
		    		break;
		    	}
			if (!wasChange) {
			 	forab (j, i, n + 1) {
			 		forn (g, n + m + 1)
			 			a[j][g] = a[j + 1][g];
			 		b[j] = b[j + 1];
			 	}
			 	forab (j, i, n + m + 1)
			 		forn (g, n)
			 			a[g][j] = a[g][j + 1];
			 	n--;
			}
		 	break;
		}
	if (wasChange) {
		forab (i, n, n + m + 1)
			if (p[i] == n + m) {
				forn (j, n + 1)
					swap(a[j][i], a[j][n + m]);
			    swap(p[i], p[n + m]);
			 	break;
			}
	}
	//now new variable is in last column
	return mp(n, n + m);
}

//standard form ("<= b")
double solve(int n, int m) {
 	auto nmPair = initialize(n, m);
 	return simplex(nmPair.fs, nmPair.sc);
}

int main() {
	freopen(FNAME".in", "r", stdin);
	freopen(FNAME".out", "w", stdout); 
    
    int n;
	scanf("%d", &n);
	forn (i, n)
		forn (j, n) {
			scanf("%d", &dist[i][j]);
			if (dist[i][j] == -1)
				dist[i][j] = INF;
			else if (i != j) {
				var[i][j] = curVariable;
				addRestriction({mp(curVariable, 1)}, 2 * dist[i][j]);
				addRestriction({mp(curVariable, -1)}, -dist[i][j]);
				curVariable++;
			}
		}	
	forn (i, n) {
	 	forn (j, n)
	 		used[j] = 0, d[i][j] = INF, pr[i][j] = -1;
	 	d[i][i] = 0;
		forn (j, n) {
			pii minDist = mp(INF, -1);
		 	forn (g, n)
		 		if (!used[g])
			 		minDist = min(minDist, mp(d[i][g], g));
			int ind = minDist.sc;
			used[ind] = 1;
			forn (g, n)
				if (!used[g] && d[i][ind] + dist[ind][g] < d[i][g])
					d[i][g] = d[i][ind] + dist[ind][g], pr[i][g] = ind;
		}
	}
	int r;
	scanf("%d", &r);
	forn (rr, r) {
		int v, u, t;
	 	scanf("%d%d%d", &v, &u, &t);
	 	vi variablesOnPath;
	 	while (u != v) {
	 	 	variablesOnPath.pb(var[pr[v][u]][u]);
	 	 	u = pr[v][u];
	 	}
	 	vector<pair<int, double>> variables;
	 	for (int v : variablesOnPath)
	 		variables.pb(mp(v, 1));
	 	addRestriction(variables, t);
	 	for (auto &np : variables)
	 		np.sc *= -1;
	 	addRestriction(variables, -t);
	}
	toStandard();
	int q;
	scanf("%d", &q);
 	auto nmPair = initialize(curRestriction, 2 * curVariable);
	int n0 = nmPair.fs, m0 = nmPair.sc;
	forn (i, n0) {
 		forn (j, m0)
 			aCopy[i][j] = a[i][j];
		bCopy[i] = b[i];
	}
	forn (i, m0)
		p0[i] = p[i];
    forn (qq, q) {
		int v, u;
	 	scanf("%d%d", &v, &u);
	 	printf("%d %d ", v, u);
	 	vi variablesOnPath;
	 	while (u != v) {
	 	 	variablesOnPath.pb(var[pr[v][u]][u]);
	 	 	u = pr[v][u];
	 	}
	 		
		forn (i, n0 + 1) {
			forn (j, m0 + 2)
				a[i][j] = aCopy[i][j];
			b[i] = bCopy[i];
		}
		forn (i, m0)
			c[i] = 0;	 	
		for (int var : variablesOnPath) {
	 		c[n0 + var] = -1;
	 		c[n0 + var + curVariable] = 1;
	 	}
	 	forn (i, n0) {
			double coef = c[p0[i]];
			forab (j, n0, m0)
				a[n0][j] -= coef * a[i][j];
			a[n0][m0] += coef * b[i];				 	
		}
		forab (i, n0, m0) 
	 		a[n0][i] += c[p0[i]];
	 	printf("%.20f ", -simplex(n0, m0));
		
		forn (i, n0 + 1) {
			forn (j, m0 + 2)
				a[i][j] = aCopy[i][j];
			b[i] = bCopy[i];
		}
		forn (i, m0)
			c[i] = 0;	 	
		for (int var : variablesOnPath) {
	 		c[n0 + var] = 1;
	 		c[n0 + var + curVariable] = -1;
	 	}
	 	forn (i, n0) {
			double coef = c[p0[i]];
			forab (j, n0, m0)
				a[n0][j] -= coef * a[i][j];
			a[n0][m0] += coef * b[i];				 	
		}
		forab (i, n0, m0) 
	 		a[n0][i] += c[p0[i]];
		printf("%.20f\n", simplex(n0, m0));
	}
	return 0;
}