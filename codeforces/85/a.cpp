#include <string>
#include <iostream>
using namespace std;
int main()
{
	string a, b;
	cin >> a >> b;
	int len = a.length();
	for(int i = 0; i < len; i ++)
	{
		if('a' <= a[i] && a[i] <= 'z')
			a[i] = a[i] + 'A' - 'a';
		if('a' <= b[i] && b[i] <= 'z')
			b[i] = b[i] + 'A' - 'a';
	}
	if(a < b)
		cout << -1;
	else if(a == b)
		cout << 0;
	else
		cout << 1;
}
