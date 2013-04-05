#include <cstdio>
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long val_t;

int mod_num;

namespace find_root
{
	int num;
	vector<int> test_num;
	void generate();
	bool check(int r);
	int main(int x);
}

namespace dis_log
{
	map<int, int> index;
	int main(int a, int b);
}

namespace gen_sol
{
	int gcd(int a, int b);
	void ex_gcd(int a, int b, int &x, int &y);
	void main(int a, int b, int c, vector<int> &sol);
}

int pow_mod(int a, int n)
{
	int ret = (n & 1) ? a : 1;
	for(n >>= 1; n; n >>= 1)
	{
		a = (val_t)a * a % mod_num;
		if(n & 1)
			ret = (val_t)ret * a % mod_num;
	}
	return ret;
}

int rev_mod(int x)
{
	return pow_mod(x, mod_num - 2);
}

void find_root::generate()
{
	int x = num - 1;
	for(int i = 2, upperlim = (int)sqrt(x); i <= upperlim; i ++)
		if(x % i == 0)
		{
			test_num.push_back((num - 1)/ i);
			while(x % i == 0)
				x /= i;
		}
}

bool find_root::check(int r)
{
	for(int i = 0; i < (int)test_num.size(); i ++)
		if(pow_mod(r, test_num[i]) == 1)
			return false;
	return true;
}

int find_root::main(int x)
{
	if(x == 2)
		return 1;
	num = x;
	generate();
	for(int r = 2; ; r ++)
		if(check(r))
			return r;
}

int dis_log::main(int a, int b)
{
	int p = (int)sqrt(mod_num);
	for(int i = 0; i <= p; i ++)
		index[pow_mod(a, p * i)] = p * i;
	for(int r = 0; r < p; r ++)
	{
		int y = (val_t)b * rev_mod(pow_mod(a, r)) % mod_num;
		if(index.count(y))
			return r + index[y];
	}
	assert(0);
}

int gen_sol::gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void gen_sol::ex_gcd(int a, int b, int &x0, int &y0)
{
	if(b == 0)
		x0 = 1, y0 = 0;
	else
	{
		int x1, y1;
		gen_sol::ex_gcd(b, a % b, x1, y1);
		x0 = y1, y0 = x1 - a / b * y1;
	}
}

void gen_sol::main(int a, int b, int c, vector<int> &sol)
{
	int g = gcd(a, b);
	if(c % g != 0)
		return;
	a /= g, b /= g, c /= g;
	int x0, y0;
	ex_gcd(a, b, x0, y0);
	x0 = (val_t)x0 * c % (mod_num - 1);
	x0 = ((val_t)x0 + mod_num - 1) % (mod_num - 1);
	sol.push_back(x0);
	for(int x = ((val_t)x0 + b) % (mod_num - 1); x != x0; x = ((val_t)x + b) % (mod_num - 1))
		sol.push_back(x);
}

void solve()
{
	int k, a;
	scanf("%d%d%d", &mod_num, &k, &a);
	int r = find_root::main(mod_num);
	int j = dis_log::main(r, a);
	vector<int> sol;
	gen_sol::main(k, mod_num - 1, j, sol);
	for(int i = 0; i < (int)sol.size(); i ++)
		sol[i] = pow_mod(r, sol[i]);
	sort(sol.begin(), sol.end());
	vector<int>::iterator it = unique(sol.begin(), sol.end());
	sol.resize(it - sol.begin());
	printf("%d\n", sol.size());
	for(int i = 0; i < (int)sol.size(); i ++)
		printf("%d\n", sol[i]);
}

int main()
{
	freopen("t.in", "r", stdin);
	solve();
}
