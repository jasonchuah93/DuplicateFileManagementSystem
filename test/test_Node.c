#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "CustomAssertions.h"
#include "Node.h"
#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include <malloc.h>

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
