#include <iostream>
#include <cstdio>
using namespace std;
 
void get_primes(long n,long *primes)
{
    *primes=0;
    for (long i=2;i<=n;++i)
    {
        bool isprime=true;
        for (long j=1;j<=*primes && *(primes+j) * *(primes+j)<=i;++j)
            if (i % *(primes+j) ==0)
            {
                isprime=false;
                break;
            }
        if (isprime) *(primes+ ++*primes)=i;       
    }
}
 
int main()
{
	freopen("t.in", "r", stdin);
    long primes[1500],sprimes[210]={0},n;
    for (long i=1;i<1500;++i) primes[i]=32768;
    cin>>n;
    get_primes(n,primes);
    for (long i=1;i<=primes[0] && primes[i]<=primes[0];++i)  sprimes[++sprimes[0]]=primes[primes[i]];
    long present[10001]={0},usedp[10001];
    for (long i=1;i<=n;++i) usedp[i]=32768;
    for (long i=1;i<=sprimes[0];++i)
    {
        present[sprimes[i]]=sprimes[i]; usedp[sprimes[i]]=1;
    }
    for (long i=4;i<=n;++i)
        for (long j=sprimes[0]<i?sprimes[0]:i;j>0;--j)
            if (i>=sprimes[j] && present[i-sprimes[j]]>0 && usedp[i-sprimes[j]]+1<usedp[i])
            {
                present[i]=sprimes[j]; usedp[i]=usedp[i-sprimes[j]]+1;
            }
    /*sprimes will be redefined to record the presentation of n*/ 
    sprimes[0]=0;
    for (long i=n;present[i]>0;i-=present[i]) sprimes[++sprimes[0]]=present[i];
    cout<<sprimes[0]<<endl;
    for (long i=1;i<=sprimes[0];++i) cout<<sprimes[i]<<' ';
    if (sprimes[0]) cout<<endl;
    return 0;
}
