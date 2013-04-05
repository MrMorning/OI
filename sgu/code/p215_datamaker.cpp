#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

char OPRT[6] = {'*', '+', '-', '^', '%', '/'};
string name[10000];

string randStr();

string rec(int n) {
	string res;
	if ( n == 1 ) {
		res = randStr();
	} else {
		int t = rand() % 3;
		int l = rand() % (n-1)+1;
		res = "(" + rec(l) + OPRT[t] + rec(n-l) + ")";
	}
	int k = rand() % 3;
	while ( k -- )
		res = (rand()%2?"+":"-") + res;
	return res;
}

string randStr() {
	int type = rand() % 2;
	string res;
	int len = rand() % 2 + 1;
	if ( type == 0 ) {
		res += rand()%9+'1';
	} else {
		res += rand()%26+'a';
	}
	for ( int i = 1; i < len; i ++ )
		res += rand()%10+'0';
	return res;
}

int main() {
	freopen("t.in", "w", stdout);
	int n, m, seed;
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	for ( int i = 0; i < m; i ++ )
		name[i] = randStr();
	while ( n -- ) {
		int t = rand() % 2;
		if ( t == 0 )
			printf("print %s\n", rec(rand() % 200+1).c_str());
		else
			printf("define %s %s\n", name[rand()%m].c_str(), name[rand()%m].c_str());
	}
}
