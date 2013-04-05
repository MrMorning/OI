#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;
int val;
char str[11111];
pair<int, int> arr[11111];
int nArr = 0;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &val);
	scanf("%s", str);
	int flag = 1, coef = 1;
	int len = strlen(str);
	for ( int i = 0; i < len; i ++ ) {
		if ( i+2 < len &&
				str[i] == '+' && str[i+1] == '+' && str[i+2] == 'a' ) {
			arr[nArr++] = make_pair(flag*coef, 0);
			coef = flag = 1;
			i += 2;
		} else if ( i+2 < len &&
				str[i] == 'a' && str[i+1] == '+' && str[i+2] == '+' ) {
			arr[nArr++] = make_pair(flag*coef, 1);
			coef = flag = 1;
			i += 2;
		}
		else if ( str[i] == '+' ) flag = 1;
		else if ( str[i] == '-' ) flag = -1;
		else {
			assert(isdigit(str[i]));
			coef = str[i]-'0';
			while ( isdigit(str[i+1]) ) 
				i++, coef = coef * 10 + str[i]-'0';
			i++;
		}

	}
	sort(arr, arr + nArr);
	int res = 0;
	for ( int i = 0; i < nArr; i ++ ) {
		if ( arr[i].second == 0 ) 
			res += arr[i].first * ++val;
		else
			res += arr[i].first * val++;
	}
	printf("%d\n", res);
}
