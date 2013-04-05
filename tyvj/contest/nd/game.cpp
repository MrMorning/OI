#include <cstdio>
#include <algorithm>
using namespace std;
int log2[1 << 17];
int minST[100000][17], maxST[100000][17];
int val[100000];
int n;

void initMinST()
{
	for(int i = 0; i < n; i ++)
		minST[0][i] = val[i];
	for(int j = 1; (1 << j) <= n; j ++)
		for(int i = 0; i < n; i ++)
		{
			minST[j][i] = minST[j - 1][i];
			if(i + (1 << (j - 1)) < n && minST[j - 1][i + (1 << (j - 1))] < minST[j][i])
				minST[j][i] = minST[j - 1][i + (1 << (j - 1))];
		}
}

void initMaxST()
{
	for(int i = 0; i < n; i ++)
		maxST[0][i] = val[i];
	for(int j = 1; (1 << j) <= n; j ++)
		for(int i = 0; i < n; i ++)
		{
			maxST[j][i] = maxST[j - 1][i];
			if(i + (1 << (j - 1)) < n && maxST[j - 1][i + (1 << (j - 1))] > maxST[j][i])
				maxST[j][i] = maxST[j - 1][i + (1 << (j - 1))];
		}
}

int askMin(int l, int r)
{
	int k = log2[r - l + 1];
	return min(minST[k][l], minST[k][r - (1 << k) + 1]);
}

int askMax(int l, int r)
{
	int k = log2[r - l + 1];
	return max(maxST[k][l], maxST[k][r - (1 << k) + 1]);
}

int main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	for(int i = 0; i < 17; i ++)
		log2[1 << i] = i;
	for(int i = 1; i < 1 << 17; i ++)
		if(log2[i] == 0)
			log2[i] = log2[i - 1];
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &val[i]);
	initMinST();
	initMaxST();

	for(int i = 0; i < n; i ++)
	{
		if(i == 0 || i == n - 1)
		{
			printf("-1\n");
			continue;
		}
		if(val[i - 1] > val[i] || val[i + 1] > val[i])
		{
			printf("-1\n");
			continue;
		}

		int lb = -1, rb = i - 1;
		for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
			if(askMax(mid, i - 1) <= val[i])
				rb = mid;
			else
				lb = mid;

		int leftMin = askMin(rb, i - 1),
			leftMax = askMax(rb, i - 1);

		lb = i + 1, rb = n;
		for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
			if(askMax(i + 1, mid) <= val[i])
				lb = mid;
			else
				rb = mid;
		int rightMin = askMin(i + 1, lb),
			rightMax = askMax(i + 1, lb);
		printf("%d\n", max(abs(rightMin - leftMax), abs(rightMax - leftMin)));
	}
}
