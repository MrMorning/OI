#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int rep[10000];
int sol[10000];
int bestsol[10000];
int heap[200001];

int costa[100000];
int costb[100000];
int src[100000];
int dst[100000];
int m,n;
int besta, bestb;

long long weighta,weightb;
long long wcost[100000];
long long suma,sumb;
long long bestprod;

FILE *datf;
FILE *logf;
FILE *dbgf;

int getrep(int j)
{
	if (dbgf) fprintf(dbgf,"%d->",j);
	if (rep[j]==j) return j;
	rep[j]=getrep(rep[j]);
	return rep[j];
}

void mergerep(int i, int j)
{
	int k=getrep(j);
	rep[k]=i;
}

int solve()
{
	if (dbgf) fprintf(dbgf,"weights: %lld %lld\n",weighta,weightb);
	int i,j,d,t;
	suma=sumb=0;
	for (i=0; i<n; i++) rep[i]=i;
	for (i=0; i<m; i++) wcost[i]=weighta*costa[i]+weightb*costb[i];
	for (i=m; i<200001; i++) heap[i]=-1;
	for (i=0; i<m; i++)
	{
		heap[i]=i;
		j=i;
		while (j)
		{
			d=(j-1)/2;
			if (wcost[heap[d]]<wcost[heap[j]]) break;
			t=heap[j]; heap[j]=heap[d]; heap[d]=t;
			j=d;
		}
	}
	for (i=0; i<n-1;)
	{
		assert(heap[0]!=-1);
		d=heap[0];
		j=0;
		while (heap[j*2+1]!=-1 || heap[j*2+2]!=-1)
		{
			if (heap[j*2+1]==-1) 
			{ 
				heap[j]=heap[j*2+2]; 
				j=j*2+2; 
				continue; 
			}
			if (heap[j*2+2]==-1 || wcost[heap[j*2+1]]<wcost[heap[j*2+2]]) 
			{ 
				heap[j]=heap[j*2+1]; 
				j=j*2+1; 
				continue; 
			}
			heap[j]=heap[j*2+2]; 
			j=j*2+2;	
		}
		heap[j]=-1;
		int sr=getrep(src[d]);
		if (dbgf) fprintf(dbgf,"%d\n",sr);
		int dr=getrep(dst[d]);
		if (dbgf) fprintf(dbgf,"%d\n",dr);
		if (sr==dr) 
		{
			if (dbgf) fprintf(dbgf,"-- rej %d %d, edge %d\n",src[d],dst[d],d);
			continue;
		}
		sol[i]=d;
		suma+=costa[d];
		sumb+=costb[d];
		i++;
		if (dbgf) fprintf(dbgf,"%d %d %d %d %d %lld\n",d,src[d],dst[d],costa[d],costb[d],wcost[d]);
		mergerep(src[d],dst[d]);
	}
	if (suma*sumb<bestprod)
	{
		bestprod=suma*sumb;
		besta=suma;
		bestb=sumb;
		memcpy(bestsol,sol,sizeof(bestsol));
	}
	if (datf) fprintf(datf,"%lld %lld %lld\n",suma,sumb,suma*sumb);
	if (dbgf) fprintf(dbgf,"---\n");
}

int sol0a,sol0b,sol1a,sol1b;

void rec(int a0,int b0,int a1,int b1, int lev=0)
{
	if (logf) fprintf(logf,"-- rec (%d %d) (%d %d)\n",a0,b0,a1,b1);
	int solxa,solxb;
	long long comp;
//	if (lev>5) return;
	weighta=(b1-b0);
	weightb=(a0-a1);
	assert(weighta>=0);
	assert(weightb>=0);
	solve();
	solxa=suma;
	solxb=sumb;
	comp =weightb*(solxb-b0);
	comp+=weighta*(solxa-a0);
	if (dbgf) fprintf(dbgf,"-- rdecision %lld %lld | %d %d | %lld\n",weighta,weightb,solxa-a0,solxb-b0,comp);
	if (comp<0) 
	{
		rec(a0,b0,solxa,solxb,lev+1);
		rec(solxa,solxb,a1,b1,lev+1);
	}
}

int main(int argc, char *argv[])
{
	//datf=fopen("timeismoney.dat","w");
	//logf=fopen("timeismoney.log","w");
	//dbgf=fopen("timeismoney.debug","w");
	freopen("t.in", "r", stdin);
	bestprod=2000000000;
	int i,j;
	scanf("%d %d",&n,&m);
	for (i=0; i<m; i++)
	{
		scanf("%d %d %d %d",src+i,dst+i,costa+i,costb+i);
		// just to be safe
		assert(src[i]!=dst[i]);
		assert(src[i]>=0 && src[i]<n);
		assert(dst[i]>=0 && dst[i]<n);
		assert(costa[i]>0 && costa[i]<10000);
		assert(costb[i]>0 && costb[i]<10000);
	}
	weighta=0;
	weightb=1;
	solve();
	sol0a=suma;
	sol0b=sumb;
	weighta=1;
	weightb=0;
	solve();
	sol1a=suma;
	sol1b=sumb;
	rec(sol0a,sol0b,sol1a,sol1b);
	printf("%d %d\n",besta,bestb);
	return 0;
	for (i=0; i<n-1; i++)
	{
		printf("%d %d\n",src[bestsol[i]],dst[bestsol[i]]);
	}
	fcloseall();
	return 0;
}
