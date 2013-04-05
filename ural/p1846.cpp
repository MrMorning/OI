#include <cstdio>
#include <vector>
#include <map>

using namespace std;
const int N_MAX = 100010;

struct Node{
	int g, l, r;
} node[N_MAX * 4];

vector<int> vec[N_MAX];

int gcd(int a, int b){
	return b ? gcd(b, a % b) : a;
}

void upd(int i){
	int t1 = node[i * 2].g, t2 = node[i * 2 + 1].g;
	if(t1 == -1 && t2 == -1)
		node[i].g = -1;
	else if(t1 == -1)
		node[i].g = t2;
	else if(t2 == -1)
		node[i].g = t1;
	else
		node[i].g = gcd(t1, t2);
}

void build_tree(int i, int l, int r){
	node[i].l = l, node[i].r = r;
	node[i].g = -1;
	if(l == r)
		return;
	build_tree(i * 2, l, (l + r) / 2);
	build_tree(i * 2 + 1, (l + r) / 2 + 1, r);
}

void change(int i, int pos, int val){
	if(node[i].l > pos || node[i].r < pos)
		return;
	if(node[i].l == pos && node[i].r == pos){
		node[i].g = val;
		return;
	}
	change(i * 2, pos, val);
	change(i * 2 + 1, pos, val);
	upd(i);
}

int rev(int x){
	static map<int, int> M;
	static int cnt = 0;
	if(M.count(x) == 0)
		M[x] = cnt ++;
	return M[x];
}

int main(){
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n;
	scanf("%d", &n);
	build_tree(1, 1, n);
	for(int i = 1; i <= n; i ++){
		char str[5];
		int x;
		scanf("%s %d", str, &x);
		int p = rev(x);
		if(str[0] == '+'){
			change(1, i, x);
			vec[p].push_back(i);
		}
		else{
			int t = vec[p].back();
			vec[p].pop_back();
			change(1, t, -1);
		}
		printf("%d\n", node[1].g == -1 ? 1 : node[1].g);
	}
}
