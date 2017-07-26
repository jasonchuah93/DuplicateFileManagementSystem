#ifndef LinkedList_H
#define LinkedList_H

#include "Node.h"

typedef struct Element_t{
	struct Element_t *next;
	void *data;
}Element;

typedef struct{
	Element *head;
	Element *tail;
	int length;
}LinkedList;

Element *createElement(void *fileInfo);
LinkedList *createLinkedList();
void *listAddFirst(Element *newElement, LinkedList *list);
Element *listRemoveFirst(LinkedList *list);
Element *listAddLast(Element *newElement, LinkedList *list);
Element *listRemoveLast(LinkedList *list);

#endif // LinkedList_H
