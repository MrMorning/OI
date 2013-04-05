#include<cstdlib>
#include<iostream>
#include<fstream>

using namespace std;
#define N 400010

int sa[N],sa1[N],rank[N],rank1[N],c[N],h[N];
int m[N];


int n,pow,count;

int cmp(const void *a,const void *b){
	int x=*(int*)a;
	int y=*(int*)b;
	if(rank[x]!=rank[y])
		return(1);
	else
		if(rank[x+pow]!=rank[y+pow])
			return(1);
		else
			return(0);
}

int cmp1(const void *a,const void *b){
	return m[*((int *)a)]-m[*((int *)b)];
}

void creat(){
	int i,j,k;

	for(i=0;i<n;i++)
		sa[i]=i;
	qsort(sa,n,sizeof(int),cmp1);


	for(i=0,j=0;i<n;i++)
	{
		if(i>0&&m[sa[i]]!=m[sa[i-1]])
			j++;
		rank[sa[i]]=j;
	}

	for(pow=1;pow<n;pow*=2)
	{
		for(i=0;i<n;i++)
			c[i]=0;
		for(i=0;i<n;i++)
			if(sa[i]+pow<n)
				c[rank[sa[i]+pow]]++;
			else
				c[rank[sa[i]]]++;
		for(i=1;i<n;i++)
			c[i]+=c[i-1];
		for(i=n-1;i>=0;i--)
			if(sa[i]+pow<n)
				sa1[--c[rank[sa[i]+pow]]]=sa[i];
			else
				sa1[--c[rank[sa[i]]]]=sa[i];
		for(i=0;i<n;i++)
			c[i]=0;
		for(i=0;i<n;i++)
			c[rank[sa1[i]]]++;
		for(i=1;i<n;i++)
			c[i]+=c[i-1];
		for(i=n-1;i>=0;i--)
			sa[--c[rank[sa1[i]]]]=sa1[i];
		for(i=0,j=0;i<n;i++)
		{
			if(i>0&&cmp(&sa[i],&sa[i-1])!=0)
				j++;
			rank1[sa[i]]=j;
		}
		for(i=0;i<n;i++)
			rank[i]=rank1[i];
	}
}



int a[200001];

int main(){
freopen("t.in", "r", stdin);
	int i,j,k,mid;
	int n1,n2;
	int sm;
	//cin>>sm;
	scanf("%d",&sm);
	for(i=0;i<sm;i++)
		scanf("%d",&a[i]);
	//      cin>>a[i];
	for(i=0;i<sm;i++)
		m[sm-i-1]=a[i];
	m[sm]=a[0]+10;
	n=sm+1;
	creat();

	for(i=0;;i++)
		if(sa[i]>=2)
			break;
	n1=sm-1-sa[i];
	n=0;
	for(j=sm-1;j>n1;j--)
		m[n++]=a[j];
	for(i=0;i<n;i++)
		m[n+i]=m[i];
	m[2*n]=a[0]+10;
	n=2*n+1;
	creat();
	for(i=0;;i++)
		if(sa[i]<n/2&&sa[i]>=1)
			break;
	n=n/2+1;
	n2=n-2-sa[i]+n1+1;
	for(i=n1;i>=0;i--)
		cout<<a[i]<<endl;
	for(i=n2;i>n1;i--)
		cout<<a[i]<<endl;
	for(i=sm-1;i>n2;i--)
		cout<<a[i]<<endl;
	return(0);
}
