#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char str[111];
int main(){
	freopen("t.in", "r", stdin);
	scanf("%s", str);
	int n = strlen(str), m;
	scanf("%d", &m);
	int ans = 0;
	for(int s = 0; s < (1 << n); s ++){
		int cnt = 0;
		for(int i = 0; i < n; i ++)
			if(s & (1 << i))
				cnt ++;
		if(cnt > m || (cnt ^ m) & 1)
			continue;
		int dir = 1, acc = 0;
		for(int i = 0; i < n; i ++){
			char cmd;
			if(s & (1 << i))
				cmd = (str[i] == 'F' ? 'T' : 'F');
			else
				cmd = str[i];
			if(cmd == 'F')
				acc += dir;
			else
				dir *= -1;
		}
		ans = max(ans, abs(acc));
	}
	printf("%d\n", ans);
}
