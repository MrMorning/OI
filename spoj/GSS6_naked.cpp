#include <cstdio>
#include <algorithm>
#define MAXN 100100
#define FOR(i,s,t) for(int i = s; i <= t ;i ++)
using namespace std;

int n,m,A[MAXN];


int main()
{
	freopen("t.in","r",stdin);
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	scanf("%d",&m);
	FOR(i,1,m)
	{
		int x,y;
		char opt;
		scanf("\n%c %d",&opt,&x);
		if(opt != 'D') scanf("%d",&y);
		switch(opt)
		{
			case 'I':
				{
					n++;
					for(int i = n ; i >= x; i --)
						A[i] = A[i-1];
					A[x] = y;
					break;
				}
			case 'Q':
				{
					int ans = -0x3f3f3f3f;
					FOR(s,x,y)
						FOR(t,s,y)
						{
							int sum = 0;
							FOR(j,s,t)
								sum += A[j];
							ans = max(sum, ans);
						}
					printf("%d\n",ans);
					break;
				}
			case 'D':
				{
					for(int i = x+1	; i <= n; i ++)
						A[i-1] = A[i];
					n--;
					break;
				}
			case 'R':
				A[x]=y;
				break;
		}
	}

}
