#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll n;
ll ans[48];
int main()
{
	for(int x = 0; x < 48; x ++)
		ans[x] = (ll)(x + 1) * (1LL << (x + 1));
	cin >> n;
	int lb = 0, rb = 48;
	for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
		if(ans[mid] <= n + 1)
			lb = mid;
		else
			rb = mid;
	if(ans[lb] != n + 1)
		printf("%d\n", lb + 1);
	else
		printf("%d\n", lb);
}
