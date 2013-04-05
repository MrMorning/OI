#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n, k;
int w[111], arr[111], nArr;
bool used[111];
double adjust(double x){
	return fabs(x) < 10e-6 ? 0 : x;
}
int main(){
	scanf("%d%d", &n, &k);
	int m = n / k;
	for(int i = 1; i <= n; i ++)
		scanf("%d", &w[i]);
	int q;
	scanf("%d", &q);
	double resMin = 10e100, resMax = -10e100;
	for(int i = 1; i <= q; i ++){
		int acc = 0;
		for(int j = 1, x; j <= m; j ++){
			scanf("%d", &x);
			used[x] = true;
			acc += w[x];
		}
		resMax = max(resMax, (double)acc / m);
		resMin = min(resMin, (double)acc / m);
	}
	for(int i = 1; i <= n; i ++)
		if(!used[i])
			arr[nArr ++] = w[i];
	if((n - nArr) / m < k){
		sort(arr, arr + nArr);
		int tmp = 0;
		for(int i = 0; i < m; i ++){
			tmp += arr[i];
		}
		resMin = min(resMin, (double)tmp / m);
		tmp = 0;
		for(int i = nArr - 1; i >= nArr - m; i --)
			tmp += arr[i];
		resMax = max(resMax, (double)tmp / m);
	}
	printf("%.8lf %.8lf\n", adjust(resMin), adjust(resMax));
}
