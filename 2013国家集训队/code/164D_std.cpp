#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i,a,b) for (int i=a;i<b;i++)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
int n,k,l,r,x[1010],y[1010],d[1010][1010],fg[1010];
vector<int> p,e[1010];
bool dfs(int u,int k) {
	if (u==n) return 1;
	if (fg[u]>0) return dfs(u+1,k);
	foreach(it, e[u]) {
		int v = *it;
		k-=(!fg[v]++);
	}
	if (k>=0&&dfs(u+1,k))return 1;
	fg[u]=1;int t=k;
	foreach(it, e[u]) {
		int v = *it;
		k+=(!--fg[v]);
	}
	if ((--k>=0)&&k>t&&dfs(u+1,k)) return 1;
	fg[u]=0;
	return 0;
}
bool check(int dis) {
	rep(i,0,n) fg[i]=0,e[i].clear();
	rep(i,0,n) rep(j,0,n) if (d[i][j]>dis) e[i].push_back(j);
	return dfs(0,k);
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d",&n,&k);
	rep(i,0,n) scanf("%d%d",x+i,y+i);
	rep(i,0,n) rep(j,i+1,n)
		p.push_back(d[i][j]=d[j][i]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
	sort(p.begin(),p.end());
	p.erase(unique(p.begin(),p.end()),p.end());
	l=-1;r=p.size();
	while (l+1<r) {
		int md=(l+r)>>1;
		if (check(p[md])) r=md; else l=md;
	}
	check(p[r]);
	printf("%d\n", p[r]);
	//rep(i,0,n) if (fg[i]) printf("%d ",i+1),--k;
	//rep(i,0,n) if (!fg[i]&&k) printf("%d ",i+1),--k;
}
