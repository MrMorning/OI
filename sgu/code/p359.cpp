#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
int val[5], ptr[5];
string str;
int n;
int main() {
	freopen("t.in", "r", stdin);
	ptr[1] = 1, ptr[2] = 2, ptr[3] = 3, ptr[4] = 4;
	cin >> n;
	getline(cin, str);
	while ( n -- ) {
		getline(cin, str);
		if ( isdigit(str[4]) ) {
			val[ptr[str[0]-'a'+1]] = str[4]-'0';
		} else if ( str.substr(1, 3) == "^:=" ) {
			val[ptr[str[0]-'a'+1]] = val[ptr[str[4]-'a'+1]];
		} else if ( str.substr(1, 2) == ":=" ) {
			ptr[str[0]-'a'+1] = ptr[str[3]-'a'+1];
		} else {
			cout << val[ptr[str[8]-'a'+1]] << endl;
		}
	}
}
