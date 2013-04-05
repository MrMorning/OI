#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;
int T, seed;
char conv[4];
string randStr(){
	int n = rand() % 200 + 1;
	string res;
	for(int i = 0; i < n; i ++)
		res += conv[rand() % 4];
	return res;
}
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d", &T, &seed);
	srand(seed);
	conv[0] = 'A', conv[1] = 'G', conv[2] = 'C', conv[3] = 'T';
	while(T --){
		int n = rand() % 6 + 1, l = rand() % 100 + 1;
		printf("%d %d\n", n + 4, l);
		printf("A %d\nG %d\nC %d\nT %d\n", -rand() % 100,-rand() % 100,-rand() % 100,-rand() % 100);
		while(n --)
			printf("%s %d\n", randStr().c_str(), rand() % 200 - 100);
	}
}
