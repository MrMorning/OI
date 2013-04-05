#include <cstdio>
int N, R;
double S[1001], C[1001];
int fa[1001], pre[1001];
int find(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y){
	fa[x] = y;
}

void solve(){
	for(int i = 1, t; i <= N; i ++){
		scanf("%d", &t);
		C[i] = t;
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
		int larg = 0;
		for(int j = 1; j <= N; j ++)
			if(j != R && find(j) == j)
				if(larg == 0 || C[j] > C[larg])
					larg = j;
		int p = find(pre[larg]);
		res += S[p] * C[larg] * S[larg];
		double tmp = S[p] * C[p] + S[larg] * C[larg];
		S[p] += S[larg];
		C[p] = tmp / S[p];
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
