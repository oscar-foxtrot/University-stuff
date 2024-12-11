struct Node
{
    struct Node *prev, *next;
    char *elem;
};
struct List
{
    struct Node *first, *last;
};



#include <string.h>
#include <stdlib.h>
void process(struct List* pl, const char* str)
{
	struct Node* tmpl = pl->first;
	struct Node* oldlast = pl->last;
	if (!pl->first || (!pl->first ^ !pl->last)) return;

	while (pl->first != oldlast) //process the first element (multiple times if needed)
	{
		char cmpres = strcmp(pl->first->elem, str);
		if (!cmpres)
		{
			tmpl = tmpl->next;
			free(pl->first);
			if (tmpl) { tmpl->prev = NULL; pl->first = tmpl; }
			else { pl->first = NULL; pl->last = NULL; return; }
		}
		else
		{
			if (!pl->first->next) return;
			tmpl = pl->first->next;
			if (cmpres > 0)
			{
				tmpl->prev = NULL;
				pl->first->next = NULL;
				pl->first->prev = pl->last;
				pl->last->next = pl->first;
				pl->last = pl->first;
				pl->first = tmpl;
			}
			else break;
		}
	}

	while (tmpl != oldlast) //processing the middle
	{
		char cmpres = strcmp(tmpl->elem, str);
		if (cmpres >= 0)
		{
			tmpl->prev->next = tmpl->next;
			struct Node* tmpl2 = tmpl;
			tmpl = tmpl->next;
			tmpl->prev = tmpl2->prev;
			if (!cmpres) free(tmpl2);
			else
			{
				pl->last->next = tmpl2;
				tmpl2->prev = pl->last;
				tmpl2->next = NULL;
				pl->last = tmpl2;
			}
		}
		else tmpl = tmpl->next;
	}

	char cmpres = strcmp(tmpl->elem, str);
	if (!cmpres)
	{
		if (!tmpl->next && !tmpl->prev) pl->first = pl->last = NULL;
		else if (!tmpl->next) 
		{
			tmpl->prev->next = NULL;
			pl->last = tmpl->prev;
		}
		else if (!tmpl->prev)
		{
			pl->first = tmpl->next;
			pl->first->prev = NULL;
		}
		else
		{
			tmpl->prev->next = tmpl->next;
			tmpl->next->prev = tmpl->prev;
		}
		free(tmpl);
	}
	else if (cmpres > 0 && tmpl->next)
	{
		if (!tmpl->prev) { tmpl->next->prev = NULL; pl->first = tmpl->next; }
		else 
		{
			tmpl->prev->next = tmpl->next;
			tmpl->next->prev = tmpl->prev;
		}
		tmpl->prev = pl->last;
		pl->last->next = tmpl;
		pl->last = tmpl;
		pl->last->next = NULL;
	}
}



#include <stdio.h>
int main() 
{
	struct List klo;
	struct List *pl1 = &klo;

	/*pl1->first = malloc(sizeof(struct Node));
	pl1 -> first -> next = malloc(sizeof(struct Node));
	pl1 -> last = pl1 -> first -> next -> next = malloc(sizeof(struct Node));
	pl1 -> first -> next -> prev = pl1 -> first;
	pl1 -> first -> next -> next -> prev = pl1 -> first -> next;
	pl1 -> first -> next -> next -> next = NULL;
	pl1->first->prev = NULL;
	pl1->last->next = malloc(sizeof(struct Node));
	pl1->last->next->prev = pl1->last;
	pl1->last = pl1->last->next;
	pl1->last->next = NULL;*/
	pl1->first = malloc(sizeof(struct Node));
	pl1->first->next = malloc(sizeof(struct Node));
	pl1->first->next->next = NULL;
	pl1->first->next->prev = pl1->first;
	pl1->last = pl1->first->next;
	pl1->first->prev = NULL;


	struct Node *tmpl = pl1 -> first;
	for(int i = 1; i<=2; ++i)
	{
		tmpl -> elem = malloc(10);
		scanf("%s", tmpl -> elem);
		tmpl = tmpl -> next;
	}
	process(pl1, "a");

	/////////////
	printf("\n");
	tmpl = pl1 -> first;
	if (pl1->first)
	{
		while (tmpl)
		{
			printf("%s ", tmpl -> elem);
			tmpl = tmpl -> next;
		}
	}
	else printf("NULL");

	return 0;
}