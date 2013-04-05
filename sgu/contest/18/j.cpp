#define CHEAT

#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

char a[100 + 10];
int N;

void Init()
{
	gets(a);
	N = strlen(a);
}

string Solve()
{
	string ans("");
	int tmp = 0;
	while (tmp < N) {
		bool key = 1;
		while (a[tmp] == ' ') {
			++ tmp;
			key = 0;
		}
		if (a[tmp] != '-') {
			char ch = ans[ans.length() - 1];
			if (a[tmp] != '"' && ! key &&  ch != '-' && ch != ' ' && ch != '"')
				ans += ' ';
			ans += a[tmp];
			++ tmp;
		}
		else {
			int tot(0);
			while (a[tmp] == ' ' || a[tmp] == '-') {
				tot += (a[tmp] == '-');
				++ tmp;
			}
			while (tot) {
				if (tot > 3) {
					ans += " --";
					tot -= 2;
				} else if (tot == 3) {
					ans += " --- ";
					tot = 0;
				} else if (tot == 2) {
					ans += " -- ";
					tot = 0;
				} else {
					ans += "-";
					tot = 0;
				}
			}
		}
	}

	if (ans[1] == '-' || ans[ans.length() - 2] == '-') return "error";
	return ans;
}

int main()
{
	int T;
	scanf("%d", &T); getchar();
	for(int i = 1; i <= T; ++ i) {
		Init();
		cout << Solve() << endl;
	}

	return 0;
}
