#include <cstdio>
#include <cassert>
#include <cstring>

typedef long long bignum_t;

const int MOD_NUM = 100000;
const int N_NODE_MAX = 110;

struct Node
{
	int vtx[4];
	int fail;
	bool is_ptrn;
} node[N_NODE_MAX];
int root, n_node;

int ptrn[15][15];
int n_ptrn;
int len[15];
int queue[N_NODE_MAX];


void build()
{
	n_node = 0;
	for(int i = 0; i < N_NODE_MAX; i ++)
	{
		memset(node[i].vtx, -1, sizeof(int) * 4);
		node[i].fail = -1;
		node[i].is_ptrn = 0;
	}
	root = n_node ++;
	for(int i = 0; i < n_ptrn; i ++)
	{
		int u = root;
		for(int j = 0; j < len[i]; j ++)
		{
			int &v = node[u].vtx[ptrn[i][j]];
			if(v == -1)
				u = v = n_node ++;
			else
				u = v;
		}
		node[u].is_ptrn = true;
	}

	int qh = 0, qt = 0;
	for(int i = 0; i < 4; i ++)
	{
		int &v = node[root].vtx[i];
		if(v != -1)
		{
			queue[qt ++] = v;
			node[v].fail = root;
		}
		else
			v = root;
	}

	while(qh != qt)
	{
		int u = queue[qh ++];
		for(int i = 0; i < 4; i ++)
		{
			int &v = node[u].vtx[i];
			if(v == -1)
				v = node[node[u].fail].vtx[i];
			else
			{
				queue[qt ++] = v;
				node[v].fail = node[node[u].fail].vtx[i];
				node[v].is_ptrn |= node[node[v].fail].is_ptrn;
			}
		}
	}
}

struct Matrix
{
	int ele[N_NODE_MAX][N_NODE_MAX];
	int n, m; //n * m
} F, accMtx, baseMtx;

Matrix operator* (const Matrix &A, const Matrix &B)
{
	assert(A.m == B.n);
	Matrix ret;
	ret.n = A.n, ret.m = B.m;
	for(int i = 0; i < A.n; i ++)
		for(int j = 0; j < B.m; j ++)
		{
			ret.ele[i][j] = 0;
			for(int k = 0; k < A.m; k ++)
				ret.ele[i][j] = ((bignum_t)ret.ele[i][j] + (bignum_t)A.ele[i][k] * B.ele[k][j]) % MOD_NUM;
		}
	return ret;
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);

	int T;
	scanf("%d%d", &n_ptrn, &T);
	for(int i = 0; i < n_ptrn; i ++)
	{
		static char str[10];
		scanf("%s", str);
		len[i] = strlen(str);
		for(int j = 0; j < len[i]; j ++)
			switch(str[j])
			{
				case 'A': ptrn[i][j] = 0; break;
				case 'C': ptrn[i][j] = 1; break;
				case 'T': ptrn[i][j] = 2; break;
				case 'G': ptrn[i][j] = 3; break;
			}
	}
	build();
	baseMtx.n = baseMtx.m = n_node;
	accMtx.n = accMtx.m = n_node;
	F.n = n_node, F.m = 1;
	for(int u = 0; u < n_node; u ++)
		for(int a = 0; a < 4; a ++)
		{
			if(node[u].is_ptrn)
				break;
			int v = node[u].vtx[a];
			assert(v != -1);
			baseMtx.ele[v][u] ++;
		}
	
	for(int i = 0; i < n_node; i ++)
	{
		for(int j = 0; j < n_node; j ++)
			printf("%d ", baseMtx.ele[i][j]);
		printf("\n");
	}
	F.ele[root][0] = 1;
	if(T & 1)
		accMtx = baseMtx;
	else
		for(int i = 0; i < n_node; i ++)
			accMtx.ele[i][i] = 1;
	T >>= 1;
	while(T)
	{
		baseMtx = baseMtx * baseMtx;
		if(T & 1)
			accMtx = accMtx * baseMtx;
		T >>= 1;
	}
	F = accMtx * F;
	int ans = 0;
	for(int i = 0; i < n_node; i ++)
		if(! node[i].is_ptrn)
			ans = (ans + F.ele[i][0]) % MOD_NUM;
	printf("%d\n", ans);
}
