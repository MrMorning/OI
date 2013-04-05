#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
vector<string> out;
const int POW[5] = {1, 10, 100, 1000, 10000};

struct Point {
	int x, y, z;
	Point(){}
	Point(int _x, int _y, int _z):
		x(_x), y(_y), z(_z){}
	bool isZero() {
		return x == 0 && y == 0 && z == 0;
	}
} p[111];
int n;
char name[111][222];
bool marked[111];

inline int sgn(ll x) {
	if ( x == 0 ) return 0;
	else if ( x > 0 ) return 1;
	else return -1;
}

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

Point cross(const Point &p1, const Point &p2) {
	return Point(	p1.y * p2.z - p2.y * p1.z,
					p1.z * p2.x - p2.z * p1.x,
					p1.x * p2.y - p2.x * p1.y	);
}

ll dot(const Point &p1, const Point &p2) {
	return (ll)p1.x * p2.x + (ll)p1.y * p2.y + (ll)p1.z * p2.z;
}

int readInt(int &res, char *s, int st) {
	res = 0;
	int cnt = 0;
	while ( isdigit(s[st]) ) {
		res += POW[cnt] * (s[st] - '0');
		cnt ++;
		st --;
	}
	if ( s[st] == '-' ) {
		res *= -1;
		st --;
	}
	return st;
}

int main() {
	scanf("%d\n", &n);
	for ( int i = 0; i < n; i ++ ) {
		static char ts[333];
		int x, y, z;
		gets(ts);
		int ptr = strlen(ts) - 1;
		while ( ts[ptr] == ' ' )
			ptr --;
		ptr = readInt(z, ts, ptr);
		ptr --;
		ptr = readInt(y, ts, ptr);
		ptr --;
		ptr = readInt(x, ts, ptr);
		ptr --;
		memcpy(name[i], ts, sizeof(char) * (ptr+1));

		p[i] = Point(x, y, z);
	}

	bool onSame = true;
	for ( int i = 0; i < n - 2; i ++ )
		if ( !cross(p[i + 1] - p[i], p[i + 2] - p[i + 1]).isZero() )
			onSame = false;

	if ( onSame ) {
		printf("%d\n", n);
		for ( int i = 0; i < n; i ++ ) 
			out.push_back(name[i]);
		sort(out.begin(), out.end());
		for ( int i = 0; i < (int)out.size(); i ++ )
			printf("%s\n", out[i].c_str());
		return 0;
	}

	for ( int i = 0; i < n; i ++ )
		for ( int j = i + 1; j < n; j ++ )
			for ( int k = j + 1; k < n; k ++ ) {
				Point dir = cross(p[j] - p[i], p[k] - p[i]);
				if ( dir.isZero() )
					continue;
				int note = 0;
				bool fail = false;
				for ( int t = 0; !fail && t < n; t ++ ) {
					int val = sgn(dot(dir, p[t] - p[i]));
					if ( val == 0 )
						continue;
					if ( !note )
						note = val;
					else if ( note != val ) 
						fail = true;
				}
				if ( !fail ) 
					marked[i] = marked[j] = marked[k] = true;
			}
	int cnt = 0;
	for ( int i = 0; i < n; i ++ )
		cnt += marked[i];
	printf("%d\n", cnt);
	for ( int i = 0; i < n; i ++ )
		if ( marked[i] ) 
			out.push_back(name[i]);
	sort(out.begin(), out.end());
	for ( int i = 0; i < (int)out.size(); i ++ )
		printf("%s\n", out[i].c_str());
}
