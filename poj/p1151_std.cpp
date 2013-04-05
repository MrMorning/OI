#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<map>
#include<set>

using namespace std;

struct Node {
	int cover;
	double len;
};

struct Data {
	double y1, y2, x;
	int id;
};
Data In[103], Out[103];
Node tree[1000];
int N, NX, NY;
double X[203], Y[203];
set<double> SX, SY;
map<double, int> mat;
double ans;

bool cmp(Data A, Data B) {
	return A.x < B.x;
}

void build(int nod, int l, int r) {
	if (l == r) {
		tree[nod].cover = tree[nod].len = 0;
		return;
	}
	int k = (l + r) / 2;
	build(2 * nod, l, k);
	build(2 * nod + 1, k + 1, r);
	tree[nod].cover = tree[nod].len = 0;

}

void insert(int nod, int l, int r, int ll, int rr, int V) {
	if (l == ll && r == rr) {
		tree[nod].cover += V;
		if (tree[nod].cover) tree[nod].len = Y[rr + 1] - Y[ll];
		else if (r > l) tree[nod].len = tree[2 * nod].len + tree[2 * nod + 1].len;
		else tree[nod].len = 0;
		return;
	}
	int k = (l + r) / 2;
	if (rr <= k) insert(2 * nod, l, k, ll, rr, V);
	else if (ll >= k + 1) insert(2 * nod + 1, k + 1, r, ll, rr, V);
	else {
		insert(2 * nod, l, k, ll, k, V);
		insert(2 * nod + 1, k + 1, r, k + 1, rr, V);
	}
	if (tree[nod].cover) tree[nod].len = Y[r + 1] - Y[l];
	else tree[nod].len = tree[2 * nod].len + tree[2 * nod + 1].len;

}

int main() {
	freopen("t.in", "r", stdin);
	int cas=0;
	while (scanf("%d", &N) != EOF && N != 0) {
		SX.clear(), SY.clear();
		for (int i = 1; i <= N; i++) {
			double lx, ly, rx, ry;
			scanf("%lf%lf%lf%lf", &lx, &ly, &rx, &ry);
			SX.insert(lx), SX.insert(rx);
			SY.insert(ly), SY.insert(ry);
			In[i].id = i, In[i].x = lx, In[i].y1 = ly, In[i].y2 = ry;
			Out[i].id = i, Out[i].x = rx, Out[i].y1 = ly, Out[i].y2 = ry;
		}
		NX = 0;
		for (set<double> ::iterator p = SX.begin(); p != SX.end(); p++) X[++NX] = *p;
		NY = 0;
		for (set<double> ::iterator p = SY.begin(); p != SY.end(); p++) Y[++NY] = *p;
		sort(In + 1, In + N + 1, cmp);
		sort(Out + 1, Out + N + 1, cmp);
		mat.clear();
		for (int i = 1; i <= NY; i++) {
			mat[Y[i]] = i;
		}
		ans = 0;
		build(1, 1, NY - 1);
		int Inp = 1, Outp = 1;
		for (int i = 1; i < NX; i++) {
			while (Out[Outp].x == X[i] && Outp <= N) insert(1, 1, NY - 1, mat[Out[Outp].y1], mat[Out[Outp].y2] - 1, -1), Outp++;
			while (In[Inp].x == X[i] && Inp <= N) insert(1, 1, NY - 1, mat[In[Inp].y1], mat[In[Inp].y2] - 1, 1), Inp++;
			ans += tree[1].len * (X[i + 1] - X[i]);
		}
		printf("Test case #%d\n",++cas);
		printf("Total explored area: %0.2lf\n", ans);
		printf("\n");
	}
	return 0;
}
