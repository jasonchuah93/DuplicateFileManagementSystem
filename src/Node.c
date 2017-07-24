#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "jansson.h"
#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "Node.h"

/****************************************************************************
    This function will create node which contain a json type of file size 
	and json type of file crc as the input parameters.
    Return information in node when the function end.
	Input  : fileObjectSize, fileObjectCRC
    Output : node
****************************************************************************/
Node *createNode(void *element){
	Node *node  = malloc(sizeof(Node));
	node->left  = NULL;
	node->right = NULL;
	node->color = 'r';
	node->data = element;
	return node;
}
