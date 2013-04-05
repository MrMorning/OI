/*
 *  * By VanishVam
 *   * O(N)
 *    */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxN = 1000111;
const int infinity = 0x7f7f7f7f;

int N;
int X[maxN],Y[maxN],Z[maxN],sum[maxN];
int ans(infinity);

int main()
{
//#ifndef ONLINE_JUDGE
	freopen("bridge.in","r",stdin);
	//freopen("bridge.out","w",stdout);
//#endif

	scanf("%d",&N);
	for(int i = 1;i < N;++i) scanf("%d",X+i);
	for(int i = 1;i < N;++i) scanf("%d",Y+i);
	for(int i = 1;i < N;++i) scanf("%d",sum+i);
	for(int i = 0;i < N;++i)
	{
		scanf("%d",Z+i);
		if(i!=0) sum[i]+=sum[i-1]+Z[i];
	}
	Y[1] = min(Y[1],Z[0]);
	X[N-1]=min(X[N-1],Z[N-1]);

	int imin(infinity);
	for(int i = N-1;i >= 1;--i)
	{
		imin = min(imin,(sum[i]-Z[i])+X[i]);//-Z[i] is necessary!
		ans  = min(ans ,imin-sum[i-1]+Y[i]);
	}

	imin = Y[N-1];
	for(int i = N-2;i >= 1;--i)
	{
		ans = min(ans,X[i]+imin);
		imin = min(imin,Y[i]);
	}

	printf("%d\n",ans);
	return 0;
}

