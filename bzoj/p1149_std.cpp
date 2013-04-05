#include"cstdio"
#include"cstdlib"
#include"algorithm"

using namespace std;

int n,s[100010][2],l[100010],h[100010],ans;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d %d",&s[i][0],&s[i][1]);
	for(int i=n;i>0;i--)
	{
		int l1,l2,h1,h2;
		if(s[i][0]==-1)l1=h1=0;
		else l1=l[s[i][0]],h1=h[s[i][0]];
		if(s[i][1]==-1)l2=h2=0;
		else l2=l[s[i][1]],h2=h[s[i][1]];
		l[i]=min(l1,l2)+1;
		h[i]=max(h1,h2)+1;
		if(h[i]-l[i]>1)
		{
			printf("-1\n");
			return 0;
		}
		if(h1<h2||l1<l2)
		{
			swap(l1,l2);
			swap(h1,h2);
			ans++;
		}
		if(h2>l1)
		{
			printf("-1\n");
			return 0;
		}
	}
	printf("%d\n",ans);
	return 0;
}
