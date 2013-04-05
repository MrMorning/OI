#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll n;
int main()
{
//	freopen("t.in", "r", stdin);
	cin >> n;
	if(n == 1)
		printf("0\n");
	else if(n <= 3)
		printf("1\n");
	else 
	{
		int cnt = 0;
		for(ll x = 0; (1LL << x) <= n; x ++)
			n -= (1LL << x), cnt ++;
		cnt += n != 0;
		printf("%d\n", cnt - 2);
	}
}
