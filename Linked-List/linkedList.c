#include "./../Helper-Functions/headers.h"

Node *MakeNode(ElementType X)
{
    Node *N = (Node *)malloc(sizeof(Node));
    assert(N);

    N->elem = X;
    N->next = NULL;
    N->prev = NULL;

    return N;
}

List *CreateEmptyList()
{
    List *L = (List *)malloc(sizeof(List));
    assert(L);

    L->head = NULL;
    L->tail = NULL;
    L->size = 0;

    return L;
}

void insert(List *list, ElementType X)
{
    Node *newNode = MakeNode(X);
    assert(newNode);
    (list->size)++;

    if (list->head == NULL)
    {
        newNode->prev = NULL;
        newNode->next = NULL;
        list->head = newNode;
        list->tail = newNode;
    }

    else
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        newNode->next = NULL;
    }

    return;
}

void Delete(List *list, const pid_t pid)
{
    Node *tempNode = (Node *)malloc(sizeof(Node));
    assert(tempNode);
    tempNode = list->head;

    if (!(list->head))
    {
        free(tempNode);
        return;
    }

    else if (!(list->head->next))
    {
        list->head = NULL;
        list->tail = NULL;
        (list->size)--;
    }

    else if (list->head->elem.pid == pid)
    {
        list->head = list->head->next;
        list->head->prev = NULL;
        (list->size)--;
    }

    else
    {
        while (tempNode)
        {
            if (tempNode->elem.pid == pid)
            {
                if (!(tempNode->next))
                    list->tail = tempNode->prev;

                else
                    tempNode->next->prev = tempNode->prev;

                tempNode->prev->next = tempNode->next;
                (list->size)--;

                break;
            }

            else
                tempNode = tempNode->next;
        }
    }

    free(tempNode);
    return;
}

ll idx(const List *pidList)
{
    if (pidList && pidList->tail)
        return (pidList->tail->elem.index) + 1;
    else
        return 1;
}

char *findCMD(const List *pidList, const pid_t pid)
{
    Node *tempNode = (Node *)malloc(sizeof(Node));
    assert(tempNode);
    tempNode = pidList->head;

    while (tempNode != NULL)
    {
        if (tempNode->elem.pid == pid)
            return tempNode->elem.command;
        else
            tempNode = tempNode->next;
    }

    return NULL;
}

pid_t findPID(const List *pidList, const long long index)
{
    Node *tempNode = (Node *)malloc(sizeof(Node));
    assert(tempNode);
    tempNode = pidList->head;

    while (tempNode != NULL)
    {
        if (tempNode->elem.index == index)
            return tempNode->elem.pid;
        else
            tempNode = tempNode->next;
    }

    return -1;
}