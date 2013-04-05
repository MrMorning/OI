#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
char str[510000];
int n;

int check(int len)
{
	static vector<int> V;
	V.clear();
	int tmp = 0;
	for(int i = 0; i < len; i ++)
		tmp |= (1 << i) * (str[i] == 'b');
	V.push_back(tmp);
	for(int i = len; i < n; i ++)
	{
		tmp >>= 1;
		tmp |= (1 << (len - 1)) * (str[i] == 'b');
		V.push_back(tmp);
	}
	sort(V.begin(), V.end());
	vector<int>::iterator it = unique(V.begin(), V.end());
	V.resize(it - V.begin());
	for(int i = 0; i < (int)V.size(); i ++)
		if(V[i] != i)
			return i;
	if((int)V.size() == (1 << len))
		return -1;
	else
		return (1 << len) - 1;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", str);
	int lb = 0, rb = 20;
	for(int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2)
		if(check(mid) != -1)
			rb = mid;
		else
			lb = mid;
	int res = check(rb);
	printf("%d\n", rb);
	for(int i = 0; i < rb; i ++)
		printf("%c", (res & (1 << i)) ? 'b' : 'a');
}
