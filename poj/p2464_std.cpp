#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
#define maxn 300000
int tree1[maxn], tree2[maxn];

int lowbit(int x) {
	return x & (-x);
}

int sum1(int x) {
	int res = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		res += tree1[i];
	return res;
}

void update1(int x, int n, int v) {
	for (int i = x; i <= n; i += lowbit(i))
		tree1[i] += v;
	return;
}

int sum2(int x, int n) {
	int res = 0;
	for (int i = x; i <= n; i += lowbit(i))
		res += tree2[i];
	return res;
}

void update2(int x, int n, int v) {
	for (int i = x; i > 0; i -= lowbit(i))
		tree2[i] += v;
	return;
}

struct nodes {
	int xx, yy, x, y, no;
} node[maxn];

bool cmpBL(nodes a, nodes b) {
	if (a.yy == b.yy) return a.xx < b.xx;
	else return a.yy < b.yy;
}

bool cmpTL(nodes a, nodes b) {
	if (a.yy == b.yy) return a.xx < b.xx;
	else return a.yy > b.yy;
}

bool cmpTR(nodes a, nodes b) {
	if (a.yy == b.yy) return a.xx > b.xx;
	else return a.yy > b.yy;
}

bool cmpBR(nodes a, nodes b) {
	if (a.yy == b.yy) return a.xx > b.xx;
	else return a.yy < b.yy;
}

bool cmpX(nodes a, nodes b) {
	return a.xx < b.xx;
}
int BL[maxn], TL[maxn], TR[maxn], BR[maxn], se[maxn];
int ans1[maxn],ans2[maxn];
int main() {
	freopen("t.in", "r", stdin);
	int i, n, k, j, res;
	while (scanf("%d", &n) && n) {
		for (i = 1; i <= n; i++)
			scanf("%d%d", &node[i].xx, &node[i].yy), node[i].no = i;
		sort(node + 1, node + 1 + n, cmpX);
		node[1].x = 1;
		for (i = 2; i <= n; i++)
			if (node[i].xx == node[i - 1].xx)
				node[i].x = node[i - 1].x;
			else node[i].x = node[i - 1].x + 1;
		sort(node + 1, node + 1 + n, cmpBL);
		node[1].y = 1;
		for (i = 2; i <= n; i++)
			if (node[i].yy == node[i - 1].yy)
				node[i].y = node[i - 1].y;
			else node[i].y = node[i - 1].y + 1;
		k = 0, node[0].y = 19999999;
		node[0].x = n + 1;
		memset(tree1, 0, sizeof (tree1));
		for (i = 1; i <= n; i++) {
			if (node[i].y != node[k].y) {
				for (; k < i; k++)
					update1(node[k].x, n, 1);
			}
			BL[node[i].no] = sum1(node[i].x - 1);
			BR[node[i].no] = k - sum1(node[i].x) - 1;
			/* printf("%d %d===\n",k,sum1(node[i].x));
			 * printf("%d %d :BL %d BR %d \n",node[i].xx,node[i].yy,BL[node[i].no],BR[node[i].no]);*/
		}
		sort(node + 1, node + 1 + n, cmpTL);
		memset(tree1, 0, sizeof (tree1));
		k = 0, node[0].y = 1999999;
		node[0].x = n + 1;
		
		for (i = 1; i <= n; i++) {
			if (node[i].y != node[k].y) {
				for (; k < i; k++)
					update1(node[k].x, n, 1);
			}
			TL[node[i].no] = sum1(node[i].x - 1);
			TR[node[i].no] = k - sum1(node[i].x) - 1;
		//	printf("%d %d :TL %d TR %d \n",node[i].xx,node[i].yy,TL[node[i].no],TR[node[i].no]);
		}
		res = 0;
		int t = 0, temp;
		/*for (i=1;i<=n;i++)
		  {
		  temp = TR[node[i].no]+BL[node[i].no];
		  if (temp>res){
		  res = temp;
		  t = 0;
		  se[0] = TL[node[i].no]+BR[node[i].no];
		  }
		  else if (temp==res) se[t++] = TL[node[i].no]+BR[node[i].no];
		  }
		  sort(se,se+t);
		  int pos = unique(se,se+t)-se;
		for (i=0;i<t;i++)
		printf("%d ",se[i]);
		*/
		vector<int> mm;
		int ans = -1;
		int tmp, tt;
		sort(node + 1, node + 1 + n, cmpX);
		for (i=1;i<=n;i++)
		{
			ans1[i] = TR[node[i].no] + BL[node[i].no];
			ans2[i] = TL[node[i].no] + BR[node[i].no];
		}
		for (i = 1; i <= n; i++) {
			tt = ans1[i];
			j = i + 1;
			while (node[j].x == node[i].x&&j<=n) {
				if (tt > ans1[j])tt = ans1[j];
				++j;
			}
			if (tt == ans) {
				tmp = -1;
				for (k = i; k < j; k++)tmp = max(tmp, ans2[k]);
				mm.push_back(tmp);
			} else if (tt > ans) {
				ans = tt;
				mm.clear();
				tmp = -1;
				for (k = i; k < j; k++)tmp = max(tmp, ans2[k]);
				mm.push_back(tmp);
			}
			i = j - 1;
		}
		sort(mm.begin(), mm.end());
		printf("Stan: %d; Ollie:", ans);
		printf(" %d", mm[0]);
		tt = mm[0];
		for (i = 1; i < mm.size(); i++)
			if (mm[i] != tt) {
				printf(" %d", mm[i]);
				tt = mm[i];
			}
		printf(";\n");
		mm.clear();
	}
}
