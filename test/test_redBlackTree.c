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

	free(fileNode1);
	free(fileNode2);
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

	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
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

	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
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
void test_addFile_add_n400_into_n200_n300_and_leftRotate(void){
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

	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
}

/**
*        root               root                      root        
*         |     add n50	     |                         |     
*         v    -------->     v     rightRotate         v  
*       n200                n200   at n100            n100
*       /   \              /    \  ------------->     /  \
*     n100   -           n100    -                  n50  n200 
*                        /
*                      n50
*
**/
void test_addFile_add_n50_into_n100_n200_root_and_rightRotate(void){
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
	unsigned long long int size3 = 50;
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
	TEST_ASSERT_EQUAL_NODE(fileNode3,fileNode1,'b',nodePtr);		
	
	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
}

/**
*     root                root                         root
*       |    add n200       |                            |
*       v    --------->     v       leftRightRotate      v  
*     n300                 n300     at n100             n200
*     /  \                 /  \   --------------->      /  \
*   n100  -             n100   -                     n100  n300
*                           \
*                          n200
**/
void test_addFile_add_n200_into_n100_n300_root_and_do_leftRightRotate(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 300;
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
	unsigned long long int size3 = 200;
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
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode3);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode1,'b',nodePtr);	

	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
}

/**
*       root            root                            root
*        |    add n250	  |                               |
*        v   --------->   v      rightLeftRotate          v  
*       n200             n200                            n250
*     /    \            /  \    ------------->          /   \
*   -     n300         -   n300                       n200  n300
*                           /
*                          n250             
*
**/
void test_addFile_add_n250_into_n300_n200_root_and_do_rightLeftRotate(void){
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
	unsigned long long int size3 = 250;
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
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode3);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode1,fileNode2,'b',nodePtr);	

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
void test_addFile_add_n50_into_n200_n100_n300_root(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 300;
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
	unsigned long long int size3 = 200;
	unsigned long int crc3 = 1231234567;
	json_t *fileObjectSize3 = json_integer(size3);
	json_t *fileObjectCRC3 = json_integer(crc3);
	Node *fileNode3 = createNode(fileObjectSize3,fileObjectCRC3);
	//Create node 4
	unsigned long long int size4 = 50;
	unsigned long int crc4 = 1231234567;
	json_t *fileObjectSize4 = json_integer(size4);
	json_t *fileObjectCRC4 = json_integer(crc4);
	Node *fileNode4 = createNode(fileObjectSize4,fileObjectCRC4);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode3);
	//Add node 4 into RBT
	addFile(&nodePtr,fileNode4);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode3);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode4);
	TEST_ASSERT_EQUAL_NODE(fileNode4,NULL,'b',fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode1);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode1,'b',nodePtr);		
	
	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
	free(fileNode4);
}

/**
*       root            root                      
*        |    add n25	  |                        
*        v   --------->   v      
*       n200             n200   
*     /    \            /  \    
*   n50     n300      n50   n300
*                     /   
*                   n25 
*
**/
void test_addFile_add_n25_into_n50_n300_n200_root(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 200;
	unsigned long int crc1 = 1231234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	Node *fileNode1 = createNode(fileObjectSize1,fileObjectCRC1);
	//Create node 2
	unsigned long long int size2 = 50;
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
	//Create node 4
	unsigned long long int size4 = 25;
	unsigned long int crc4 = 1231234567;
	json_t *fileObjectSize4 = json_integer(size4);
	json_t *fileObjectCRC4 = json_integer(crc4);
	Node *fileNode4 = createNode(fileObjectSize4,fileObjectCRC4);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode3);
	//Add node 4 into RBT
	addFile(&nodePtr,fileNode4);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode4);
	TEST_ASSERT_EQUAL_NODE(fileNode4,NULL,'b',fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode3);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode3,'b',nodePtr);	

	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
	free(fileNode4);
}

/**
*       root            root                      
*        |    add n100	  |                        
*        v   --------->   v      
*       n200             n200   
*     /    \            /  \    
*   n50     n300      n50   n300
*                       \   
*                      n100 
*
**/
void test_addFile_add_n100_into_n50_n300_n200_root(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 200;
	unsigned long int crc1 = 1231234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	Node *fileNode1 = createNode(fileObjectSize1,fileObjectCRC1);
	//Create node 2
	unsigned long long int size2 = 50;
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
	//Create node 4
	unsigned long long int size4 = 100;
	unsigned long int crc4 = 1231234567;
	json_t *fileObjectSize4 = json_integer(size4);
	json_t *fileObjectCRC4 = json_integer(crc4);
	Node *fileNode4 = createNode(fileObjectSize4,fileObjectCRC4);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode3);
	//Add node 4 into RBT
	addFile(&nodePtr,fileNode4);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode4);
	TEST_ASSERT_EQUAL_NODE(NULL,fileNode4,'b',fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode3);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode3,'b',nodePtr);	

	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
	free(fileNode4);
}

/**
*       root            root                      
*        |    add n250	  |                        
*        v   --------->   v      
*       n200             n200   
*     /    \            /  \    
*   n50     n300      n50   n300
*                           /   
*                          n250 
*
**/
void test_addFile_add_n250_into_n50_n300_n200_root(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 200;
	unsigned long int crc1 = 1231234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	Node *fileNode1 = createNode(fileObjectSize1,fileObjectCRC1);
	//Create node 2
	unsigned long long int size2 = 50;
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
	//Create node 4
	unsigned long long int size4 = 250;
	unsigned long int crc4 = 1231234567;
	json_t *fileObjectSize4 = json_integer(size4);
	json_t *fileObjectCRC4 = json_integer(crc4);
	Node *fileNode4 = createNode(fileObjectSize4,fileObjectCRC4);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode3);
	//Add node 4 into RBT
	addFile(&nodePtr,fileNode4);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode4);
	TEST_ASSERT_EQUAL_NODE(fileNode4,NULL,'b',fileNode3);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode3,'b',nodePtr);	

	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
	free(fileNode4);
}

/**
*       root            root                      
*        |    add n500	  |                        
*        v   --------->   v      
*       n200             n200   
*     /    \            /  \    
*   n50     n300      n50   n300
*                            \   
*                            n5000
*
**/
void test_addFile_add_n500_into_n50_n300_n200_root(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 200;
	unsigned long int crc1 = 1231234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	Node *fileNode1 = createNode(fileObjectSize1,fileObjectCRC1);
	//Create node 2
	unsigned long long int size2 = 50;
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
	//Create node 4
	unsigned long long int size4 = 5000;
	unsigned long int crc4 = 1231234567;
	json_t *fileObjectSize4 = json_integer(size4);
	json_t *fileObjectCRC4 = json_integer(crc4);
	Node *fileNode4 = createNode(fileObjectSize4,fileObjectCRC4);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode3);
	//Add node 4 into RBT
	addFile(&nodePtr,fileNode4);
	//Test 
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode4);
	TEST_ASSERT_EQUAL_NODE(NULL,fileNode4,'b',fileNode3);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode3,'b',nodePtr);		
	
	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
	free(fileNode4);
}

/*****************************************

	More NODE tests

*******************************************/

/**
*       root              root      Add n300              root
*        |    add n300(2)  |        Same Value Detected    |          
*        v   --------->    v        Compare CRC instead    v
*       n200              n200      --------------------> n300(2)
*     /    \              /  \                            /  \
*   n50     n300       n50  n300(1)                    n200  n5000   
*            \                 \                       / \
*            n500            n5000                  n50  n300(1)
*
**/
void test_addFile_add_same_size_value_into_tree_to_compare_crc(void){
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 200;
	unsigned long int crc1 = 1231231234;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	Node *fileNode1 = createNode(fileObjectSize1,fileObjectCRC1);
	//Create node 2
	unsigned long long int size2 = 50;
	unsigned long int crc2 = 1121234567;
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	Node *fileNode2 = createNode(fileObjectSize2,fileObjectCRC2);
	//Create node 3
	unsigned long long int size3 = 300;
	unsigned long int crc3 = 1231234567;
	json_t *fileObjectSize3 = json_integer(size3);
	json_t *fileObjectCRC3 = json_integer(crc3);
	Node *fileNode3 = createNode(fileObjectSize3,fileObjectCRC3);
	//Create node 4
	unsigned long long int size4 = 5000;
	unsigned long int crc4 = 4231234567;
	json_t *fileObjectSize4 = json_integer(size4);
	json_t *fileObjectCRC4 = json_integer(crc4);
	Node *fileNode4 = createNode(fileObjectSize4,fileObjectCRC4);
	//Create node 5
	unsigned long long int size5 = 300;
	unsigned long int crc5 = 3211234567;
	json_t *fileObjectSize5 = json_integer(size5);
	json_t *fileObjectCRC5 = json_integer(crc5);
	Node *fileNode5 = createNode(fileObjectSize5,fileObjectCRC5);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode3);
	//Add node 4 into RBT
	addFile(&nodePtr,fileNode4);
	//Add node 5 into RBT
	addFile(&nodePtr,fileNode5);
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode5);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode3,'r',fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode4);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode3);
	TEST_ASSERT_EQUAL_NODE(fileNode1,fileNode4,'b',nodePtr);

	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
	free(fileNode4);
	free(fileNode5);
}
/**
*       root              root                               root
*        |    add n300(2)  |        Same Value,crc detected    |          
*        v   --------->    v        Throw instead              v
*       n200              n200      -------------------->     n200
*     /    \              /  \                                /  \
*   n50     n300       n50  n300(1)                        n50  n300(1)   
*            \                 \                                    \ 
*            n500            n5000                                  n50000  
*
**/
void test_addFile_add_same_crc_value_into_tree(void){
	Error *e = NULL;
	//Initialize root
	Node *nodePtr = NULL;
	//Create node 1
	unsigned long long int size1 = 200;
	unsigned long int crc1 = 1231231234;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	Node *fileNode1 = createNode(fileObjectSize1,fileObjectCRC1);
	//Create node 2
	unsigned long long int size2 = 50;
	unsigned long int crc2 = 1121234567;
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	Node *fileNode2 = createNode(fileObjectSize2,fileObjectCRC2);
	//Create node 3
	unsigned long long int size3 = 300;
	unsigned long int crc3 = 1231234567;
	json_t *fileObjectSize3 = json_integer(size3);
	json_t *fileObjectCRC3 = json_integer(crc3);
	Node *fileNode3 = createNode(fileObjectSize3,fileObjectCRC3);
	//Create node 4
	unsigned long long int size4 = 5000;
	unsigned long int crc4 = 4231234567;
	json_t *fileObjectSize4 = json_integer(size4);
	json_t *fileObjectCRC4 = json_integer(crc4);
	Node *fileNode4 = createNode(fileObjectSize4,fileObjectCRC4);
	//Create node 5
	unsigned long long int size5 = 300;
	unsigned long int crc5 = 1231234567;
	json_t *fileObjectSize5 = json_integer(size5);
	json_t *fileObjectCRC5 = json_integer(crc5);
	Node *fileNode5 = createNode(fileObjectSize5,fileObjectCRC5);
	//Add node 1 into RBT
	addFile(&nodePtr,fileNode1);
	//Add node 2 into RBT
	addFile(&nodePtr,fileNode2);
	//Add node 3 into RBT
	addFile(&nodePtr,fileNode3);
	//Add node 4 into RBT
	addFile(&nodePtr,fileNode4);
	//Add node 5 into RBT but fail to add in. 
	//Throw similar crc node out from the tree
	//Test 
	Try{
		addFile(&nodePtr,fileNode5);
		TEST_FAIL_MESSAGE("Same CRC");
	}Catch(e){
		TEST_ASSERT_EQUAL_PTR(e->data,fileNode3);
		TEST_ASSERT_EQUAL(e->errCode,ERR_EQUIVALENT_NODE);
	}
	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
	free(fileNode4);
	free(fileNode5);
}