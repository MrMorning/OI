#include <cstdio>
#include <cstdlib>
#include <vector>
#define pb(x) push_back(x)
using namespace std;

vector<pair<char, int> > out;

int a1, a2, a3, a4;

void must(bool b) {
	if (!b) {
		printf("-1\n");
		exit(0);
	}
}	

int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &a1, &a2, &a3, &a4);
	if (abs(a3 - a4) > 1) 
		must(0);
	if (a3 == a4 + 1) {
		must(a1 >= a3);
		must(a2 >= a3);
		for (int i = 0; i < a3; i ++) {
			out.pb(make_pair('4', 1));
			out.pb(make_pair('7', 1));
		}
		out[0].second = a1 - (a3 - 1);
		out[a3 * 2 - 1].second = a2 - (a3 - 1);
	}
	else if(a4 == a3 + 1) {
		must(a1 >= a4);
		must(a2 >= a4);
		for (int i = 0; i < a4; i ++) {
			out.pb(make_pair('7', 1));
			out.pb(make_pair('4', 1));
		}
		out[1].second = a1 - (a4 - 1);
		out[a4 * 2 - 2].second = a2 - (a4 - 1);
	}
	else {
		if (a1 >= a3 + 1 && a2 >= a3) {
			for (int i = 0; i < a3; i ++) {
				out.pb(make_pair('4', 1));
				out.pb(make_pair('7', 1));
			}
			out.pb(make_pair('4', 1));
			out[0].second = a1 - a3;
			out[(int)out.size() - 2].second = a2 - (a3 - 1);
		}
		else {
			must(a1 >= a3);
			must(a2 >= a3 + 1);
			for (int i = 0; i < a3; i ++) {
				out.pb(make_pair('7', 1));
				out.pb(make_pair('4', 1));
			}
			out.pb(make_pair('7', 1));
			out[1].second = a1 - (a3 - 1);
			out[(int)out.size() - 1].second = a2 - a3;
		}
	}
	int sz = out.size();
	for (int i = 0; i < sz; i ++)
		for (int j = 0; j < out[i].second; j ++)
			printf("%c", out[i].first);
}
