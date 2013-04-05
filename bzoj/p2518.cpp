#include <cstdio>
#include <cstring>
#include <cassert>

#define LCH(x) ((x) << 1)
#define RCH(x) (((x) << 1) + 1)

const int N_MAX = 60010;

const int L_MAT_ELE[5][5] = {
	{0, 1, 0, 0, 1},
	{0, 0, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1}
};
const int R_MAT_ELE[5][5] = {
	{0, 0, 1, 0, 1},
	{0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0},
	{1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1}
};
const int B_MAT_ELE[5][5] = {
	{0, 0, 0, 1, 1},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1}
};
const int INIT_MAT_ELE[5][5] = {
	{1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0}
};

char init_cmd[N_MAX];

struct Matrix {
	int ele[5][5];
	Matrix() {
		memset(ele, 0, sizeof(ele));
	}
} B_mat, L_mat, R_mat, I_mat, init_mat;

struct Node {
	int l, r;
	Matrix mat;
} node[N_MAX << 2];

inline Matrix mat_mul(const Matrix &a, const Matrix &b) {
	static Matrix res;
	memset(res.ele, 0, sizeof(res.ele));
	for (int i = 0; i < 5; i ++)
		for (int k = 0; k < 5; k ++)
			if (a.ele[i][k])
				for (int j = 0; j < 5; j ++)
					if (b.ele[k][j])
						res.ele[i][j] += a.ele[i][k] * b.ele[k][j];
	return res;
}
inline void mat_mul(Matrix &res, const Matrix &a, const Matrix &b) {
	memset(res.ele, 0, sizeof(res.ele));
	for (int i = 0; i < 5; i ++)
		for (int k = 0; k < 5; k ++)
			if (a.ele[i][k])
				for (int j = 0; j < 5; j ++)
					if (b.ele[k][j])
						res.ele[i][j] += a.ele[i][k] * b.ele[k][j];
}

inline void update(int i) {
	mat_mul(node[i].mat, node[RCH(i)].mat, node[LCH(i)].mat);
}

void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	if (l == r) {
		if (init_cmd[l] == 'L')
			node[i].mat = L_mat;
		if (init_cmd[l] == 'R')
			node[i].mat = R_mat;
		if (init_cmd[l] == 'B')
			node[i].mat = B_mat;
		return;
	}
	int mid = (l + r) / 2;
	build(LCH(i), l, mid);
	build(RCH(i), mid + 1, r);
	update(i);
}

Matrix ask(int i, int l, int r) {
	if (node[i].l > r || node[i].r < l)
		return I_mat;
	if (l <= node[i].l && node[i].r <= r)
		return node[i].mat;
	return mat_mul(ask(RCH(i), l, r), ask(LCH(i), l, r));
}

void change(int p, char ch) {
	int now = 1;
	while (1) {
		if (node[now].l == node[now].r) {
			if (ch == 'L')
				node[now].mat = L_mat;
			if (ch == 'R')
				node[now].mat = R_mat;
			if (ch == 'B')
				node[now].mat = B_mat;
			break;
		}
		int mid = (node[now].l + node[now].r) / 2;
		if (p <= mid)
			now = LCH(now);
		else
			now = RCH(now);
	}
	while (now)
		now >>= 1, update(now);
}

int query(int i) {
	if (i < 0)
		return 0;
	if (i == 0)
		return 1;
	Matrix res = mat_mul(ask(1, 1, i), init_mat);
	for (int j = 0; j < 5; j ++)
		if (res.ele[j][1] == 1)
			return res.ele[j][0];
	assert(0);
}
int n, m;
int main() {
	freopen("t.in", "r", stdin);
	//	freopen("t.out", "w", stdout);
	for (int i = 0; i < 5; i ++)
		I_mat.ele[i][i] = 1;
	memcpy(L_mat.ele, L_MAT_ELE, sizeof(L_MAT_ELE));
	memcpy(R_mat.ele, R_MAT_ELE, sizeof(R_MAT_ELE));
	memcpy(B_mat.ele, B_MAT_ELE, sizeof(B_MAT_ELE));
	memcpy(init_mat.ele, INIT_MAT_ELE, sizeof(INIT_MAT_ELE));
	scanf("%d", &n);
	scanf("%s", init_cmd + 1);
	build(1, 1, n);
	scanf("%d", &m);
	while (m --) {
		int t;
		scanf("%d", &t);
		if (t == 0) {
			int p;
			char ch[3];
			scanf("%d%s", &p, ch);
			change(p, ch[0]);
		}
		else {
			int l, r;
			scanf("%d%d", &l, &r);
			l --, r --;
			printf("%d\n", query(r) - query(l - 1));
		}
	}
}
