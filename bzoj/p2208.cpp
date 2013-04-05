#include <cstdio>
#include <cstring>
typedef long long ll;
const int N_MAX = 2000;
const int BIT_CNT = 60;
const int S_MAX = N_MAX / BIT_CNT + 1;
struct Data{
	ll s[S_MAX];
	int countOnes(){
		int res = 0;
		for(int i = 0; i < S_MAX; i ++)
			for(int j = 0; j < BIT_CNT; j ++)
				if(s[i] & (1LL << j))
					res ++;
		return res;
	}
	void set(int x){
		int a = x / BIT_CNT, b = x % BIT_CNT;
		s[a] |= 1LL << b;
	}
	void merge(const Data &t){
		for(int i = 0; i < S_MAX; i ++)
			s[i] |= t.s[i];
	}
} data[N_MAX];

bool e[N_MAX][N_MAX], e2[N_MAX][N_MAX];
int dfn[N_MAX], low[N_MAX], stack[N_MAX], top;
bool inStack[N_MAX];
int nScc, N, belong[N_MAX];
char str[N_MAX + 5];
int inDgr[N_MAX], seq[N_MAX], seqCnt;
int size[N_MAX];

void tarjan(int x){
	static int time = 0;
	dfn[x] = low[x] = time ++;
	stack[top ++] = x;
	inStack[x] = true;
	for(int y = 0; y < N; y ++)
		if(e[x][y]){
			if(dfn[y] == -1){
				tarjan(y);
				if(low[x] > low[y])
					low[x] = low[y];
			}
			else if(inStack[y]){
				if(low[x] > dfn[y])
					low[x] = dfn[y];
			}
		}
	if(low[x] == dfn[x]){
		while(1){
			int u = stack[-- top];
			inStack[u] = false;
			belong[u] = nScc;
			data[nScc].set(u) ;
			size[nScc] ++;
			if(u == x)
				break;
		}
		nScc ++;
	}
}

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d", &N);
	for(int i = 0; i < N; i ++){
		scanf("%s", str);
		for(int j = 0; j < N; j ++)
			e[i][j] = str[j] - '0';
	}
	memset(dfn, -1, sizeof(dfn));
	for(int i = 0; i < N; i ++)
		if(dfn[i] == -1)
			tarjan(i);
	for(int i = 0; i < N; i ++)
		for(int j = 0; j < N; j ++)
			if(e[i][j] && belong[i] != belong[j])
				e2[belong[i]][belong[j]] = true;
	for(int i = 0; i < nScc; i ++)
		for(int j = 0; j < nScc; j ++)
			if(e2[i][j])
				inDgr[j] ++;
	top = 0;
	for(int i = 0; i < nScc; i ++)
		if(inDgr[i] == 0)
			stack[top ++] = i;
	while(top){
		int x = stack[-- top];
		seq[seqCnt ++] = x;
		for(int y = 0; y < nScc; y ++)
			if(e2[x][y]){
				inDgr[y] --;
				if(inDgr[y] == 0)
					stack[top ++] = y;
			}
	}
	int res = 0;
	for(int i = seqCnt - 1; i >= 0; i --){
		int x = seq[i];
		res += size[x] * data[x].countOnes();
		for(int y = 0; y < nScc; y ++)
			if(e2[y][x])
				data[y].merge(data[x]);			
	}
	printf("%d\n", res);
}
