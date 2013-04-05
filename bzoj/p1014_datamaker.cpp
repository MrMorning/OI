#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;
int main()
{
	freopen("t.in", "w", stdout);
	int len, seed, n_cmd;
	scanf("%d%d%d", &len, &n_cmd, &seed);
	srand(seed);
	string str;
	for(int i = 0; i < len; i ++)
		str = str + (char)(rand() % 26 + 'a');
	printf("%s\n", str.c_str());
	printf("%d\n", n_cmd);
	while(n_cmd --)
	{
		int t = rand() % 3;
		if(t == 0)
		{
			int a = rand() % str.length();
			int b = rand() % str.length();
			printf("Q %d %d\n", a + 1, b + 1);
		}
		else if(t == 1)
		{
			int a = rand() % str.length();
			string ch;
			ch += ((char)(rand() % 26 + 'a'));
			str.insert(a, ch);
			printf("I %d %s\n", a + 1, ch.c_str());
		}
		else
		{
			int a = rand() % str.length();
			string ch;
			ch += ((char)(rand() % 26 + 'a'));
			str.replace(a, 1, ch);
			printf("R %d %s\n", a + 1, ch.c_str());
		}
	}
}
