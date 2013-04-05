/*
 * $Date: Thu Jan 26 21:54:06 2012 +0800
 * $Author: csimstu
 * $Source: ZOJ Monthly, January 2011 Problem J The Hive II
 * $Method: Plug-DP
 */
#include <cassert>
#include <cstdio>
#include <vector>
#include <cstring>
#define foreach(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it ++)

using namespace std;

typedef int mask_t;
typedef pair<mask_t, int> hash_t;
typedef long long int64;
#define INT64_FMT "%lld"

const int N_MASK_MAX = 20000;

const int ODD[4] = {0, 4, 8, 12};
const int EVEN[4] = {2, 6, 10, 14};

vector<int> trans[8];

struct HashTable{
#define MOD 16384
	vector<hash_t> ele[MOD];
	void clear(){
		for(int i = 0; i < MOD; i ++)
			ele[i].clear();
	}
	int& operator[] (int x){
		int code = x & (MOD - 1);
		int n = ele[code].size();
		for(int i = 0; i < n; i ++)
			if(ele[code][i].first == x)
				return ele[code][i].second;
		ele[code].push_back(make_pair(x, -1));
		return ele[code][n].second;
	}
} hash;

int nrow, nobs;
bool isObs[11][11];
int64 f[2][N_MASK_MAX];
int toMask[N_MASK_MAX];
int maskCnt;
int cur;

int fetch(mask_t s){
	int &res = hash[s];
	if(res == -1){
		toMask[maskCnt] = s;
		res = maskCnt;
		maskCnt ++;
	}
	return res;
}
void roll(){
	memset(f[cur], 0, sizeof(f[cur]));
	cur ^= 1;
}

void modify(int &x, int k, int v){
	if(((x & (1 << k)) > 0) == v)
		return;
	x ^= 1 << k;
}

void expand(mask_t s, int j, int p, const int OFFSET[]){
	foreach(np, trans[p]){
		int ns = s;
		for(int t = 0; t < 3; t ++)
			modify(ns, OFFSET[j] + t, (*np & (1 << t)) > 0);
		if(!(ns & (1 << 16)) && !(ns & 1))
			f[!cur][fetch(ns)] += f[cur][fetch(s)];
	}
}

void work(){
	maskCnt = 0;
	hash.clear();
	memset(isObs, 0, sizeof(isObs));
	while(nobs --){
		static char str[4];
		scanf("%s", str);
		isObs[str[0] - 'A'][str[1] - 'A'] = true;
	}
	cur = 0;
	memset(f[cur], 0, sizeof(f[cur]));
	f[cur][fetch(0)] = 1;
	for(int i = 0; i < nrow; i ++){
		for(int j = 0; j < 4; j ++, roll())
			for(int k = 0, tot = maskCnt; k < tot; k ++){
				if(!f[cur][k])
					continue;
				int s = toMask[k];
				int p = (s >> EVEN[j]) & 7;
				if(!isObs[i][j * 2 + 1])
					expand(s, j, p, EVEN);
				else if(p == 0)
					f[!cur][k] += f[cur][k];
			}
		for(int j = 0; j < 4; j ++, roll())
			for(int k = 0, tot = maskCnt; k < tot; k ++){
				if(!f[cur][k])
					continue;
				int s = toMask[k];
				int p = (s >> ODD[j]) & 7;
				if(!isObs[i][j * 2])
					expand(s, j, p, ODD);
				else if(p == 0)
					f[!cur][k] += f[cur][k];
			}
	}
	printf(INT64_FMT "\n", f[cur][fetch(0)]);
}

void addTrans(int a, int b){
	trans[a].push_back(b);
}

int main(){
	freopen("t.in", "r", stdin);
	addTrans(0, 5); addTrans(0, 6); addTrans(0, 3);
	addTrans(1, 1); addTrans(1, 2); addTrans(1, 4);
	addTrans(2, 1); addTrans(2, 2); addTrans(2, 4);
	addTrans(4, 1); addTrans(4, 2); addTrans(4, 4);
	addTrans(5, 0); addTrans(6, 0); addTrans(3, 0);

	while(scanf("%d%d", &nrow, &nobs) != EOF){
		work();
	}
}
