#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "Node.h"
#include "errorNode.h"
#include "Rotation.h"
#include "compareJSON.h"
#include "RedBlackTree.h"
#include "RestructureNode.h"
#include "CustomAssertions.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_createErr_should_store_fileNode(void){
	Node *nodePtr = NULL;
	Error *errPtr = NULL;
	unsigned long long int size = 50;
	unsigned long int crc = 1231234567;
	char *pathName = "forTesting/testPicture2.jpg";
	json_t *fileObjectName = json_string(pathName);
	json_t *fileObjectSize = json_integer(size);
	json_t *fileObjectCRC = json_integer(crc);
	
	nodePtr = createNodeWithFileInfo(fileObjectName,fileObjectSize,fileObjectCRC);
	errPtr = createErr("Encounter Duplicate Node",nodePtr);

	TEST_ASSERT_NOT_NULL(errPtr);
	TEST_ASSERT_EQUAL_PTR(errPtr->data,nodePtr);
	TEST_ASSERT_EQUAL(errPtr->errorMsg,"Encounter Duplicate Node");
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',errPtr->data);
	
	free(nodePtr);
	free(errPtr);
}

void test_createErr_should_throw_err(void){
	Node *nodePtr = NULL;
	Error *e = NULL;
	unsigned long long int size = 50;
	unsigned long int crc = 1231234567;
	char *pathName = "forTesting/testPicture2.jpg";
	json_t *fileObjectName = json_string(pathName);
	json_t *fileObjectSize = json_integer(size);
	json_t *fileObjectCRC = json_integer(crc);
	
	nodePtr = createNodeWithFileInfo(fileObjectName,fileObjectSize,fileObjectCRC);
	e = createErr("Try to throw to error",nodePtr);
	Try{
		Throw(e);
	}Catch(e){
		TEST_ASSERT_NOT_NULL(e);
		TEST_ASSERT_EQUAL_PTR(e->data,nodePtr);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',nodePtr);
		free(nodePtr);
		freeErr(e);
	}
}

