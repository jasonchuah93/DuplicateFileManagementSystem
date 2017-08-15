#include <string.h>
#include <malloc.h>
#include "fileInfo.h"
#include "Node.h"

Node *createNode(void *fileInfo){
	Node *node  = malloc(sizeof(Node));
	node->left  = NULL;
	node->right = NULL;
	node->color = 'r';
	node->data = fileInfo;
	return node;
}

