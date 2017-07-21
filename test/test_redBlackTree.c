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

/*****************************************

	2 NODE tests

*******************************************/
/**
*    root              root
*     |     add n100    |
*     v     -------->   v
*    n200              n200	    
*    / \               / \
*   -   -           n100  -   
**/
void test_addFileNode_should_add_n100_into_n200(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	FileInfo info1 = {.fileSize = 100,. fileCRC32Value = 120000};
	Node *fileNode1 = createNode(&info1);
	//Create node 2
	FileInfo info2 = {.fileSize = 100,. fileCRC32Value = 110000};
	Node *fileNode2 = createNode(&info2);
	//Add node into RBT
	addFileNode(&nodePtr,fileNode1);
	addFileNode(&nodePtr,fileNode2);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode2,NULL,'b',nodePtr);

	free(fileNode1);
	free(fileNode2);
}

/*****************************************

	3 NODE tests

*******************************************/
/**
*     root             root
*     |    add n300     |
*     v    -------->    v
*   info1             info1        
*   /  \              /   \      
*  info2 -          info2 info3
**/
void test_addFile_add_n300_into_n100_n200_root(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	FileInfo info1 = {.fileSize = 200,. fileCRC32Value = 120000};
	Node *fileNode1 = createNode(&info1);
	//Create node 2
	FileInfo info2 = {.fileSize = 100,. fileCRC32Value = 110000};
	Node *fileNode2 = createNode(&info2);
	//Create node 3
	FileInfo info3 = {.fileSize = 200,. fileCRC32Value = 310000};
	Node *fileNode3 = createNode(&info3);
	//Add node into RBT
	addFileNode(&nodePtr,fileNode1);
	addFileNode(&nodePtr,fileNode2);
	addFileNode(&nodePtr,fileNode3);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode3);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode3,'b',nodePtr);

	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
}

/*****************************************

	4 NODE tests

*******************************************/
/**
*     root                root                         
*       |    leftRight      |                           
*       v    add n50        v       
*     n300   --------->    n200     
*     /  \                 /  \        
*   n100  -             n100   n300                  
*     \                  /                           
*     n200              n50                        
*
**/