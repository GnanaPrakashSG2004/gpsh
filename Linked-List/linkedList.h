#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <sys/types.h>

typedef struct element ElementType;
typedef struct node Node;
typedef struct list List;

struct element
{
    char *command;
    char *fullCmd;
    pid_t pid;
    long long index;
};

struct node
{
    ElementType elem;
    Node *next;
    Node *prev;
};

struct list
{
    Node *head;
    Node *tail;
    long long size;
};

Node *MakeNode(const ElementType X);
List *CreateEmptyList();
void insert(List *list, const ElementType x);
void Delete (List *list, const pid_t pid);
long long idx(const List *pidList);
char *findCMD(const List *pidList, const pid_t pid);
pid_t findPID(const List *pidList, const long long index);

#endif