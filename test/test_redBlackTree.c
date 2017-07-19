#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "JSON.h"
#include "jansson.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "Node.h"
#include "errorNode.h"
#include "compareJSON.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "CustomAssertions.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

/*****************************************

	1 NODE tests

*******************************************/
/**
*   root              root
*	 |    add n100     |
*	 v    --------->   v
*	NULL              n100
**/
void test_addFileNode_should_add_fileNode_into_empty_root(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 
	FileInfo info = {.fileName = "jason.txt",.fileSize = 3016,. fileCRC32Value = 110000};
	Node *fileNode = createNode(&info);
	//Add node into RBT
	addFileNode(&nodePtr,fileNode);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode);
		
	free(fileNode);
}

