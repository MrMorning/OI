#include <cstdio>
#include <cstring>

struct Link
{
	Link *next;
	char ch;
};

inline Link *allocLink(char ch)
{
	static Link pool[100000];
	static int freePos = 0;
	Link *x = &pool[freePos ++];
	x->ch = ch;
	return x;
}

char str1[30010], str2[30010];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%s%s", str1, str2);
	int n1 = strlen(str1),
		n2 = strlen(str2);
	Link *head = allocLink('('), *now = head;
	for(int i = 0; i < n1; i ++)
	{
		Link *next = allocLink(str1[i] - 'A' + 'a');
		now->next = next;
		now = next;
	}
	now->next = allocLink(')');
	now = head->next;
	int expandCnt = 0;
	for(int i = 0; i < n2; i ++)
	{
		if(now->ch == ')')
		{
			printf("NO\n");
			return 0;
		}
		if((now->ch == 'a' && str2[i] == 'B') 
				|| (now->ch == 'b' && str2[i] == 'A'))
			now = now->next;
		else
		{
			if(expandCnt * 2 + n1 >= n2)
			{
				printf("NO\n");
				return 0;
			}
			if(now->ch == 'a')
			{
				Link *l1 = allocLink('b'),
					 *l2 = allocLink('a');
				l1->next = l2, l2->next = now->next;
				now = l1;
				expandCnt ++;
			}
			else
			{
				Link *l1 = allocLink('a'),
					 *l2 = allocLink('b');
				l1->next = l2, l2->next = now->next;
				now = l1;
				expandCnt ++;
			}
		}
	}
	if(expandCnt * 2 + n1 == n2)
		printf("YES\n");
	else
		printf("NO\n");
}
