#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
#define MAX(a, b) ((a) > (b) ? (a) : (b))
string str;
int main()
{
	freopen("t.in", "r", stdin);
	cin >> str;
	int n_cmd;
	scanf("%d", &n_cmd);
	while(n_cmd --)
	{
		string cmd;
		cin >> cmd;
		if(cmd[0] == 'Q')
		{
			int a, b;
			scanf("%d%d", &a, &b);
			a --, b --;
			int len = 0;
			while(MAX(a, b) + len < str.length() && str[a + len] == str[b + len])
				len ++;
			printf("%d\n", len);
		}
		else if(cmd[0] == 'R')
		{
			int x;
			char ch;
			scanf("%d %c", &x, &ch);
			x --;
			str[x] = ch;
		}
		else
		{
			int x;
			string ch;
			scanf("%d", &x);
			cin >> ch;
			str.insert(x, ch);
		}
	}
}
