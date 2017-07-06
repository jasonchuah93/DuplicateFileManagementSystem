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

	1 NODE tests

*******************************************/
/**
*   root              root
*	 |    add n100     |
*	 v    --------->   v
*	NULL              n100
**/
void test_addFile_should_add_fileNode_into_empty_root(void){
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
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode);	
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
void test_addFile_should_add_n100_into_n200(void){
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
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode2,NULL,'b',nodePtr);		
}

/**
*       root                root
*         |     add n500      |
*         v    --------->     v
*        n200               n200       
*        /  \               /   \
*      -     -             -   n500
**/
void test_addFile_should_add_n500_into_n200(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 200;
	unsigned long int crc1 = 1231234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	Node *fileNode1 = createNode(fileObjectSize1,fileObjectCRC1);
	//Create node 2
	unsigned long long int size2 = 500;
	unsigned long int crc2 = 1231234567;
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	Node *fileNode2 = createNode(fileObjectSize2,fileObjectCRC2);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,fileNode2,'b',nodePtr);		
}

/*****************************************

	3 NODE tests

*******************************************/
/**
*     root             root
*     |    add n300     |
*     v    -------->    v
*   n200              n200        
*   /  \              /   \      
*  n100 -          n100  n300
**/
void test_addFile_add_n300_into_n100_n200_root(void){
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
	//Create node 3
	unsigned long long int size3 = 300;
	unsigned long int crc3 = 1231234567;
	json_t *fileObjectSize3 = json_integer(size3);
	json_t *fileObjectCRC3 = json_integer(crc3);
	Node *fileNode3 = createNode(fileObjectSize3,fileObjectCRC3);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode3);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode3);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode3,'b',nodePtr);		
}

/**
*        root                root
*          |       add n100   |
*          v      --------->  v
*        n200               n200    
*       /    \              /  \
*      -    n300         n100  n300  
**/
void test_addFile_add_n100_into_n300_n200_root(void){
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
	//Create node 3
	unsigned long long int size3 = 300;
	unsigned long int crc3 = 1231234567;
	json_t *fileObjectSize3 = json_integer(size3);
	json_t *fileObjectCRC3 = json_integer(crc3);
	Node *fileNode3 = createNode(fileObjectSize3,fileObjectCRC3);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode3);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode2);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode3);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode3,'b',nodePtr);		
}

/**
*        root              root                        root
*         |    add n400      |                          |
*         v    -------->     v      leftRotate          v  
*       n200               n200                        n300
*       /  \              /   \    ------------->     /   \
*     -   n300           -    n300                  n200  n400 
*                               \                     
*                              n400                
*
**/
void test_addRecord_add_n400_into_n200_n300_and_leftRotate(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 200;
	unsigned long int crc1 = 1231234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	Node *fileNode1 = createNode(fileObjectSize1,fileObjectCRC1);
	//Create node 2
	unsigned long long int size2 = 300;
	unsigned long int crc2 = 1231234567;
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	Node *fileNode2 = createNode(fileObjectSize2,fileObjectCRC2);
	//Create node 3
	unsigned long long int size3 = 400;
	unsigned long int crc3 = 1231234567;
	json_t *fileObjectSize3 = json_integer(size3);
	json_t *fileObjectCRC3 = json_integer(crc3);
	Node *fileNode3 = createNode(fileObjectSize3,fileObjectCRC3);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode3);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode3);
	TEST_ASSERT_EQUAL_NODE(fileNode1,fileNode3,'b',nodePtr);		
}