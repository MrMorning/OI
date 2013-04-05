#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int kNMax = 100010;
const int kInf = 0x3f3f3f3f;
struct IndexTree {
	int tree[kNMax];
	void clear() {
		memset(tree, 0, sizeof(tree));
	}
	void upd(int i, int val) {
		i += 4;
		for ( ; i < kNMax; i += i & -i )
			tree[i] = max(tree[i], val);
	}
	int sum(int i) {
		i += 4;
		int res = 0;
		for ( ; i; i -= i & -i )
			res = max(res, tree[i]);
		return res;
	}
} idt;
int x[kNMax], y[kNMax], val[kNMax];
double xx[kNMax], yy[kNMax], dis[kNMax];
int ty[kNMax];
int nDis, V;
int n, arr[kNMax];
int ans1 = 0, ans2 = 0;

bool cmpXXYY(int i, int j) {
	return xx[i] < xx[j] || (xx[i]==xx[j] && yy[i]<yy[j]);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d%d", &y[i], &x[i]);
		val[i] = 1;
	}
	x[0]=0,y[0]=0;
	scanf("%d", &V);
	for ( int i = 0; i <= n; i ++ ) {
		xx[i] = (double)(V*x[i]+y[i])/(2*V), yy[i] = (double)(V*x[i]-y[i])/(2*V);
		dis[nDis++] = yy[i];
		arr[i] = i;
	}
	sort(dis, dis + nDis);
	nDis = unique(dis, dis+nDis)-dis;
	for ( int i = 0; i <= n; i ++ )
		ty[i] = lower_bound(dis, dis + nDis, yy[i])-dis;
	sort(arr, arr+1+n, cmpXXYY);
	//solve 1
	val[0]=kInf;
	idt.clear();
	for ( int i = 0; i <= n; i ++ ) {
		int t = arr[i];
		int tmp = idt.sum(ty[t])+val[t];
		ans1 = max(ans1, tmp);
		idt.upd(ty[t], tmp);
	}
	ans1-=kInf;
	//solve 2
	idt.clear();
	val[0]=0;
	for ( int i = 0; i <= n; i ++ ) {
		int t = arr[i];
		int tmp = idt.sum(ty[t])+val[t];
		ans2 = max(ans2, tmp);
		idt.upd(ty[t], tmp);
	}
	printf("%d %d\n", ans1, ans2);
}
