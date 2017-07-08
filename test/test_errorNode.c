#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "errorNode.h"
#include "Node.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_createErrNode_should_store_fileNode(void){
	Node *nodePtr = NULL;
	Error *errPtr = NULL;
	unsigned long long int size = 50;
	unsigned long long int crc = 123123456789;
	char *pathName = "forTesting/testPicture2.jpg";
	json_t *fileObjectName = json_string(pathName);
	json_t *fileObjectSize = json_integer(size);
	json_t *fileObjectCRC = json_integer(crc);
	
	nodePtr = createNodeWithFileInfo(fileObjectName,fileObjectSize,fileObjectCRC);
	errPtr = createErr(nodePtr);

	TEST_ASSERT_NOT_NULL(errPtr);
	TEST_ASSERT_EQUAL(errPtr->data,nodePtr);
	
	free(nodePtr);
	free(errPtr);
}

void test_createErrNode_should_throw_err(void){
	Node *nodePtr = NULL;
	Error *e;
	unsigned long long int size = 50;
	unsigned long long int crc = 123123456789;
	char *pathName = "forTesting/testPicture2.jpg";
	json_t *fileObjectName = json_string(pathName);
	json_t *fileObjectSize = json_integer(size);
	json_t *fileObjectCRC = json_integer(crc);
	
	nodePtr = createNodeWithFileInfo(fileObjectName,fileObjectSize,fileObjectCRC);
	Try{
		e = createErr(nodePtr);	
		Throw(e);
	}Catch(e){
		TEST_ASSERT_NOT_NULL(e);
		TEST_ASSERT_EQUAL_PTR(e->data,nodePtr);
		free(nodePtr);
		freeErr(e);
	}
}
