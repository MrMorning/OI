#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

vector<int> ans;
int a[222222];
int n, sum;

int main(){
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%d", &a[i]);
		sum += a[i];
	}
	for(int i = 0; i < n; i ++){
		if(fabs((double)(sum - a[i]) / (n - 1) - a[i]) < 10e-6)
			ans.push_back(i);
	}
	printf("%d\n", ans.size());
	for(int i = 0; i < ans.size(); i ++)
		printf("%d ", ans[i] + 1);
}
