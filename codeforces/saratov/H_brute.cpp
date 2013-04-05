#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
const int N_MAX = 200, K_MAX = 300;
map<string, int> strMap;
string toStr[N_MAX * K_MAX];
bool choose[N_MAX * K_MAX];
bool done[N_MAX];
int may[N_MAX][K_MAX], mayCnt[N_MAX];
int love[N_MAX], perm[N_MAX];
int stat[N_MAX * K_MAX], ptr[N_MAX * K_MAX];
int N;
int strIdx;

int countBits(int x){
	int res = 0;
	while(x)
		res += x & 1, x >>= 1;
	return res;
}

void dfs(int i){
	/*static int time = 0;
	time ++;
	if(time > 1000000){
		printf("-1\n");
		exit(0);
	}*/
	if(i == N){
		for(int k = 0; k < N; k ++)
			cout << toStr[love[k]] << '\n';
		exit(0);
	}
	int x = perm[i];
	if(done[x]){
		dfs(i + 1);
		return;
	}
	for(int k = 0; k < mayCnt[x]; k ++)
		if(!choose[may[x][k]]){
			love[x] = may[x][k];
			choose[may[x][k]] = true;
			dfs(i + 1);
			choose[may[x][k]] = false;
		}
}

bool cmp(const int &a, const int &b){
	return mayCnt[a] < mayCnt[b];
}

bool cmp2(const int &a, const int &b){
	return toStr[a].length() > toStr[b].length();
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &N);
	for(int i = 0; i < N; i ++){
		string str;
		cin >> str;
		int upperlim = str.size();
		for(int s = 0; s < 1 << upperlim; s ++)
			if(1 <= countBits(s) && countBits(s) <= 4){
				string ts("");
				for(int d = 0; d < (int)str.size(); d ++)
					if(s & (1 << d))
						ts += str[d];
				if(strMap.count(ts) == 0){
					strMap[ts] = strIdx;
					toStr[strIdx] = ts;
					strIdx ++;
				}
				may[i][mayCnt[i] ++] = strMap[ts];
			}
		sort(may[i], may[i] + mayCnt[i]);
		mayCnt[i] = unique(may[i], may[i] + mayCnt[i]) - may[i];
		random_shuffle(may[i], may[i] + mayCnt[i]);
		for(int j = 0; j < mayCnt[i]; j ++)
			stat[may[i][j]] ++, ptr[may[i][j]] = i;
	}
	for(int i = 0; i < strIdx; i ++)
		if(stat[i] == 1)
			done[ptr[i]] = true, love[ptr[i]] = i;
	for(int i = 0; i < N; i ++)
		perm[i] = i;
	sort(perm, perm + N, cmp);
	dfs(0);
	printf("-1\n");
}
