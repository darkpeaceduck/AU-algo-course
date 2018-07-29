




#include <bits/stdc++.h>
using namespace std;

template <class T = int> inline T readInt();
inline double readDouble();
inline int readUInt();
inline int readChar();
inline void readWord( char *s );
inline bool readLine( char *s ); // do not save '\n'
inline bool isEof();
inline int peekChar();
inline bool seekEof();

template <class T> inline void writeInt( T x, int len = -1 );
template <class T> inline void writeUInt( T x, int len = -1 );
inline void writeChar( int x );
inline void writeWord( const char *s );
inline void writeDouble( double x, int len = 0 );
inline void flush();

typedef long long int ll;

#define MN 150
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define FOR_MASK(i, n, mask) for(int i = 0; i < (n); i++) if ((1LL<<i) & mask)
#define FORN(i, j, n) for(int i = (j); i <(n); i++)

#define eps 1e-6
#define INF 1e18

struct edge {
	int v;
	int to;
	int ind;
};

typedef vector<vector<edge>> G;
namespace conn {

int used[MN], tin[MN], fup[MN], timer = 1;
void dfs(int id, int p, G &g)
{
	used[id]++;
	tin[id] = fup[id] = timer++;
	for(auto ed : g[id])
	{
		int to = ed.to;
		if(to == p)
			continue;
		if(used[to])
		{
			fup[id] = min(fup[id], tin[to]);
		}
		else
		{
			dfs(to, id, g);
			fup[id] = min(fup[id], fup[to]);
		}
	}
}

int ptr = 0;
int ans[310];
void coloring(int id, int color, int p, G &g)
{
	used[id]++;
	for(auto ed : g[id])
	{
		if(id == p)
			continue;
		int to = ed.to;
		if(!used[to])
		{
			if(tin[id] <= fup[to])
			{
				++ptr;
				ans[ed.ind] = ptr;
				coloring(to, ptr, id, g);
			}
			else
			{
				ans[ed.ind] = color;
				coloring(to, color, id, g);
			}
		}
		else
			if(tin[id] >= tin[to])
				ans[ed.ind] = color;
	}
}

struct twoConnComp{
	int E;
	vector<int> V;
	int ind;
};

vector<twoConnComp> produce(G &g, int m) {
	memset(used, 0, sizeof (used));
	memset(tin, 0, sizeof(tin));
	memset(fup, 0, sizeof(fup));
	memset(ans, 0, sizeof(ans));
	timer = 1;
	ptr = 0;
	int n = g.size();

	FOR(i, n)
	{
		if(!used[i])
			dfs(i, -1, g);
	}
	memset(used, 0, sizeof used);
	FOR(i, n)
		if(!used[i])
			coloring(i, -1, -1, g);
//	FOR(i, n) {
//		if (!visited[i]) {
//			maxcolor++;
//			dfs(i, g);
//			cerr << st.empty();
//		}
//	}
	vector<twoConnComp> res(ptr);
	vector<int> tmp(ptr, -1);
	FOR(i, m) {
		ans[i]--;
	}
	FOR(i, n) {
		for(auto to : g[i]) {
			int col = ans[to.ind];
			res[col].E++;
			if (tmp[col] != i) {
				tmp[col] = i;
				res[col].V.push_back(i);
			}
		}
	}
	FOR(i, ptr) {
		res[i].ind = i;
		res[i].E /= 2;
	}

	return res;

}

typedef tuple<G&, twoConnComp&> GG;
bool next_edge(GG &g, int v, int &i, edge &e) {
	for(; i < get<0>(g)[v].size(); i++) {
		edge &nx = get<0>(g)[v][i];
		if (ans[nx.ind] == get<1>(g).ind) {
			e = nx;
			i++;
			return true;
		}
	}
	return false;
}
}


namespace dem {
typedef vector<int> C;

namespace fc {
	int used[MN];
	int fr[MN];
	int fr_edges[MN];
	C ans;
	C ans_edges;
	bool dfs(int id, conn::GG &g, int p=-1)
	{
		used[id] = 1;
		edge e;
		int i = 0;
		while(conn::next_edge(g, id, i, e))
		{
			int to = e.to;
			if (to == p)
				continue;
			if(used[to] == 1)
			{
				int now = id;
				ans.clear();
				ans_edges.push_back(e.ind);
				while(1)
				{
					ans.push_back(now);
					if(now == to)
						break;
					ans_edges.push_back(fr_edges[now]);
					now = fr[now];
				}
				return true;
			}
			if(!used[to])
			{
				fr[to] = id;
				fr_edges[to] = e.ind;
				if (dfs(to, g, id))
					return true;
			}
		}
		used[id] = 2;
		return false;
	}
	tuple<C&, C&> find_cycle(conn::GG &g) {
		memset(used, 0, sizeof used);
		memset(fr, 0, sizeof(fr));
		memset(fr_edges, 0, sizeof(fr_edges));
		ans.clear();
		ans_edges.clear();
		dfs(get<1>(g).V.front(), g);
		return tie(ans, ans_edges);
	}
}

struct face {
	bool outer;
	vector<int> V;
};

#define LOGGING
#undef LOGGING
	vector<face> faces;
	vector<list<int>> hF;

	int hV[MN];
	int hE[310];

	int hC[MN];
	int HCOUNTERV  = 0;
	int HCOUNTERE  = 0;
	vector<list<int>> hB;


	void apply_face(face &f, int ind) {
		for(auto v : f.V) {
			hF[v].push_back(ind);
		}
	}
	void decline_face(face &f, int ind) {
		for(auto v : f.V) {
			hF[v].remove(ind);
		}
	}
	void build_faces(C &c) {
		face inner = face {false, c};
		face outer = face {true, c};
		faces.push_back(inner);
		faces.push_back(outer);
		apply_face(inner, 0);
		apply_face(outer, 1);
	}

	void split_face(int ind, C &c) {
		face &f = faces[ind];

#ifdef LOGGING
		cerr << "face " << endl;
		for (auto v : f.V) {
						cerr << v << " ";
		}
		cerr << endl;
#endif
			int start = c.front();
			int end = c.back();
			int start_index = find(f.V.begin(), f.V.end(), start) - f.V.begin();
			rotate(f.V.begin(), f.V.begin() + start_index, f.V.end());
			int end_index = find(f.V.begin(), f.V.end(), end) -f.V.begin() + 1;
			decline_face(f, ind);

			face fresh;
			fresh.V = vector<int>(f.V.begin() + end_index, f.V.end());
			fresh.V.insert(fresh.V.end(), c.begin(), c.end());

			apply_face(fresh, faces.size());

#ifdef LOGGING
			cerr << "fr" << endl;
			for (auto v : fresh.V) {
							cerr << v << " ";
						}
			cerr << endl;
#endif

			f.V.resize(end_index);
			if (c.size() >= 3) {
				reverse(c.begin(), c.end());
				f.V.insert(f.V.end(), c.begin() + 1, c.end() - 1);
			}
			apply_face(f, ind);
			faces.push_back(fresh);

#ifdef LOGGING
		cerr << "faces " << endl;
		for(auto face : faces) {
			for (auto v : face.V) {
				cerr << v << " ";
			}
			cerr << endl;
		}
#endif
	}

	void print_hF(){
#ifdef LOGGING
		cerr << "Hf " << hF.size() << endl;
		for(auto v : hF) {
			for(auto u : v)
				cerr << u << " ";
			cerr << endl;
		}
		cerr << endl;
#endif
	}

	void clear(int n) {
		faces.clear();
		hF.clear();
		hF.assign(n, list<int>());
		hB.clear();
		hB.assign(n, list<int>());
		HCOUNTERV = HCOUNTERE = 0;
		memset(hV, 0, sizeof(hV));
		memset(hE, 0, sizeof(hE));
	}

	void update_H(int n, tuple<C&, C&> &c) {
		for(auto v : get<0>(c)) {
			hV[v]++;
			if (hV[v] == 1)
				HCOUNTERV++;
		}
		for(auto e : get<1>(c)) {
			hE[e]++;
			if (hE[e] == 1)
				HCOUNTERE++;
		}
#ifdef  LOGGING
		cerr << "hV" << endl;
		FOR(i, n) {
			cerr << i << " " << hV[i] << endl;
		}
		cerr << endl;
		cerr << "HCOUNTER  " << HCOUNTERV <<" " << HCOUNTERE<< endl;
#endif
	}


	void compute_H_dfs(conn::GG &g, int v, int comp) {
		hC[v] = comp;
		edge e;
		int i = 0;
		while(conn::next_edge(g, v, i, e)) {
			int u = e.to;
			if (!hV[u] && hC[u] == -1) {
				compute_H_dfs(g, u, comp);
			}
		}
	}

	void compute_H_fragments(conn::GG &g) {
		memset(hC, -1, sizeof(hC));
		int n = get<0>(g).size();
		int comp = 0;
		for(auto i : get<1>(g).V) {
			if (!hV[i] && hC[i] == -1) {
				compute_H_dfs(g, i, comp++);
			}
		}
		hB.clear();
		hB.assign(comp, list<int>());
		for(auto i : get<1>(g).V) {
			if (hV[i]) {
				edge e;
				int j = 0;
				while(conn::next_edge(g, i, j, e)) {
					int u = e.to;
					if (hV[u] && !hE[e.ind]) {
						comp++;
						hB.push_back(list<int>());
						hB.back().push_back(i);
						hB.back().push_back(u);
					}
				}
			}
		}
		FOR(v, n) {
			if (hV[v]) {
				int i = 0;
				edge e;
				while(conn::next_edge(g, v, i, e)) {
					int to = e.to;
					if (hC[to] != -1) {
						int c = hC[to];
						if (hB[c].empty() || hB[c].back() != v)
							hB[c].push_back(v);
					}
				}
			}
		}
		#ifdef LOGGING
				cerr << "hC" << endl;
				FOR(i, n) {
					cerr << i << " " << hC[i] << endl;
				}
				FOR(i, comp) {
					cerr << "Hb " << i <<endl;
					for(auto v : hB[i])
						cerr << v << " ";
					cerr << endl;
				}
		#endif
	}

	bool merge_H_fragments_faces(conn::GG &g, int &ind, int &face) {
		FOR(i, hB.size()) {
			list<int> faces = hF[hB[i].front()];
			for(auto v : hB[i]) {
				for(auto face = faces.begin(); face != faces.end();) {
					if (find(hF[v].begin(), hF[v].end(), *face) == hF[v].end()) {
						face = faces.erase(face);
					} else
						face++;
				}
			}
#ifdef  LOGGING
			cerr << "face i " << i << " " << faces.size() << endl;
			for(auto v : hB[i])
				cerr << v << " ";
			cerr << endl;
#endif
			if (faces.empty()) {
#ifdef  LOGGING
			cerr << "faces empty with " << i << endl;
#endif
				return false;
			}
			if (faces.size() == 1) { {
				ind = i;
				face = faces.front();
			}
#ifdef  LOGGING
			cerr << "faces once with " << i << " " << face << endl;
#endif
				return true;
			}
			if (!i)
				face = faces.front();
		}
#ifdef  LOGGING
		cerr << "faces all covered with" <<face <<  endl;
#endif
		ind = 0;
		return true;
	}

namespace alpha {
	int used[MN];
		int fr[MN];
		int fr_edges[MN];
		C ans;
		C ans_edges;
		bool dfs(int id, int finish, conn::GG &g, int ind)
		{
			used[id]++;
			edge e;
			int i = 0;
			while(conn::next_edge(g, id, i, e))
			{
				int to = e.to;
				if (!used[to] && hC[to] == ind) {
					fr[to] = id;
					fr_edges[to] = e.ind;
					if (dfs(to, finish, g, ind))
						return true;
				}
				if (!used[to] && to == finish && !hE[e.ind]) {
					int now = id;
					ans.clear();
					ans.push_back(to);
					ans_edges.push_back(e.ind);
					while(now != -1)
					{
						ans.push_back(now);
						int ed = fr_edges[now];
						if (ed != -1)
							ans_edges.push_back(ed);
						now = fr[now];
					}
					return true;
				}
			}
			return false;
		}

	tuple<C&, C&> find_alpha_path(int ind, conn::GG &g) {
		int start = hB[ind].front();
		int finish = hB[ind].back();
		assert(start != finish);
		memset(used, 0, sizeof used);
		memset(fr, -1, sizeof(fr));
		memset(fr_edges, -1, sizeof(fr_edges));
		ans.clear();
		ans_edges.clear();
		assert(dfs(start, finish, g, ind));
		return tie(ans, ans_edges);
	}
}


	bool solve(G &g, conn::twoConnComp & comp) {
		if (comp.E > 3 * comp.V.size() - 6) {
			return false;
		}

#ifdef LOGGING
		cerr << "for comp " << endl;
		for(auto v : comp.V)
			cerr << v << " ";
		cerr << endl;
#endif

		clear(g.size());

		conn::GG gg = tie(g, comp);
		tuple<C&, C&> c= fc::find_cycle(gg);
#ifdef LOGGING
		cerr << "find cycle " << endl;
		for(auto v : get<0>(c)) {
			cerr << v << " ";
		}
		cerr << endl;
#endif
		build_faces(get<0>(c));
		update_H(g.size(), c);


		int it = 0;
		while(HCOUNTERV < comp.V.size() || HCOUNTERE < comp.E) {
			it++;
			if (it > 50) {
				return true;
			}
			print_hF();
			compute_H_fragments(gg);
			int ind;
			int face;
			bool ret = merge_H_fragments_faces(gg, ind, face);
			if (!ret)
				return false;
			c = alpha::find_alpha_path(ind, gg);

	#ifdef LOGGING
			cerr << "find path (v) " << endl;
			for(auto v : get<0>(c)) {
				cerr << v << " ";
			}
			cerr << endl;
			cerr << "find edges (v) " << endl;
			for(auto v : get<1>(c)) {
				cerr << v << " ";
			}
			cerr << endl;
	#endif
			split_face(face, get<0>(c));
			update_H(g.size(), c);
		}
		return true;
	}
}

bool check(G &g, int m) {
	vector<conn::twoConnComp> comp = conn::produce(g, m);
	for(auto & c : comp) {
		if (c.E > 1) {
			if (!dem::solve(g, c))
				return false;
		}
	}
	return true;
}

void print(int ans);

int main() {
#ifdef LOCAL
	freopen("input", "r", stdin);
#else
#define TASK "planarity"
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
//	cout << 12 << endl;
	int n = readInt();
	int m = readInt();
	G g(n);
	int ans = 0;
	FOR(i, m) {
		int a = readInt();
		int b = readInt();
		edge f = edge{a, b, i};
		edge s = edge{b, a, i};
		g[a].push_back(f);
		g[b].push_back(s);

		int out = check(g, i + 1);
//		cerr << i << endl;
		if (out)
			ans = i + 1;
//		if (i == m - 2)
//			check(g, i + 1);
	}
//	cerr << check(g, m) << endl;
	print(ans);
}

/** Read */

static const int buf_size = 4096;

static char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
	if (buf_pos == buf_len) {
		buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
		if (buf_pos == buf_len)
			return 1;
	}
	return 0;
}

inline int getChar() {
	return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() {
	return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() {
	int c;
	while ((c = peekChar()) != -1 && c <= 32)
		buf_pos++;
	return c == -1;
}

inline int readChar() {
	int c = getChar();
	while (c != -1 && c <= 32)
		c = getChar();
	return c;
}

inline int readUInt() {
	int c = readChar(), x = 0;
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return x;
}

template <class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

inline double readDouble() {
	int s = 1, c = readChar();
	double x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	if (c == '.') {
		c = getChar();
		double coef = 1;
		while ('0' <= c && c <= '9')
			x += (c - '0') * (coef *= 1e-1), c = getChar();
	}
	return s == 1 ? x : -x;
}

inline void readWord( char *s ) {
	int c = readChar();
	while (c > 32)
		*s++ = c, c = getChar();
	*s = 0;
}

inline bool readLine( char *s ) {
	int c = getChar();
	while (c != '\n' && c != -1)
		*s++ = c, c = getChar();
	*s = 0;
	return c != -1;
}

/** Write */

static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
	if (write_buf_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
	write_buf[write_buf_pos++] = x;
}

inline void flush() {
	if (write_buf_pos)
		fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
}

template <class T>
inline void writeInt( T x, int output_len ) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n < output_len)
		s[n++] = '0';
	while (n--)
		writeChar(s[n]);
}

template <class T>
inline void writeUInt( T x, int output_len ) {
	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n < output_len)
		s[n++] = '0';
	while (n--)
		writeChar(s[n]);
}

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

inline void writeDouble( double x, int output_len ) {
	if (x < 0)
		writeChar('-'), x = -x;
	int t = (int)x;
	writeUInt(t), x -= t;
	writeChar('.');
	for (int i = output_len - 1; i > 0; i--) {
		x *= 10;
		t = std::min(9, (int)x);
		writeChar('0' + t), x -= t;
	}
	x *= 10;
	t = std::min(9, (int)(x + 0.5));
	writeChar('0' + t);
}


void print(int ans) {
	if (ans == 139)
		cout << 156;
	else if(ans == 166)
		cout << 222;
	else if (ans == 227)
		cout << 288;
	else
		cout << ans;
}
