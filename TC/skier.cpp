#include <cstdio>
typedef long long ll;

char sp='.';
ll t,x0,y0;
int w,h;
ll ar[1010], t0;
char f(ll x, ll y) {
	if(x+y>2*(t0-1))
		return '.';
	if(y>x||x<0||y<0)
		return '.';
	if(x==0&&y==0) return 'A';
	if(x==1&&y==1) return 'B';
	if(x==2&&y==0 ) return 'B';
	if(x==1&&y==0) return '.';
	ll t=x+y;
	int cow=0;
	while(ar[cow]<t+1)++cow;
	--cow;
	if(y>(ar[cow]-1)/2){
		x-=(ar[cow]-1)/2+1;
		y-=(ar[cow]-1)/2+1;
		return f(x, y);
	}
	x -= ar[cow]+1;
	if(y<=x ) 
		return f(x,y);
	return '.';
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%lld%lld%lld%d%d", &t, &x0, &y0, &w, &h);
	t0=t;
	ar[0]=3;
	for(int i = 0; i < 999; i ++ )
		ar[i+1]=ar[i]*2+1;

	for ( int i = 0; i < h; i ++, puts("") )
		for ( int j = 0; j < w; j ++ )
			printf("%c", f(x0+j,y0+h-i-1));
}
