#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "Rotation.h"
#include "compareJSON.h"
#include "RedBlackTree.h"
#include "RestructureNode.h"
#include "CustomAssertions.h"

void setUp(void){}
void tearDown(void){}

/*****************************************

	1 NODE TEST

*******************************************/
/**
*    root              root
*     |     del n200    |
*     v     -------->   v
*    n200              null	    
*    
*    
**/
void test_removeFile_should_remove_n200_and_root_become_null(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 
	unsigned long long int size = 100;
	unsigned long int crc = 1231234567;
	json_t *fileObjectSize = json_integer(size);
	json_t *fileObjectCRC = json_integer(crc);
	Node *fileNode = createNode(fileObjectSize,fileObjectCRC);
	//Add node into RBT
	addFile(&nodePtr,fileNode);
	//Del node into RBT
	Node *removedNode = removeFile(&nodePtr,fileNode);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,NULL);
	TEST_ASSERT_EQUAL_PTR(removedNode,fileNode);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode);	
}

/*****************************************

	2 NODE TEST

*******************************************/
/**
*    root              root
*     |     del n100    |
*     v     -------->   v
*    n200              n200	    
*    /  \              / \
*  n100  -            -   -
**/
void test_removeFile_should_remove_n100_from_root_and_left_n200(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 200;
	unsigned long int crc1 = 1231234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	Node *fileNode1 = createNode(fileObjectSize1,fileObjectCRC1);
	//Create node 2
	unsigned long long int size2 = 100;
	unsigned long int crc2 = 1231234567;
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	Node *fileNode2 = createNode(fileObjectSize2,fileObjectCRC2);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Delete node 2 from RBT
	Node *removedNode = removeFile(&nodePtr,fileNode2);
	//Test
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_PTR(removedNode,fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',nodePtr);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode);
}