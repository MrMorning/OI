#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
struct Trie
{
    Trie *next[26];
    Trie *fail;
    int cnt;
    Trie()
    {
        cnt=0;
        memset(next,NULL,sizeof(next));
        fail=NULL;
    }
} *root;
void build()
{
    root=NULL;
    root=new Trie; 
}
void insert(char *s)
{
    Trie *r=root,*p;
    int i=0;
    while(s[i])
    {
        if(r->next[s[i]-'a']==NULL)
        {
            p=new Trie();
            r->next[s[i]-'a']=p;
        }
        r=r->next[s[i]-'a'];
        i++;
    }
    r->cnt++;
} 
void BuildTrie()
{
    int i;
    Trie *r=root,*p,*tmp;
    root->fail=NULL;
    queue<Trie *>q;
    q.push(root);
    while(!q.empty())
    {
        p=q.front();
        q.pop();
        for(i=0;i<26;i++)
            if(p->next[i]!=NULL)
            {
                if(p==root)
                    p->next[i]->fail=root;
                else
                {
                    tmp=p->fail;
                    while(tmp!=root&&tmp->next[i]==NULL)
                        tmp=tmp->fail;
                    if(tmp->next[i]==NULL)
                        p->next[i]->fail=root;
                    else p->next[i]->fail=tmp->next[i];
                }
                q.push(p->next[i]);
            }
    }
}
int check(char *s)
{
    int c=0;
    Trie *r=root,*p,*tmp;
    while(*s)
    {
        int idx=*s-'a';
        while(r->next[idx]==NULL&&r!=root)
            r=r->fail;
        r=r->next[idx];
        if(r==NULL)
            r=root;
        tmp=r;
        while(tmp!=root)
        {
            c+=tmp->cnt;
            tmp->cnt=0;
            tmp=tmp->fail;
        }
        s++;
    }
    return c;
}
int cas,n;
char txt[1000010],ss[52];
int main()
{
	freopen("t.in", "r", stdin);
    scanf("%d",&cas);
    while(cas--)
    {
        scanf("%d",&n);
        build();
        while(n--)
        {
            scanf("%s",ss);
            insert(ss);
        }
        scanf("%s",txt);
        BuildTrie();
        printf("%d\n",check(txt));
    }
    return 0;
}
