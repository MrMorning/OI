#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll x;
int n, y;

int main()
{
	cin >> n >> x >> y;
	if(y < n || (ll)(y - n + 1) * (y - n + 1) + n - 1 < x)
		cout << -1;
	else
	{
		cout << y - n + 1 << '\n';
		for(int i = 1; i < n; i ++)
			cout << 1 << '\n';
	}
}
