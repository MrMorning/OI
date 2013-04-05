#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> boy[2], girl[2];
int N;

int main(){
	scanf("%d", &N);
	for(int i = 1; i <= N; i ++){
		int x;
		scanf("%d", &x);
		if(x < 0)
			boy[0].push_back(-x);
		else 
			girl[1].push_back(x);
	}
	for(int i = 1; i <= N; i ++){
		int x;
		scanf("%d", &x);
		if(x > 0)
			girl[0].push_back(x);
		else 
			boy[1].push_back(-x);
	}
	int ans = 0;
	for(int t = 0; t <= 1; t ++){
		sort(boy[t].begin(), boy[t].end());
		sort(girl[t].begin(), girl[t].end());
		int p = boy[t].size(),
			q = girl[t].size();
		int j = q - 1;
		for(int i = p - 1; i >= 0; i --){
			while(j >= 0 && boy[t][i] <= girl[t][j])
				j --;
			if(j == -1)
				break;
			ans ++;
			j --;
		}
	}
	printf("%d\n", ans);
}
