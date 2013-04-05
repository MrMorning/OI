#include <cstdio>
int N;
int a[111111];

void reverse(int l, int r){
	static int b[111111];
	for(int i = l; i <= r; i ++)
		b[i] = a[r - i + l];
	for(int i = l; i <= r; i ++)
		a[i] = b[i];
}

bool sorted(){
	for(int i = 2; i <= N; i ++)
		if(a[i] < a[i - 1])
			return false;
	return true;
}

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d", &N);
	for(int i = 1; i <= N; i ++)
		scanf("%d", &a[i]);
	long long ans = 0;
	while(!sorted()){
		for(int i = 1; i <= N; i ++){
			int j = i;
			while(i < N && a[i + 1] < a[i])
				i ++;
			if(i > j)
				reverse(j, i), ans ++;
		}
	}
	printf("%lld\n", ans);
}
