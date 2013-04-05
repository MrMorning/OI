#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define BASE 100007
#define N_MAX 111111
#define INV(x) (N - (x) + 1)
int pow[N_MAX], log2[N_MAX];
int res[N_MAX], rad[N_MAX], rad2[N_MAX];
char str[N_MAX], pal[N_MAX];
struct Hash{
	int presum[N_MAX];
	void init(char str[], int len){
		presum[0] = 0;
		for(int i = 1; i <= len; i ++)
			presum[i] = presum[i - 1] * BASE + str[i];
	}
	int get(int l, int r){
		return presum[r] - presum[l - 1] * pow[r - l + 1];
	}
} hash[2];

struct ST{
	int f[17][N_MAX], a[N_MAX];
	void init(int _a[], int n){
		memcpy(a + 1, _a + 1, sizeof(int) * n);
		for(int i = 1; i <= n; i ++)
			f[0][i] = i;
		for(int j = 1; 1 << j <= n; j ++)
			for(int i = 1; i <= n; i ++){
				f[j][i] = f[j - 1][i];
				int p = i + (1 << (j - 1));
				if(p > n)
					continue;
				if(a[f[j - 1][p]] < a[f[j][i]])
					f[j][i] = f[j - 1][p];
			}
	}
	int ask(int l, int r){
		int len = log2[r - l + 1];
		int k = 1 << len;
		int res = f[len][l];
		if(a[f[len][r - k + 1]] < a[res])
			res = f[len][r - k + 1];
		return res;
	}
} rmq[2];

void solve(){
	static char _str[N_MAX];
	scanf("%s", _str);
	int N = strlen(_str);
	for(int i = 1; i <= N; i ++)
		str[i] = _str[i - 1], pal[i] = _str[N - i];
	hash[0].init(str, N);
	hash[1].init(pal, N);
	for(int i = 1; i <= N; i ++){
		int lb = 1, rb = min(i, N - i + 1) + 1, mid = (lb + rb) >> 1;
		//[lb, rb)
		while(lb < rb - 1){
			if(hash[0].get(i - mid + 1, i) == hash[1].get(INV(i + mid - 1), INV(i)))
				lb = mid;
			else
				rb = mid;
			mid = (lb + rb) >> 1;
		}
		rad[i] = lb;
	}
	for(int i = 1; i < N; i ++){
		int lb = 0, rb = min(i, N - i) + 1, mid = (lb + rb) >> 1;
		//[lb, rb)
		while(lb < rb - 1){
			if(hash[0].get(i - mid + 1, i) == hash[1].get(INV(i + mid), INV(i + 1)))
				lb = mid;
			else
				rb = mid;
			mid = (lb + rb) >> 1;
		}
		rad2[i] = lb;
	}
	rmq[0].init(rad, N);
	rmq[1].init(rad2, N - 1);

	for(int L = 1; L <= N; L ++){
		if(L & 1){
			int lb = L / 2, rb = N - L / 2, mid = (lb + rb) >> 1;
			//(lb, rb]
			while(lb < rb - 1){
				if(2 * rad[rmq[0].ask(L / 2 + 1, mid)] - 1 < L)
					rb = mid;
				else
					lb = mid;
				mid = (lb + rb) >> 1;
			}
			if(2 * rad[rmq[0].ask(L / 2 + 1, rb)] - 1 < L)
				res[L] = rb - L / 2;
			else
				res[L] = 0;
		}
		else{
			int lb = L / 2 - 1, rb = N - L / 2, mid = (lb + rb) >> 1;
			//(lb, rb]
			while(lb < rb - 1){
				if(2 * rad2[rmq[1].ask(L / 2, mid)] < L)
					rb = mid;
				else
					lb = mid;
				mid = (lb + rb) >> 1;
			}
			if(2 * rad2[rmq[1].ask(L / 2, rb)] < L)
				res[L] = rb - L / 2 + 1;
			else
				res[L] = 0;
		}
	}
	unsigned long long ans = 0, acc = 1;
	for(int i = 1; i <= N; i ++){
		ans += acc * res[N - i + 1];
		acc *= 100007;
	}
	cout << ans << '\n';
}

int main(){
	pow[0] = 1;
	for(int i = 1; i <= 100000; i ++)
		pow[i] = BASE * pow[i - 1];
	for(int i = 0; 1 << i <= 100000; i ++)
		log2[1 << i] = i;
	for(int i = 1; i <= 100000; i ++)
		if(log2[i] == 0)
			log2[i] = log2[i - 1];
	int T;
	scanf("%d", &T);
	while(T --)
		solve();
}
