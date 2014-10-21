#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "StringArr.h"

struct StringArr *newStringArr()
{
    struct StringArr *p = (struct StringArr *)malloc(sizeof(struct StringArr));
    p->data = NULL;
    p->next = NULL;
    return  p;
}

struct StringArr *StringArrAdd(struct StringArr *node, char *str)
{
      if (node->data==NULL) {
         node->data = str;
         return node;
      } else {
         struct StringArr *p = (struct StringArr *)malloc(sizeof(struct StringArr));
         p->data = str;
         p->next = node->next;
         node->next = p;
         return p;
      }
}

void StringArrFree(struct StringArr *head)
{
    struct StringArr *p = head;
    while(head->next != NULL)
    {
        head = head->next;
        free(p->data);
        free(p);
        p = head;
    }
    free(head->data);
    free(head);
}

int StringArrMaxLen(struct StringArr *head)
{
	struct StringArr *p = head;
	int len=0, maxlen=0;
    if (head->data == NULL) {
        return 0;
    } else {
		while(1)
		{
			len = strlen(p->data);
			if (len>maxlen) {
				maxlen = len;
			}
			p = p->next;
			if (p==NULL) {
				break;
			}
		}
	}
	return maxlen;
}	

void StringArrPrint(struct StringArr *head)
{
    struct StringArr *p = head;
    if (head->data == NULL) {
        printf("empty");
    } else {
		while(1)
		{
			printf("%s\n", p->data);
			p = p->next;
			if (p==NULL) {
				break;
			}
		}
    }
}
