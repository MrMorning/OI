#include <cstdio>
typedef long long ll;

char sp='.';
ll t,x0,y0;
int w,h;
char f(ll x, ll y) {
	if ((x+y)%2==1) return sp;
	ll m=(x+y)/2;
	ll n=y;
	if(m<0 || n<0) return sp;
	if((m&n)!=n||m>t-1) return sp;
	return m%2==0?'A':'B';
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%lld%lld%lld%d%d", &t, &x0, &y0, &w, &h);
	for ( int i = 0; i < h; i ++, puts("") )
		for ( int j = 0; j < w; j ++ )
			printf("%c", f(x0+j,y0+h-i-1));
}
