#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long int64;

const int N_MAX = 500;
const int64 INF = 0x3f3f3f3f3f3f3f3fLL;


int nbee;
int64 pos[N_MAX], dir[N_MAX];
int meet[N_MAX];

struct Query{
	int64 time;
	int bee, idx;
	bool operator< (const Query &t) const{
		return time < t.time;
	}
} query[1000];
int nquery;
pair<int64, int> ans[1000];

void solve(){
	scanf("%d", &nbee);
	for(int i = 0; i < nbee; i ++){
		scanf("%lld", &pos[i]);
		pos[i] *= 2;
	}
	for(int i = 0; i < nbee; i ++){
		scanf("%lld", &dir[i]);
		if(dir[i] == 0)
			dir[i] = -1;
	}
	scanf("%d", &nquery);
	for(int i = 0; i < nquery; i ++){
		scanf("%d%lld", &query[i].bee, &query[i].time);
		query[i].time *= 2;
		query[i].idx = i;
	}
	sort(query, query + nquery);
	memset(meet, 0, sizeof(meet));
	int64 now = 0;
	int j = 0;
	while(1){
		int64 nextMeet = INF;
		for(int i = 0; i < nbee; i ++){
			if(i > 0){
				if(dir[i] == -1 && dir[i - 1] == 1)
					nextMeet = min(nextMeet, (pos[i] - pos[i - 1]) / 2);
			}
		}
		while(j != nquery && now <= query[j].time && query[j].time < now + nextMeet){
			int x = query[j].bee;
			ans[query[j].idx].first = pos[x] + (query[j].time - now) * dir[x], 
				ans[query[j].idx].second = meet[x];
			j ++;
		}

		if(j == nquery || nextMeet == INF)
			break;

		static bool hello[500];
		memset(hello, 0, sizeof(hello));
		for(int i = 0; i < nbee; i ++){
			if(i > 0){
				if(dir[i] == -1 && dir[i - 1] == 1
						&& (pos[i] - pos[i - 1]) / 2 == nextMeet)
					hello[i - 1] = hello[i] = true;
			}
		}
		for(int i = 0; i < nbee; i ++)
			pos[i] += nextMeet * dir[i];
		for(int i = 0; i < nbee; i ++)
			if(hello[i])
				dir[i] *= -1, meet[i] ++;
		now += nextMeet;
	}
	for(int i = 0; i < nquery; i ++)
		printf("%lld %d\n", ans[i].first / 2, ans[i].second);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --)
		solve();
}
