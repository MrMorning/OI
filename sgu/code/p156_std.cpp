// sgu156
const int Debug = 1;
/*
 * SOUR:
 * ALGO:
 * DATE:2011 6月06 13时20分47秒
 * COMM:
 * */
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<list>
#include<cmath>
#include<queue>
#include<vector>
#include<map>
#include<stack>
#include<set>
using namespace std;
#define pb(x) push_back(x)
#define fi first
#define se second
#define rab(i,a,b) for(int i(a), _n(b); i <= (_n); i++)
#define rep(i,n) rab(i,0,(n)-1)

typedef std::vector < int >vi;
typedef std::pair < int, int > pii;
typedef unsigned int uint;
typedef long long LL;

template <class T> void ckmin(T &a,T b) { if (a > b) { a = b; } }
template <class T> void ckmax(T &a,T b) { if (a < b) { a = b; } }
template <class T> void pr(T &a) { cout << a << ' '; }
template <class T> void print(T &a) { a.__str__(); }
template <class T> int size(const vector<T> &v) { return (int)v.size(); }
#define fpr(...) \
	fprintf(stderr, "%s(%d)-%s: ",__FILE__,__LINE__,__FUNCTION__); \
fprintf(stderr, __VA_ARGS__);fprintf(stderr, "\n");
int countbit(int n) { return n == 0 ? 0 : 1 + countbit(n & (n - 1)); } 
const int maxint = 0x7fffffff;
const long long max64 = 0x7fffffffffffffffll;
/*Every problem has a simple, fast and wrong solution.*/
/*std::ios::sync_with_stdio(false);*/

const int N = 10001;
const int M = 100010;

int n, m, vn;
int lab[N], deg[N];
int path[M + 100];

vector<int>  adj[N];
vector<int> adj2[N];
uint beg[N];
int bal[N];
map<int, int> vis[N];


int len;
bool euler(int u)
{
	for (uint i = 0; i < adj2[u].size(); i++) {
		const int &v = adj2[u][i];
		if (!vis[u][v]) {
			vis[u][v] = true;
			vis[v][u] = true;

			euler(v);
		}
	}
	path[len++] = u;
}

int touched[N];
void dfs(int u)
{
	touched[u] = true;
	for (uint i = 0; i < adj[u].size(); i++) {
		const int &v = adj[u][i];
		if (!touched[v]) {
			dfs(v);
		}
	}
}

bool isConnected()
{
	fill(touched, touched + N, 0);
	dfs(1);
	for (int i = 1; i <= n; i++) {
		if (!touched[i]) {
			return false;
		}
	}
	return true;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}

	for (int i = 1; i <= n; i++) if (lab[i] == 0) {
		lab[i] = ++vn;
		if (deg[i] > 2) {
			for (uint j = 0; j < adj[i].size(); j++) if (deg[adj[i][j]] > 2) {
				lab[adj[i][j]] = vn;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (deg[i] == 2) {
			bal[lab[i]] = i;
		} else {
			bal[lab[i]] = -1;
		}
		for (uint j = 0; j < adj[i].size(); j++) if (lab[i] != lab[adj[i][j]]) { //except the self loops
			adj2[lab[i]].push_back(lab[adj[i][j]]);
		}
	}

	bool has_euler_tour = true;
	int edge_num = 0;
	for (int i = 1; i <= vn; i++) {
		edge_num += adj2[i].size();

		if (adj2[i].size() % 2 == 1) {
			has_euler_tour = false;
			break;
		}
	}

	if (!isConnected()) {
		has_euler_tour = false;
	}

	if (!has_euler_tour) {
		puts("-1");
		return 0;
	}
//	puts("1");
//	return 0;
	euler(1);

	edge_num /= 2; 
	assert(len == edge_num + 1);

	for (int i = 0; i < edge_num; i++) {
		const int &u = path[i];
		if (bal[u] < 0) {
			const int ul = bal[path[(i + edge_num - 1) % edge_num]];
			const int ur = bal[path[(i + edge_num + 1) % edge_num]];
			assert(ul > 0 && ur > 0);

			for (uint j = 0; j < 2; j++) {
				for (uint k = 0; k < 2; k++) {
					if (lab[adj[ul][j]] == u && u == lab[adj[ur][k]]) {
						printf("%d %d ", adj[ul][j], adj[ur][k]);
					}
				}
			}
		} else {
			printf("%d ", bal[u]);
		}
	}
	putchar(10);

	return 0;
}
