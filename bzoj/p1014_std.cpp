#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
FILE *fin=fopen( "t.in" , "r" );
int q,size,len;
unsigned pow3137[110000];
char s[110000];
struct node{
       node *l,*r,*fa; int siz; char ch; unsigned hash;
       void update(){
            siz=(!l?0:l->siz)+1+(!r?0:r->siz);
            hash=(l?l->hash:0)*3137+ch;
            if(r) hash=hash*pow3137[r->siz]+r->hash;
       }
       void rl(){
            node *p=fa;  p->r=l;
            if(p->r) p->r->fa=p;
            fa=p->fa;   if(fa){
              if(fa->l==p) fa->l=this;
              else fa->r=this; }
            p->fa=this;  l=p; p->update();
       }
       void rr(){
            node *p=fa;  p->l=r;
            if(p->l) p->l->fa=p;
            fa=p->fa;   if(fa){
               if(fa->l==p) fa->l=this;
               else fa->r=this; }
            p->fa=this;  r=p; p->update();
       }
       void splay(node*);
       node* build(int,int);
       node* findk(int);
}a[110000],*T;

void node::splay(node *t=NULL){
     while(fa!=t){
         if(fa->fa==t){
            if(fa->l==this) rr();
            else rl();
         }
         else{
            if(fa->fa->l==fa){
               if(fa->l==this) fa->rr();
               else rl();  rr();
            }
            else{
               if(fa->r==this) fa->rl();
               else rr();  rl();
            }
         }
     }
     if(t==NULL) T=this;
     update();
}

node* node::build(int b,int e){
      if(b>e) return NULL;
      int mid=b+e>>1;
      node *ret=&a[++size];
      ret->ch=s[mid];
      ret->l=build(b,mid-1);
      ret->r=build(mid+1,e);
      if(ret->l) ret->l->fa=ret;
      if(ret->r) ret->r->fa=ret;
      ret->update();
      return ret;
}

node* node::findk(int k){
      node *ret=T;
      while(1){
         int sz=(ret->l?ret->l->siz:0)+1;
         if(sz>k) ret=ret->l;
         else if(sz==k) return ret;
         else{
              k-=sz;
              ret=ret->r;
         }
      }
}

unsigned Gethash(int x,int l){
         if(x==1){
              node *p=node().findk(x+l);
              p->splay();
              return p->l->hash;
         }
         else if(x+l>len){
              node *p=node().findk(x-1);
              p->splay();
              return p->r->hash;
         }
         else{
              node *p=node().findk(x-1),*q=node().findk(x+l);
              p->splay();
              q->splay(p);
              return q->l->hash;
         }
}
bool Check(int x,int y,int mid){
     return Gethash(x,mid)==Gethash(y,mid);
}
void Replace(int x,char ch){
     node *p=node().findk(x);
     p->ch=ch;
     p->splay();
}
void Insert(int x,int ch){
     node *p=node().findk(x),*q;
     p->splay();
     if(p->r==NULL){
          p->r=&a[++size];
          p->r->ch=ch;
          p->r->fa=p;
          p->r->update();
          p->update();
     }
     else{
          q=node().findk(x+1);
          q->splay(p);
          q->l=&a[++size];
          q->l->ch=ch;
          q->l->fa=q;
          q->l->update();
          q->update();
          p->update();
     }
}

void debug(node *t){
     if(t==NULL) return;
     debug(t->l);
     fprintf(stdout,"%c",t->ch);
     debug(t->r);
}

int main(){
    fscanf(fin,"%s%d",s,&q);
    len=strlen(s);
    for(int i=0;i<len;i++) s[i]=tolower(s[i]);
    pow3137[0]=1;
    for(int i=1;i<100001;i++)
      pow3137[i]=pow3137[i-1]*3137;
   
    T=node().build(0,len-1);
   
    int x,y;
    char ch;
    while(q--){
       fscanf(fin,"%s",s);
     //  debug(T);
      // fprintf(stdout,"\n");
       if(s[0]=='Q'){
          fscanf(fin,"%d%d",&x,&y);
          if(x==y){
             fprintf(stdout,"%d\n",len-x+1);
             continue;
          }
          int lo=0,hi=min(len-y+1,len-x+1)+1,mid;
          while(lo+1<hi){
             mid=lo+hi>>1;
             if(Check(x,y,mid)) lo=mid;
             else hi=mid;
          }
          fprintf(stdout,"%d\n",lo);
       }
       else if(s[0]=='R'){
            fscanf(fin,"%d %c",&x,&ch);
            Replace(x,ch);
       }
       else{
            fscanf(fin,"%d %c",&x,&ch);
            Insert(x,ch);
            len++;
       }
    }
   
    return 0;
}
