#include <cstdio>
#include <cstring>
#include <algorithm>
const int kNMax = 100010;
using namespace std;

char str[kNMax], pat[kNMax];
int rad[kNMax], pre[kNMax], f[kNMax];
int n;
pair<int, int> out[3];

void manacher() {
	int p = -1;
	for ( int i = 0; i < n; i ++ ) {
		if ( p != -1 && p+rad[p] > i )
			rad[i] = min(rad[2*p-i], p+rad[p]-i);
		else rad[i] = 0;
		while ( i+rad[i]<n&&i-rad[i]>=0&&str[i+rad[i]]==str[i-rad[i]] )
			rad[i]++;
		if ( p==-1 || i+rad[i] > p+rad[p] ) 
			p = i;
	}
}

void KMP() {
	for ( int i = 0; i < n; i ++ )
		pat[i] = str[n-i-1];
	pre[0] = -1;
	for ( int i = 1; i < n; i ++ ) {
		int t = pre[i-1];
		while ( t != -1 && pat[t+1] != pat[i] )
			t = pre[t];
		if ( pat[t+1] == pat[i] )
			pre[i] = t+1;
		else pre[i] = -1;
	}

	memset(f, 0x3f, sizeof(f));
	for ( int i = 0, j = -1; i < n; i ++ ) {
		while ( str[i] != pat[j+1] && j >= 0 )
			j = pre[j];
		if ( str[i] == pat[j+1] ) {
			j++;
			f[n-j-1] = min(f[n-j-1], i);
		}
	}
}

int main() {
//	freopen("t.in", "r", stdin);
	scanf("%s", str);
	n = strlen(str);
	manacher();
	KMP();
	f[n] = 0;
	int ans = 0;
	for ( int i = 0; i < n; i ++ ) {
		int lb = i+rad[i]-1, rb = n;
		for ( int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2 )
			if ( f[mid] <= i-rad[i] ) rb = mid;
			else lb = mid;
		int l1 = rad[i]*2-1, l2 = n-rb;
		if ( l1+2*l2 > ans ) {
			ans = l1+2*l2;
			out[0] = make_pair(f[rb]-l2+1, l2);
			out[1] = make_pair(i-rad[i]+1, l1);
			out[2] = make_pair(rb, l2);
		}
	}
	if ( out[0].second == 0 ) 
		printf("1\n%d %d\n", out[1].first+1, out[1].second);
	else {
		printf("3\n");
		for ( int t = 0; t < 3; t ++ )
			printf("%d %d\n", out[t].first+1, out[t].second);
	}
}
