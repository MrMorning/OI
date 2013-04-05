#include<cstdio>
#include<cstring>
#define maxn 200010
using namespace std;
int n,g[maxn];
struct Bignum
{
	int len;
	long long l[10000];
	long long M;
	Bignum()
	{
		len=1;
		l[0]=0;
		M=1000000000LL;
	}
	inline void operator += (const long long &x)
	{
		long long s=x;
		for(int i=0; i<len; i++)
		{
			l[i]+=s%M;
			s=s/M+l[i]/M;
			l[i]%=M;
			if(!s)return ;
		}
		while(s)l[len++]=s%M,s/=M;
	}
	inline void operator += (const Bignum &b)
	{
		long long x=0;
		for(int i=0; i<len; i++)
		{
			if(i<b.len)x=l[i]+b.l[i]+x;
			else x=l[i]+x;
			l[i]=x%M;
			x/=M;
		}
		for(int i=len; i<b.len; i++)
		{
			x=b.l[i]+x;
			l[i]=x%M;
			x/=M;
		}
		len=b.len>len?b.len:len;
		while(x)l[len++]=x%M,x/=M;
	}
	Bignum operator * (const Bignum &b)
	{
		Bignum ret;
		for(int i=0; i<=len+b.len; i++)
			ret.l[i]=0;
		for(int i=0; i<len; i++)
			for(int j=0; j<b.len; j++)
			{
				ret.l[i+j]+=l[i]*b.l[j];
				ret.l[i+j+1]+=ret.l[i+j]/M;
				ret.l[i+j]%=M;
			}
		ret.len=len+b.len-1;
		while(ret.l[ret.len]) ret.len++;
		return ret;
	}
	Bignum operator * (const int &x)
	{
		Bignum ret;
		long long s=0;
		ret.len=len;
		for(int i=0;i<len;i++)
		{
			s=x*l[i]+s;
			ret.l[i]=s%M;
			s/=M;
		}
		while(s)ret.l[ret.len++]=s%M,s/=M;
		return ret;
	}
	inline void operator /= (const int &x)
	{
		long long s=0;
		for(int i=len-1; i>=0; i--)
		{
			s=s*M+l[i];
			l[i]=s/x;
			s%=x;
		}
		while(!l[len-1]) len--;
	}
	inline void print()
	{
		for(int i=len-1; i>=0; i--)
			if(i!=len-1)printf("%09lld",l[i]);
			else printf("%lld",l[i]);
	}
}ans;
int gcd(int x,int y)
{
	if(x<y) x^=y,y^=x,x^=y;
	while(y)
	{
		x%=y;
		x^=y,y^=x,x^=y;
	}
	return x;
}
void pow(int x)
{
	Bignum ret,tmp;
	tmp.l[0]=2,ret.l[0]=1;
	int re=0,tm=1;
	while(x)
	{
		if(x&1)
		{
			ret=ret*tmp,re+=tm;
			if(g[re])
				ans+=ret*g[re],g[re]=0;
		}
		tmp=tmp*tmp;
		tm*=2;
		if(tm<=n&&g[tm])
			ans+=tmp*g[tm],g[tm]=0;
		x>>=1;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=n; i>=1; i--)
		g[gcd(i,n)]++;
	for(int i=n; i>=0; i--)
		if(g[i])
			pow(i);
	ans/=n;
	ans.print();
	return 0;
}
