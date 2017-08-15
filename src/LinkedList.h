#ifndef LinkedList_H
#define LinkedList_H

#define getEleName(ele) (((FileInfo*)((Element*)(ele))->data))->fileName
#define getEleSize(ele) (((FileInfo*)((Element*)(ele))->data))->fileSize
#define getEleCRC(ele) (((FileInfo*)((Element*)(ele))->data))->fileCRC32Value
#define getListName(list) ((FileInfo*)(list->head->data))->fileName  
#define getListSize(list) ((FileInfo*)(list->head->data))->fileSize
#define getListCRC(list) ((FileInfo*)(list->head->data))->fileCRC32Value

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

#endif // LinkedList_H
