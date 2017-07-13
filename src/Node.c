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
Node *createNode(json_t *fileObjectSize,json_t *fileObjectCRC){
	Node *node  = malloc(sizeof(Node));
	node->fileSize  = json_integer_value(fileObjectSize);
	node->crc32Value = json_integer_value(fileObjectCRC);
	node->left  = NULL;
	node->right = NULL;
	node->color = 'r';
	return node;
}

/****************************************************************************
    This function will create node which contain a json type of file size 
	and json type of file crc as the input parameters.
    Return information in node when the function end.
	Input  : fileObjectSize, fileObjectCRC
    Output : node
****************************************************************************/
Node *createNodeWithFileInfo(json_t *fileObjectName,json_t *fileObjectSize,json_t *fileObjectCRC){
	Node *node  = malloc(sizeof(Node));
	node->pathName = json_string_value(fileObjectName);
	node->fileSize  = json_integer_value(fileObjectSize);
	node->crc32Value = json_integer_value(fileObjectCRC);
	node->left  = NULL;
	node->right = NULL;
	node->color = 'r';
	return node;
}
