#include <cstdio> 
int n,m,a,b,d[222222]; int main(){scanf("%d%d",&n,&m);while(m--)scanf("%d%d",&a,&b),d[a]=d[b]=1;for(int i=1;i<=n;i++)if(!d[i]){puts("NIE");return 0;};puts("TAK");}
