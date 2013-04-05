#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;
char VOWEL[6] = {'A', 'O', 'Y', 'E', 'U', 'I'};
char str[300];
bool marked[300];
int main()
{
	scanf("%s", str);
	int n = strlen(str);
	memset(marked, 0, sizeof(marked));
	for(int t = 0; t < 6; t ++)
		for(int i = 0; i < n; i ++)
			if(str[i] == VOWEL[t] || str[i] == VOWEL[t] - 'A' + 'a')
				marked[i] = true;
	string res("");
	for(int i = 0; i < n; i ++)
		if(!marked[i])
			if('A' <= str[i] && str[i] <= 'Z')
				res = res + "." + (char)(str[i] - 'A' + 'a');
			else
				res = res + "." + str[i];
	cout << res;
}
