#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

const int N_MAX = 2048;

char exprs[N_MAX], str[N_MAX];
int n2, alphaCnt;
char alpha[N_MAX];
char ans[32778];
int ansCnt;
int curVal;

inline bool makeCalc(char oprt, bool a, bool b)
{
	switch(oprt)
	{
		case '|': return a | b;
		case '&': return a & b;
		case '=': return a == b;
		case '>': return !(a & !b);
		default:  return a ^ b;
	}
}

int findPair(int r)
{
	assert(exprs[r] == ')');
	int cnt = 0;
	for(int i = r; i >= 0; i --)
	{
		if(exprs[i] == ')')
			cnt --;
		else if(exprs[i] == '(')
			cnt ++;
		if(cnt == 0)
			return i;
	}
	assert(0);
}

bool calcExp(int l, int r);
bool calcPrev(int r, int &l)
{
	bool val;
	if(exprs[r] == ')')
	{
		int t = findPair(r);
		val = calcExp(t + 1, r - 1);
		l = t - 1;
	}
	else
		val = curVal & 1 << (exprs[r] - 'a'), l = r - 1;
	while(l >= 0 && exprs[l] == '!')
	{
		l --;
		val ^= 1;
	}
	return val;
}

bool calcExp(int l, int r)
{
	assert(l <= r);
	int t;
	bool val = calcPrev(r, t);
	if(t < l)
		return val;
	else
	{
		char oprt = exprs[t];
		if(oprt == '&')
		{
			while(oprt == '&')
			{
				int s;
				val &= calcPrev(t - 1, s);
				t = s;
				oprt = exprs[t];
			}
			if(t < l)
				return val;
		}
		return makeCalc(oprt, calcExp(l, t - 1), val);
	}
}

int bsearch(char ch)
{
	int lb = -1, rb = alphaCnt;
	for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
		if(alpha[mid] < ch)
			lb = mid;
		else
			rb = mid;
	return rb;
}

void adjustExp()
{
	int n1 = strlen(str);
	for(int i = 0; i < n1; i ++)
		if('a' <= str[i] && str[i] <= 'z')
			alpha[alphaCnt ++] = str[i];
	sort(alpha, alpha + alphaCnt);
	alphaCnt = unique(alpha, alpha + alphaCnt) - alpha;

	n2 = 0;
	for(int i = 0; i < n1; i ++)
		if(str[i] == '|')
			exprs[n2 ++] = '|', i ++;
		else if(str[i] == '<')
			exprs[n2 ++] = '=', i += 2;
		else if(str[i] == '=')
			exprs[n2 ++] = '>', i ++;
		else
		{
			if('a' <= str[i] && str[i] <= 'z')
				exprs[n2 ++] = 'a' + bsearch(str[i]);
			else
				exprs[n2 ++] = str[i];
		}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%s", str);
	adjustExp();
	int upperlim = 1 << alphaCnt;
	bool flag = false;
	bool first = true;
	for(curVal = 0; curVal < upperlim; curVal ++)
	{

		if(calcExp(0, n2 - 1) == 1)
		{
			if(!first)
			{
				ans[ansCnt ++] = '|', ans[ansCnt ++] = '|';
			}
			first = false;
			flag = true;
			for(int i = 0; i < alphaCnt; i ++)
			{
				if(i != 0)
					ans[ansCnt ++] = '&';
				if((1 << i) & curVal)
					ans[ansCnt ++] = alpha[i];
				else
					ans[ansCnt ++] = '!', ans[ansCnt ++] = alpha[i];
			}
		}
	}
	if(!flag)
		printf("%c&!%c\n", alpha[0], alpha[0]);
	else
		printf("%s", ans);
}
