#include<stdio.h>
#include<math.h>

int num[10001];
double asset[10001][11],m[11],s[11],v[11],w[11],S[11][11];
int main()
{
	int n,t,i,j,k;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d",&t,&n);
	for(i=0;i<n;++i)
		scanf("%d",&num[i]);
	for(i=0;i<=t;++i)
		for(j=0;j<n;++j)
		{
			scanf("%lf",&asset[i][j]);
			asset[i][j]*=num[j];
		}
	double vp=0;
	for(i=0;i<n;++i)
	{
		v[i]=asset[0][i];
		vp+=v[i];
	}

	for(i=t;i>0;--i)
		for(j=0;j<n;++j)
			asset[i][j]=(asset[i-1][j]-asset[i][j])/asset[i][j];
	for(i=0;i<n;++i)
	{
		for(j=1;j<=t;++j)
			m[i]+=asset[j][i];
		m[i]/=t;
		for(j=1;j<=t;++j)
			s[i]+=(asset[j][i]-m[i])*(asset[j][i]-m[i]);
		s[i]=sqrt(s[i]/t);
	}

	double mp=0;
	for(i=0;i<n;++i)
	{
		w[i]=v[i]/vp;
		mp+=w[i]*m[i];
	}

	for(i=0;i<n;++i)
		for(j=i;j<n;++j)
		{
			double ans=0;
			for(int k=1;k<=t;++k)
				ans+=(asset[k][i]-m[i])*(asset[k][j]-m[j]);
			S[i][j]=S[j][i]=ans/t;
		}

	double sp=0;
	for(i=0;i<n;++i)
	{
		double ws=0;
		for(j=0;j<n;++j)
			ws+=w[j]*S[i][j];
		sp+=ws*w[i];
	}
	sp=sqrt(sp);
	printf("%.2lf\n",-vp*(mp-1.644854*sp));
	return 0;
}
