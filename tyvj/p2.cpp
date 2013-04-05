#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using std::swap;

int m, n, k;
int prime[500], primeCnt;
bool checked[1000000];
int ans = 0;

inline int min(int a, int b)
{
	return a < b ? a : b;
}

inline int max(int a, int b)
{
	return a > b ? a : b;
}

inline int abs(int x)
{
	return x > 0 ? x : -x;
}

void initPrime()
{
	int hash[1001];
	memset(hash, 1, sizeof(hash));
	for(int i = 2; i <= 1000; i ++)
		if(hash[i])
		{
			prime[++ primeCnt] = i;
			for(int j = i; j <= 1000; j += i)
				hash[j] = false;
		}
}

void solveDiv()
{
	ans = n - m + 1;
	memset(checked, 0, sizeof(checked));
	for(int i = m; i <= n; i ++)
	{
		if(checked[i])
			continue;
		checked[i] = true;
		int t = i * k;
		if(t > n)
			break;
		bool flag = false;
		while(m <= t && t <= n && ! checked[t])
		{
			if(flag)
				ans --;
			flag = ! flag;
			checked[t] = true;
			t *= k;
		}
	}
}

int cnt[500];
void search(int i, int num)
{
	if(i > primeCnt || num > n)
		return;
	ans += num != k/num && !checked[num] && m <= num && num <= n &&!checked[k/num] && m <= k/num && k/num <= n;
	checked[num] = checked[k/num] = true;
	if(cnt[i])
	{
		int tmp = 1;
		for(int t = 1; t <= cnt[i]; t ++)
		{
			tmp *= prime[i];
			search(i + 1, num * tmp);
		}
	}
	search(i + 1, num);
}

void solvePlus()
{
	ans = n - m + 1 - max(0, min((k-2*m+1)/2, (2*n-k+1)/2));
}

void solveMinus()
{
	int tmp = n - m + 1;
	int more = tmp % k;
	ans = (tmp / k + 1) / 2 * k;
	if(tmp/k % 2 == 0)
		ans += more;
}

void solveMulti()
{
	int tmp = k;
	ans = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(checked, 0, sizeof(checked));
	for(int i = 1; i <= primeCnt; i ++)
		while(tmp % prime[i] == 0)
			tmp /= prime[i], cnt[i] ++;
	if(tmp != k) // is a large prime
	{
		search(1, 1);
	}
	ans = n - m + 1 - ans;
}

int main()
{
	freopen("t.in", "r", stdin);
	initPrime();
	int testNum;
	scanf("%d\n", &testNum);
	for(int i = 1; i <= testNum; i ++)
	{
		char ch;
		scanf("%c %d %d %d\n", &ch, &k, &m, &n);
		switch(ch)
		{
			case '+':
				solvePlus();
				break;
			case '-':
				solveMinus();
				break;
			case '*':
				solveMulti();
				break;
			case '/':
				solveDiv();
				break;
		}
		printf("%d\n", ans);
	}
}
