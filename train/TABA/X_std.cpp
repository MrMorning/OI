#include <cstdio>
#include <cstring>
#include <algorithm>
using std::sort;
const int maxn=100100,maxm=maxn+maxn;
struct tree{
	int head[maxn],link[maxm],next[maxm],w[maxm],pr[maxm],num[maxm],s,t,tot,n;
	int res[maxn],d[maxn],f[maxn],far[maxn],core1,core2,ebc,root;
	int ans[maxn],len;
	bool v[maxn],onway[maxn];
	void findfar(int p){
		far[p]=res[p]=0;
		for (int i=head[p];i;i=next[i])
			if (d[p]+w[i]<d[link[i]]){
				d[link[i]]=d[p]+w[i];
				findfar(link[i]);
				if (far[link[i]]+w[i]>far[p]){
					res[p]=i;
					far[p]=far[link[i]]+w[i];
				}
			}
	}
	int getfar(int p){
		memset(d,0x3f,sizeof(d));
		d[p]=0;
		findfar(p);
		int i;
		for (i=p;res[i];i=link[res[i]])
			onway[i]=true;
		onway[i]=true;
		return i;
	}
	void getcore(){
		root=getfar(1);
		int leaf=getfar(root);
		for (int i=root;res[i];i=link[res[i]])
			if (d[link[res[i]]]+d[link[res[i]]]==d[leaf]){
				core1=link[res[i]];core2=-1;
				break;
			}else
				if (d[link[res[i]]]+d[link[res[i]]]>d[leaf]){
					core1=i;core2=link[res[i]];ebc=res[i];
					break;
				}
	}
	void treedp(int p){
		f[p]=0;
		for (int i=head[p];i;i=next[i])
			if (far[link[i]]+w[i]==far[p]){
				treedp(link[i]);
				if (pr[i]<=f[link[i]])
					f[p]+=pr[i];
				else
					f[p]+=f[link[i]];
			}
		if (f[p]==0) f[p]=0x3f3f3f3f;
	}
	void dpans(int p){
		for (int i=head[p];i;i=next[i])
			if (far[link[i]]+w[i]==far[p]){
				treedp(link[i]);
				if (pr[i]<=f[link[i]])
					ans[++len]=num[i];
				else
					dpans(link[i]);
			}
	}
	int mincost(){
		getcore();
		if (core2!=-1){
			memset(d,0x3f,sizeof(d));
			d[core1]=0;d[core2]=0;far[core2]=-0x3f3f3f3f;
			findfar(core1);
			treedp(core1);
			far[core1]=-0x3f3f3f3f;
			findfar(core2);
			treedp(core2);
			if (pr[ebc]<f[core1]&&pr[ebc]<f[core2]){
				len=1;
				ans[len]=num[ebc];
				return pr[ebc];
			}
			if (f[core1]<f[core2]){
				memset(d,0x3f,sizeof(d));
				d[core1]=0;d[core2]=0;far[core2]=-0x3f3f3f3f;
				findfar(core1);
				len=0;
				dpans(core1);
				return f[core1];
			}
			len=0;
			dpans(core2);
			return f[core2];
		}
		memset(d,0x3f,sizeof(d));
		d[core1]=0;
		findfar(core1);
		treedp(core1);
		int max=0,maxson;
		for (int i=head[core1];i;i=next[i])
			if (far[link[i]]+w[i]==far[core1]){
				int min=pr[i];
				if (f[link[i]]<min) min=f[link[i]];
				if (min>max){
					max=min;
					maxson=link[i];
				}
			}
		far[maxson]=-0x3f3f3f3f;
		treedp(core1);
		len=0;
		dpans(core1);
		return f[core1];
	}
	void add(int a,int b,int ww,int pp,int n){
		next[++tot]=head[a];
		head[a]=tot;
		link[tot]=b;
		w[tot]=ww;
		pr[tot]=pp;
		num[tot]=n;
		next[++tot]=head[b];
		head[b]=tot;
		link[tot]=a;
		w[tot]=ww;
		pr[tot]=pp;
		num[tot]=n;
	}
	void init(){
		memset(head,0,sizeof(head));
		tot=0;
	}
} g;
int main(){
	int n;
	freopen("t.in","r",stdin);
	scanf("%d",&n);
	g.init();
	for (int i=1;i<n;i++){
		int x,y,z,w;
		scanf("%d%d%d%d",&x,&y,&z,&w);
		g.add(x,y,z,w,i);
	}
	printf("%d\n",g.mincost());
/*	printf("%d\n",g.len);
	sort(g.ans+1,g.ans+g.len+1);
	for (int i=1;i<=g.len;i++)
		printf("%d ",g.ans[i]);
	puts("");
*/	return 0;
}
