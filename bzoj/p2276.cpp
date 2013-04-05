#include <cstdio> 
#include <string>
using namespace std;int n,h,t,s;pair<int,int> q[1000000];int main(){freopen("t.in", "r", stdin);scanf("%d",&n);for(int i=0,l,r;i<n;i++){int w=i;scanf("%d%d",&l,&r);while(h<t&&q[h].first>r)h++;if(h<t)s=max(s,i-q[h].second+1);while(h<t&&q[t-1].first<l)w=q[t-1].second,t--;q[t++]=make_pair(l,w);}printf("%d\n",s);}
