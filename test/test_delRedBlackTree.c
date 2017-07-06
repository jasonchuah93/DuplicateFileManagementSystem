#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "Rotation.h"
#include "compareJSON.h"
#include "redBlackTree.h"
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
	printf("value: %d",removedNode->crc32Value);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,NULL);
	TEST_ASSERT_EQUAL_PTR(removedNode,fileNode);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode);	
}

