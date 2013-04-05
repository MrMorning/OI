#include <cstdio>
#include <cstdlib>
#include <map>
#include <algorithm>
using namespace std;
int n, seed;
map<int, int> Mx, My; 
int randval()
{
	return rand() % 1000000 + 1;
}
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
	{
	/*	int x = randval();
		while(Mx.count(x))
			x = randval();
		Mx[x] = 1;
		int y = randval();
		while(My.count(y))
			y = randval();
		My[y] = 1;
	*/	printf("%d %d\n", 1, 1 + i);
	}
}
