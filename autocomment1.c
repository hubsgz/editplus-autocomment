#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "StringArr.h"


char *trim(char *str)
{
	char *head, *rear;
	head = str;
	rear = head + strlen(str) -1;
	while (*head==' ') {
		head++;
	}
	while (*rear==' ') {
		
		printf("-->%c<--\n", *rear);
		rear = '\0';
		rear--;
	}

	return head;
}

int strpos(char *str, char *sub, int pos)
{
	int i=0,j=0;
	while (*(str+i) && *(sub+j))
	{
		if (*(str+i) == *(sub+j)) {
			++i;
			++j;
		} else {
			j = 0;
			i = i-j+1;
		}
	}
	if (j>=strlen(sub)) {
		return i-strlen(sub);
	} else {
		return -1;
	}
}

void paramPrint(char *str, int start, int end)
{
	int i;
	for (i=start; i<end; i++)
	{
		printf("%c", *(str+i));
	}
	printf("\n");
}

void printComment(struct StringArr *head, char *funName)
{
	int maxlen = StringArrMaxLen(head);

	printf("    /**\n");
	printf("      * %s\n", funName);
	printf("      *\n"); 

	if (head->data!=NULL) {
		struct StringArr *p = head;
		do
		{
			printf("      * @param type $%-*s %s\n", maxlen, p->data, p->data);
			p = p->next;
		}
		while (p!=NULL);
		printf("      *\n"); 
	}

	printf("      * @return mixed\n");
	printf("      */\n");

}


int main(int argc, char *argv[])
{	
	char *str= NULL;
	char *fstr = NULL;
	int pos;				//function��λ��
	int pos_bracket_left;	//������λ��
	int pos_bracket_right;	//������λ��
	char *functionName;		//������
	int functionLen;
	char *p;
	struct StringArr *head;  //ͷ�ڵ�
	struct StringArr *lastnode;			//β�ڵ�
	int i=0, paramNum=0, start=0, end=0;
	char c;
	char *paramName;

	if (argc==1) {
		str = "    public function getTopList (int $page,int  $pageSize=1,  array $filter=array(), $other) {   ";
	} else {
		str = argv[1];
	}	
	
	fstr = (char *)malloc((strlen(str)+1)*sizeof(char));
	strcpy(fstr, str);

	

	//function��λ��
	pos = strpos(fstr, "function", 0);

	//������λ��
	pos_bracket_left = strpos(fstr, "(", pos);
	
	//��ú�����
	functionName = (char *)malloc((pos_bracket_left-pos+1)*sizeof(char));
	functionLen = strlen("function ");
	strncpy(functionName, fstr+pos+functionLen, pos_bracket_left-functionLen-pos);
	*(functionName + (pos_bracket_left-functionLen-pos)) = '\0';
	
	//������λ��
	p = fstr+strlen(fstr)-1;
	pos_bracket_right = strlen(fstr);
	while (p>fstr && (*p!=')')) {
		pos_bracket_right--;
		p--;
	}
	
	//�ַ�������
	head = newStringArr();	//ͷ�ڵ�
	lastnode = head;			//β�ڵ�
	
	//�����ȡÿ��������	
	for (i=pos_bracket_left; i<pos_bracket_right; i++)
	{
		c = *(fstr+i);
		if (c=='$') {
			start = i+1;
		}
		if (c=='=' || c==' ' || c==',' || c==')') {
			if (start>0) {			
				end = i;
				//paramPrint(fstr, start, end);
				paramName = (char *)malloc(end-start+1);
				strncpy(paramName, fstr+start, end-start);
				*(paramName+(end-start)) = '\0';
				lastnode = StringArrAdd(lastnode, paramName);
				start = end = 0;
				paramNum++;
				continue;
			}
		}
	}

	//StringArrPrint(head);
	//��ӡע��
	printComment(head, functionName);

	//�ͷ��ڴ�
	free(fstr);
	free(functionName);
	StringArrFree(head);
	
	//StringArr����
	//void testStringArr();
	//testStringArr();

	return 0;
}

void testStringArr()
{
    struct StringArr *head = newStringArr();
    struct StringArr *new = StringArrAdd(head, "123");
    struct StringArr *new1 = StringArrAdd(new, "123456");
    struct StringArr *new2 = StringArrAdd(new1, "123789456");
	int maxlen = StringArrMaxLen(head);
    StringArrPrint(head);
	
	printf("\nmaxlen = %d \n", maxlen);
	
    StringArrFree(head);
    //getch();
}
