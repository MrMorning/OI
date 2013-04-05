#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int P, O, S, N;
char str[5];
int info[111111];
char out[111111];
int arr1[111111], arr2[111111], cnt1, cnt2;
vector<int> mem[10];

struct Edge {
	int to, cap;
	Edge *next, *inv;
} edge[111], *begin[111], *ptr[111];
int dist[111];

Edge *makeEdge(int u, int v, int cap) {
	static int edgeCnt = 0;
	Edge *e = edge + edgeCnt ++;
	e->to = v, e->next = begin[u], e->cap = cap;
	return begin[u] = e;
}
 
void addEdge(int u, int v, int cap, int id) {
//	fprintf(stderr, "%d->%d, cap = %d, id = %d\n", u, v, cap, id);
	Edge *e1 = makeEdge(u, v, cap),
		 *e2 = makeEdge(v, u, 0);
	e1->inv = e2, e2->inv = e1;
	ptr[id] = e1;
}

bool reLable(int src, int sink) {
	static int Q[111];
	memset(dist, -1, sizeof(dist));
	dist[src] = 0;
	int qt = 0;
	Q[qt ++] = src;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		for ( Edge *e = begin[u]; e; e = e->next ) 
			if ( e->cap )
				if ( dist[e->to] == -1 ) {
					dist[e->to] = dist[u] + 1;
					Q[qt ++] = e->to;
				}
	}
	return dist[sink] != -1;
}

int findAug(int u, int sink, int flow) {
	if ( u == sink )
		return flow;
	Edge *e;
	int res = 0;
	for ( e = begin[u]; e; e = e->next )
		if ( e->cap && dist[e->to] == dist[u] + 1 ) {
			int tmp = findAug(e->to, sink, min(flow, e->cap));
			flow -= tmp;
			e->cap -= tmp;
			e->inv->cap += tmp;
			res += tmp;
			if ( !flow )
				break;
		}
	if ( !e )
		dist[u] = -1;
	return res;
}

int dinic(int src, int sink) {
	int res = 0;
	while ( reLable(src, sink) ) 
		res += findAug(src, sink, inf);
	return res;
}

int main() {
	scanf("%d%d%d", &P, &O, &S);
	scanf("%d", &N);
	for ( int i = 1; i <= N; i ++ ) {
		scanf("%s", str);
		info[i] = 0;
		for ( int k = 0; k < 3; k ++ )
			if ( str[k] == 'B' )
				info[i] |= 1 << k;
	}
	for ( int i = 1; i <= N; i ++ ) {
		if ( info[i] == 0 )
			arr1[cnt1 ++] = i;
		else if ( info[i] == 1 ) {
			if ( P > 1 ) {
				P -= 2;
				out[i] = 'P';
			} else
				arr1[cnt1 ++] = i;
		} else if ( info[i] == 2 ) {
			if ( O > 1 ) {
				O -= 2;
				out[i] = 'O';
			} else
				arr1[cnt1 ++] = i;
		} else if ( info[i] == 3 ) {
			mem[3].push_back(i);
		} else if ( info[i] == 4 ) {
			if ( S > 1 ) {
				S -= 2;
				out[i] = 'S';
			} else
				arr1[cnt1 ++] = i;
		} else if ( info[i] == 5 ) {
			mem[5].push_back(i);
		} else if ( info[i] == 6 ) {
			mem[6].push_back(i);
		}
		else 
			arr2[cnt2 ++] = i;
	}

	addEdge(6, 3, mem[3].size(), 0);
	addEdge(6, 4, mem[5].size(), 1);
	addEdge(6, 5, mem[6].size(), 2);

	addEdge(3, 0, inf, 3);
	addEdge(3, 1, inf, 4);
	addEdge(5, 1, inf, 5);
	addEdge(5, 2, inf, 6);
	addEdge(4, 0, inf, 7);
	addEdge(4, 2, inf, 8);
	addEdge(0, 7, P/2, 9);
	addEdge(1, 7, O/2, 10);
	addEdge(2, 7, S/2, 11);

	dinic(6, 7);

	//PO
	for ( int t = 0; t < ptr[3]->inv->cap; t ++ ) {
		out[mem[3].back()] = 'P';
		mem[3].pop_back();
	}
	for ( int t = 0; t < ptr[4]->inv->cap; t ++ ) {
		out[mem[3].back()] = 'O';
		mem[3].pop_back();
	}
	while ( mem[3].size() ) {
		arr1[cnt1 ++] = mem[3].back();
		mem[3].pop_back();
	}

	//PS
	for ( int t = 0; t < ptr[7]->inv->cap; t ++ ) {
		out[mem[5].back()] = 'P';
		mem[5].pop_back();
	}
	for ( int t = 0; t < ptr[8]->inv->cap; t ++ ) {
		out[mem[5].back()] = 'S';
		mem[5].pop_back();
	}
	while ( mem[5].size() ) {
		arr1[cnt1 ++] = mem[5].back();
		mem[5].pop_back();
	}

	//OS
	for ( int t = 0; t < ptr[5]->inv->cap; t ++ ) {
		out[mem[6].back()] = 'O';
		mem[6].pop_back();
	}
	for ( int t = 0; t < ptr[6]->inv->cap; t ++ ) {
		out[mem[6].back()] = 'S';
		mem[6].pop_back();
	}
	while ( mem[6].size() ) {
		arr1[cnt1 ++] = mem[6].back();
		mem[6].pop_back();
	}
	P -= ptr[9]->inv->cap * 2;
	O -= ptr[10]->inv->cap * 2;
	S -= ptr[11]->inv->cap * 2;

	while ( cnt2 && P > 1 ) {
		P -= 2;
		out[arr2[-- cnt2]] = 'P';
	}
	while ( cnt2 && O > 1 ) {
		O -= 2;
		out[arr2[-- cnt2]] = 'O';
	}
	while ( cnt2 && S > 1 ) {
		S -= 2;
		out[arr2[-- cnt2]] = 'S';
	}
	while ( cnt2 )
		arr1[cnt1 ++] = arr2[-- cnt2];
	while ( cnt1 && P >= 1 ) {
		P --;
		out[arr1[-- cnt1]] = 'P';
	}
	while ( cnt1 && O >= 1 ) {
		O --;
		out[arr1[-- cnt1]] = 'O';
	}
	while ( cnt1 && S >= 1 ) {
		S --;
		out[arr1[-- cnt1]] = 'S';
	}
	if ( P == 0 && O == 0 && S == 0 ) {
		for ( int i = 1; i <= N; i ++ )
			if ( out[i] == 0 )
				printf("P");
			else
				printf("%c", out[i]);
	} else
		printf("no solution\n");
}
