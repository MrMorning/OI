#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
vector<int> vec;
char str[1111];
int K;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%s%d", str, &K);
	int n = strlen(str);
	for ( int i = 0; i < n; i ++ )
	   vec.push_back(str[i] - '0');	
	while ( K -- ) {
		int t;
		for ( t = 0; t + 1 < (int)vec.size() && vec[t + 1] <= vec[t]; t ++ );
		vec.erase(vec.begin() + t);
	}
	for ( int i = 0; i < (int)vec.size(); i ++ )
		printf("%d", vec[i]);
}
