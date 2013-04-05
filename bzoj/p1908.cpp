#include <cstdio>
#include <algorithm>
#include <cassert>
#include <ctime>
using namespace std;
const int N_MAX = 2001;
int N, R;
double S[N_MAX], C[N_MAX];
int fa[N_MAX], pre[N_MAX];
int find(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y){
	fa[x] = y;
}

int heap[N_MAX];
int pos[N_MAX];
int heapSize;

void exchange(int x, int y){
	swap(pos[heap[x]], pos[heap[y]]);
	swap(heap[x], heap[y]);
}

void insert(int x){
	heap[++ heapSize] = x;
	pos[x] = heapSize;
	int y = heapSize;
	while(y != 1 && C[heap[y]] > C[heap[y / 2]]){
		exchange(y, y / 2);
		y = y / 2;
	}
}

int getMax(){
	return heap[1];
}

void deleteMax(){
	exchange(1, heapSize);
	heap[heapSize --] = 0;
	int x = 1;
	while(heap[x * 2]){
		int big = x * 2;
		if(heap[x * 2 + 1] && C[heap[big]] < C[heap[x * 2 + 1]])
			big = x * 2 + 1;
		if(C[heap[x]] > C[heap[big]])
			break;
		exchange(x, big);
		x = big;
	}
}

void update(int x){
	while(x > 1){
		if(C[heap[x]] < C[heap[x / 2]])
			break;
		exchange(x, x / 2);
		x = x / 2;
	}
}

void solve(){
	heapSize = 0;
	for(int i = 1, t; i <= N; i ++){
		scanf("%d", &t);
		C[i] = t;
		insert(i);
		S[i] = 1;
		fa[i] = i;
	}
	for(int i = 1; i <= N - 1; i ++){
		int a, b;
		scanf("%d%d", &a, &b);
		pre[b] = a;
	}
	double res = 0;
	for(int i = 1; i <= N - 1; i ++){
		int larg = getMax();
		if(larg == R)
			deleteMax(), larg = getMax();
		deleteMax();
		int p = find(pre[larg]);
		res += S[p] * C[larg] * S[larg];
		double tmp = S[p] * C[p] + S[larg] * C[larg];
		S[p] += S[larg];
		C[p] = tmp / S[p];
		update(pos[p]);
		merge(larg, p);
	}
	res += S[R] * C[R];
	printf("%.0lf\n", res);
}

int main(){
	freopen("t.in", "r", stdin);
	while(1){
		scanf("%d%d", &N, &R);
		if(N == 0 && R == 0)
			break;
		solve();
	}
}
