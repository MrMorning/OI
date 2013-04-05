#include"stdio.h"
#define s(x) x=readInt(buffer)
int mulx[10007],muly[10007],cpos[10010],lookup[20020],p,inv[20020];
void solve(int x,int p,int& n,int& k)
{
  if(x==1)
  {
    n=1;k=0;return;
  }
  solve(p%x,x,k,n);
  n=n-k*(p/x);
  int r=-1-(n/p);
  n=n-p*r;
  k=k+x*r;
}
int inverse(int x,int p)
{
  int n,k;
  solve(x,p,n,k);
  return n;
}
void multiply(int a[3][3],int b[3][3])//a*=b
{
  int c[3];
  for(int j=0;j<3;j++)
  {
    c[j]=a[0][0]*b[0][j]+a[0][1]*b[1][j];
  }
  c[2]+=a[0][2];
  c[0]%=p,c[1]%=p,c[2]%=p;
  for(int j=0;j<3;j++)a[1][j]=a[0][j],a[0][j]=c[j];
}
int look(int x,int l,int r)
{
  if(l==r)return l;
  int mid=(l+r)>>1;
  if(cpos[mid]<=x)return look(x,mid+1,r);
  return look(x,l,mid);
}
long long find(long long l,int ct,int i,int period)
{
  return (l/period)*ct+look((int)(l%period),1,i)-1;
}
/** begin fast IO*/
int i;
char buffer[3012500];
void initRead(char* buffer)
{
  fread(buffer,1,3012500,stdin);i=0;
}
int readInt(char* buffer)
{
  int num=0;
  while(buffer[i]<=32)i++;
  while(buffer[i]>32)
    num=num*10+buffer[i]-'0',i++;
  return num;
}
long long readLongLong(char* buffer)
{
  long long num=0;
  while(buffer[i]<=32)i++;
  while(buffer[i]>32)
    num=num*10+buffer[i]-'0',i++;
  return num;
}
/** end fast IO*/
int a,b,x,y,z,c,q;
void solve0()
{
  int a0=a,b0=b;
  a=lookup[mulx[b]+muly[a]];
  b=lookup[mulx[a]+muly[b]];
  int save1=a,save2=b,period=0,i=1;
  int diff=0,last=0;
  do
  {
    if(a==c){	cpos[i++]=period<<1;		if(cpos[i-1]-last>diff)diff=cpos[i-1]-last;	last=cpos[i-1];		}
    if(b==c){	cpos[i++]=(period<<1)+1;	if(cpos[i-1]-last>diff)diff=cpos[i-1]-last;	last=cpos[i-1];		}
    period++;
    a=lookup[mulx[b]+muly[a]];
    b=lookup[mulx[a]+muly[b]];
  }while(a!=save1||b!=save2);
  period<<=1;
//   printf("period= %d\ti=%d\tmaxdiff=%d\n",period,i,diff);
  int count=i-1,tt=0;
  cpos[i]=period+1;
  long long first,second,ans;
  for(;tt<q;tt++)
  {
    first=readLongLong(buffer),
    second=readLongLong(buffer),
    ans=((a0==c)&&(second>=1)&&(first<=1))?1:0,
    ans+=((b0==c)&&(second>=2)&&(first<=2))?1:0;
    first-=3,second-=3;
    if(second>=0)
    {
      ans+=find(second,count,i,period);
      if(first>0)ans-=find(first-1,count,i,period);
    }
    printf("%Ld\n",ans);
  }
}
void solve1()
{
  int a0=a,b0=b;
  int offset=0,alpha=-1,add=0,i=1;
  do
  {
    if(a==c)	{alpha=b;			add=0;	break;}
    if(b==c)	{alpha=lookup[mulx[b]+muly[a]];	add=1;	break;}
    offset++;
    a=lookup[mulx[b]+muly[a]];
    b=lookup[mulx[a]+muly[b]];
  }while(a!=a0||b!=b0);
  offset=offset*2+add;
  int count,cyclelen=0;
  if(alpha>=0)
  {
    int period=0,power[3][3],matrix[3][3],next[p],nextafter[p],last=alpha;
    for(int l=0;l<9;l++)power[l/3][l%3]=matrix[l/3][l%3]=0;
    power[0][0]=power[1][1]=power[2][2]=1;
    matrix[0][0]=x,matrix[0][1]=y,matrix[0][2]=z,matrix[1][0]=matrix[2][2]=1;
    for(int x=0;x<p;x++)nextafter[x]=next[x]=-1;
    cpos[i++]=0;
//     printf("%d:%d\n",i-1,cpos[i-1]+offset);
    while(next[last]!=alpha)
    {
      multiply(power,matrix);
      period++;
      int x=power[1][0],y=power[1][1],z=power[1][2];
      if(x)
      {
	int alpha=(inv[x]*((p-z+c*(p+1-y))%p))%p;
	if(nextafter[alpha]<0)
	  nextafter[alpha]=period,
	  count++,
	  next[alpha]=(power[0][0]*alpha+power[0][1]*c+power[0][2])%p;
      }
      else if((c*y+z)%p==c)
	    for(int alpha=0;alpha<p;alpha++)
	      if(nextafter[alpha]<0)
		nextafter[alpha]=period,
		next[alpha]=(power[0][0]*alpha+power[0][1]*c+power[0][2])%p;
      while(next[last]>=0&&next[last]!=alpha)cyclelen+=nextafter[last],cpos[i++]=cyclelen/*,printf("%d:%d\n",i-1,cpos[i-1]+offset)*/,last=next[last];
      if(next[last]==alpha)cyclelen+=nextafter[last],cpos[i]=cyclelen/*,printf("%d:%d\n",i,cpos[i]+offset)*/;
    }
    count=i-1;
  }else cpos[1]=2,count=0,cyclelen=1;
//   printf("i=%d\tcyclelength=%d\n",i,cyclelen);
  long long first,second,ans;
  int tt=0;
  for(;tt<q;tt++)
  {
    first=readLongLong(buffer),
    second=readLongLong(buffer),
    ans=0,
    first-=offset+1,second-=offset+1;
    if(second>=0)
    {
      ans+=find(second,count,i,cyclelen);
      if(first>0)ans-=find(first-1,count,i,cyclelen);
    }
    printf("%Ld\n",ans);
  }
}
int main()
{
	freopen("t.in", "r", stdin);
  initRead(buffer);
  int t;
  s(t);
  while(t--)
  {
    s(a),s(b),s(x),s(y),s(z),s(p),s(c),s(q);
    a%=p,b%=p,c%=p,x%=p,y%=p,z%=p;
    mulx[0]=muly[0]=0;
    int i=1;
    for(;i<p;i++){
      inv[i]=inv[i+p]=inverse(i,p);
      mulx[i]=mulx[i-1]+x,
      muly[i]=muly[i-1]+y;
      if(mulx[i]>=p)mulx[i]-=p;
      if(muly[i]>=p)muly[i]-=p;
    }
    int tkk=z;
    for(i=0;i<p;i++,tkk++){
      if(tkk>=p)tkk-=p;
      lookup[i]=lookup[i+p]=tkk;
    }
    if(y==0)
      solve0();
    else solve1();
  }
}

