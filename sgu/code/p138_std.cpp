#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct datat{int d,mark;}a[111];
int n,ans[111111][2];

bool cmp(datat x,datat y){return x.d>y.d;}

int main(){
	freopen("t.in", "r", stdin);
	int sum=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i].d);
		a[i].mark=i;
		sum+=a[i].d;
	}
	sort(&a[1],&a[n+1],cmp);
	sum/=2;
	printf("%d\n",sum);
	int tot=0;
	for (int i=1;i<=n;i++){
		while (tot<sum && a[i].d>1){
			a[i].d--;
			tot++;
			ans[tot][0]=a[i].mark;
		}    
		if (tot<sum){
			tot++;
			ans[tot][1]=a[i].mark;
			ans[tot][0]=a[i+1].mark;
			a[i+1].d--;
			a[i].d--;
		}    
	}
	int top=1;
	while (a[top].d==0) top++;
	for (int i=1;i<=sum;i++){
		printf("%d ",ans[i][0]);
		if (ans[i][1]) printf("%d",ans[i][1]);
		else{
			printf("%d",a[top].mark);
			a[top].d--;
			while (a[top].d==0) top++;
		}   
		printf("\n"); 
	}
}   
