#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 100001;
int rank[N_MAX], sa[N_MAX], height[N_MAX];

void radixSort(int *x, int *y, int n, int z){
	static int w[N_MAX];
	memset(w, 0, sizeof(int) * z);
	for(int i = 0; i < n; i ++) 
		w[x[y[i]]] ++;
	for(int i = 1; i < z; i ++) 
		w[i] += w[i - 1];
	for(int i = n - 1; i >= 0; i --) 
		sa[-- w[x[y[i]]]] = y[i];
}

inline bool isEqual(int *x, int i, int j, int l){
	return x[i] == x[j] && x[i + l] == x[j + l];
}

void initSA(char *s, int n, int z){
	int i;
	static int _x[N_MAX], _y[N_MAX];
	int *x = _x, *y = _y;
	for(i = 0; i < n; i ++) x[i] = s[i], y[i] = i;
	radixSort(x, y, n, z);
	for(int len = 1, p; p < n; z = p, len <<= 1){
		for(p = 0, i = n - len; i < n; i ++) 
			y[p ++] = i;
		for(i = 0; i < n; i ++) 
			if(sa[i] >= len) 
				y[p ++] = sa[i] - len;
		radixSort(x, y, n, z);
		for(swap(x, y), x[sa[0]] = 0, p = 1, i = 1; i < n; i ++)
			x[sa[i]] = isEqual(y, sa[i - 1], sa[i], len) ? p - 1 : p ++;
	}
}

void initHeight(char *s, int n){
	for(int i = 0; i < n; i ++) 
		rank[sa[i]] = i;
	for(int i = 0, k = 0, j; i < n; height[rank[i ++]] = k)
		if(rank[i]) 
			for(k ? k -- : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k ++);
}

int main(){
}
