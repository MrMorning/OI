#include<iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int a[7],sum,b[100],n;

int f[60002];

int main()

{
	freopen("t.in", "r", stdin);
	freopen("test1", "w", stdout);
	int i,j,cas=1,k;

	while(scanf("%d%d%d%d%d%d",&a[1],&a[2],&a[3],&a[4],&a[5],&a[6])==6)

	{

		if((a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6])==0)

			break;

		printf("Collection #%d:\n",cas++);

		sum=0;

		n=0;

		for(i=1;i<=6;i++)

		{

			sum+=a[i]*i;

			k=0;

			for(j=0;(1<<j)<a[i];j++)

			{

				b[n++]=(1<<j)*i;

				k+=(1<<j)*i;

			}

			if(a[i]>k)

				b[n++]=(a[i]-k)*i;

		}

		if(sum%2)

		{

			printf("Can't be divided.\n\n");

			continue;

		}

		memset(f,0,sizeof(f));

		f[0]=1;

		for(i=0;i<n;i++)

		{

			for(j=sum/2;j>=b[i];j--)

			{

				if(f[j-b[i]])

					f[j]=1;

			}

		}

		if(f[sum/2])

			printf("Can be divided.\n\n");

		else

			printf("Can't be divided.\n\n");

	}

	return 0;

}
