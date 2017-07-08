#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "CustomAssertions.h"
#include "Node.h"
#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"

void setUp(void){}
void tearDown(void){}

void test_createNode_should_store_size_and_crc_of_file_into_node(void){
    Node *nodePtr = NULL;
	unsigned long long int size = 50;
	unsigned long long int crc = 123123456789;
	json_t *fileObjectSize = json_integer(size);
	json_t *fileObjectCRC = json_integer(crc);
	
	nodePtr = createNode(fileObjectSize,fileObjectCRC);
	
	TEST_ASSERT_NOT_NULL(nodePtr);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',nodePtr);
	TEST_ASSERT_EQUAL(nodePtr->fileSize,size);
	TEST_ASSERT_EQUAL(nodePtr->crc32Value,crc);
	
	free(nodePtr);
}

void test_createNodeWithFileInfo_should_store_size_and_crc_and_pathName_of_file_into_node(void){
    Node *nodePtr = NULL;
	unsigned long long int size = 50;
	unsigned long long int crc = 123123456789;
	char *pathName = "forTesting/testPicture2.jpg";
	json_t *fileObjectName = json_string(pathName);
	json_t *fileObjectSize = json_integer(size);
	json_t *fileObjectCRC = json_integer(crc);
	
	nodePtr = createNodeWithFileInfo(fileObjectName,fileObjectSize,fileObjectCRC);
	
	TEST_ASSERT_NOT_NULL(nodePtr);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',nodePtr);
	TEST_ASSERT_EQUAL_STRING(nodePtr->pathName,pathName);
	TEST_ASSERT_EQUAL(nodePtr->fileSize,size);
	TEST_ASSERT_EQUAL(nodePtr->crc32Value,crc);
	
	free(nodePtr);
}

