#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N_MAX = 500100;
ll q1[N_MAX], q2[N_MAX];
int n;
int main()
{
	freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin >> n;
	int qh1 = 0, qt1 = 0, qh2 = 0, qt2 = 0;
	memset(q1, 0x3f, sizeof(q1));
	memset(q2, 0x3f, sizeof(q2));
	for(int i = 0; i < n; i ++)
		cin >> q1[qt1 ++];
	ll res = 0;
	while(qt1 - qh1 + qt2 - qh2 > 1)
	{
		ll val;
		if(qt1 - qh1 == 0 || q1[qh1] > q2[qh2 + 1])
		{
			val = q2[qh2] + q2[qh2 + 1];
			qh2 += 2;
		}
		else if(qt2 - qh2 == 0 || q2[qh2] > q1[qh1 + 1])
		{
			val = q1[qh1] + q1[qh1 + 1];
			qh1 += 2;
		}
		else
		{
			val = q1[qh1] + q2[qh2];
			qh1 ++, qh2 ++;
		}
		res += val;
		q2[qt2 ++] = val;
	}
	cout << res << '\n';
}
