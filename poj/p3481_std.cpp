#include<stdlib.h>
#include<stdio.h>

typedef struct CLIENT{
	int K;
	int P;
	struct CLIENT *next;
	struct CLIENT *prior;
}CLIENT,*CLinkList;

CLinkList head;

void load(){
	head=(CLinkList)malloc(sizeof(CLIENT));
	head->next=head;
	head->prior=head;
}

void AddNode(){
	CLinkList newbase=(CLinkList)malloc(sizeof(CLIENT));
	scanf("%d%d",&newbase->K,&newbase->P);
	CLinkList reHead=head->next;
	while(reHead!=head){
		if(reHead->P>newbase->P)
			break;
		reHead=reHead->next;
	}
	reHead->prior->next=newbase;
	newbase->prior=reHead->prior;
	newbase->next=reHead;
	reHead->prior=newbase;
}

void printMax(){
	if(head->next==head){
		printf("0\n");
		return;
	}
	CLinkList del=head->prior;
	printf("%d\n",del->K);
	del->prior->next=del->next;
	del->next->prior=del->prior;
	free(del);
}

void printMin(){
	if(head->next==head){
		printf("0\n");
		return;
	}
	CLinkList del=head->next;
	printf("%d\n",del->K);
	del->prior->next=del->next;
	del->next->prior=del->prior;
	free(del);
}

void solve(){
	int code;
	while(scanf("%d",&code)&&code){
		switch(code){
			case 1:AddNode();break;
			case 2:printMax();break;
			case 3:printMin();break;
			default:
				   break;
		}
	}
}

int main(){
	freopen("t.in","r",stdin);
	load();
	solve();
	return EXIT_SUCCESS;
}
