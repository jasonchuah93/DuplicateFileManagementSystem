#include <stdio.h>
#include <malloc.h>
#include "LinkedList.h"

Element *createElement(void *fileInfo){
	Element *element = malloc(sizeof(Element));
	element->data = fileInfo;
	element->next = NULL;
	return element;
}

LinkedList *createLinkedList(){
	LinkedList *list = malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
	return list;
}

Element *listAddFirst(Element *newElement, LinkedList *list){
	if(list->head == NULL && list->tail == NULL){
		list->head = list->tail = newElement;
		newElement -> next = NULL;
	}else{
		newElement->next=list->head;
		list->head=newElement;
	}
	list->length++;
}

Element *listRemoveFirst(LinkedList *list){
	Element *tempElement;
	if(list->head == NULL && list->tail == NULL)
		return NULL;
	if(list->head==list->tail){
		tempElement =list->head;
		list->head=list->tail = NULL;	
	}else{
		tempElement =list->head ;
		list->head=list->head->next;
	}
	list->length--;
	return tempElement;	
}

Element *listAddLast(Element *newElement, LinkedList *list){
	if(list->head == NULL && list->tail == NULL){
		list->head = list->tail = newElement;
		newElement -> next = NULL;
	}else{
		newElement->next=list->tail;
		list->tail=newElement;
	}
	list->length++;
}

Element *listRemoveLast(LinkedList *list){
	Element *tempElement;
	if(list->head == NULL && list->tail == NULL)
		return NULL;
	if(list->head==list->tail){
		tempElement =list->head;
		list->head=list->tail = NULL;	
	}else{
		tempElement =list->tail ;
		list->tail=list->tail->next;
	}
	list->length--;
	return tempElement;	
}