#include <cstdio>
#include <cstring>
#include <cassert>

const char tzolkin[20][10] =
{"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};
const char haab[19][10] = 
{"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};

int convert(char *s)
{
	for(int i = 0; i < 19; i ++)
		if(strcmp(s, haab[i]) == 0)
			return i;
	assert(0);
}

int main()
{
	freopen("t.in", "r", stdin);
	int t;
	scanf("%d\n", &t);
	printf("%d\n", t);
	for(int i = 0; i < t; i ++)
	{
		int day, year;
		char month[10];
		scanf("%d. %s %d\n", &day, month, &year);
		int cnt = year * 365 + convert(month) * 20 + day;
		printf("%d %s %d\n", cnt % 260 % 13 + 1, tzolkin[cnt % 260 % 20], cnt / 260);
	}
}
