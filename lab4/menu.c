#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "linktable.h"

int Help();
int Quit();
int Add();
int Sub();

#define CMD_MAX_LEN 128
#define DESC_LEN 1024
#define CMD_NUM 10

typedef struct DataNode
{
    tLinkTableNode *pNext;
    char *cmd;
    char *desc;
    int (*handler)();
}tDataNode;

int InitMenuData(tLinkTable **ppLinkTable)
{
    *ppLinkTable=CreateLinkTable();
    tDataNode *pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="help";
    pNode->desc="show the command menu";
    pNode->handler=Help;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode*)pNode);
    pNode=(tDataNode*)(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="version";
    pNode->desc="menu program v2.5";
    pNode->handler=NULL;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode*)pNode);
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="quit";
    pNode->desc="quit from menu of command";
    pNode->handler=Quit;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode*)pNode);
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="add";
    pNode->desc="add two numbers";
    pNode->handler=Add;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode*)pNode);
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="sub";
    pNode->desc="make a sub of two numbers";
    pNode->handler=Sub;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode*)pNode);
    return 0;
}

tLinkTable *head=NULL;

//show all cmd in list
int ShowAllCmd(tLinkTable *head)
{
    printf("menu list:\n");
    tDataNode *p=(tDataNode*)GetLinkTableHead(head);
    while(p!=NULL)
    {
        printf("%s-\n%s\n",p->cmd,p->desc);
        p=(tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode*)p);
    }
    return 0;
}

tDataNode *FindCmd(tLinkTable *head,char *cmd)
{
    tDataNode *p=(tDataNode*)GetLinkTableHead(head);
    while(p!=NULL)
    {
        if(strcmp(p->cmd,cmd)==0)
        {
            return p;
        }
        p=(tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode*)p);
    }
    return NULL;
}

int main()
{
    InitMenuData(&head);
    while(1)
    {
        char cmd[CMD_MAX_LEN];
        printf("Welcome to my command menu!\n");
        scanf("%s",cmd);
        tDataNode *p=FindCmd(head,cmd);
        if (p == NULL)
        {
            printf("this is a wrong cmd!You can input \"help\" for help\n");
            continue;
        }
        //printf("%s %s\n",p->cmd,p->desc);
        if(p->handler!=NULL)
        {
            p->handler();
        }
    }
}

int Help()
{
    ShowAllCmd(head);
    return 0;
}

int Quit()
{
    exit(0);
}
int Add()
{
    int a,b;
    printf("please input two numbers:\n");
    scanf("%d %d",&a,&b);
    int c = a+b;
    printf("Result:a+b= %d\n",c);
    return 0;
}
int Sub()
{
    int a,b;
    printf("Please input two numbers:\n");
    scanf("%d %d",&a,&b);
    int c=a-b;
    printf("Result:a-b= %d\n",c);
    return 0;
}
