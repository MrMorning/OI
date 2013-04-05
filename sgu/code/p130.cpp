#include <iostream>
using namespace std;
typedef long long ll;
ll f[31];
int n;
int main()
{
	cin >> n;
	f[0] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j < i; j ++)
			f[i] += f[j] * f[i - j - 1];
	cout << f[n] << ' ' << n + 1;
}
