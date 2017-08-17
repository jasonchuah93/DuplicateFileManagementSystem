#include "unity.h"
#include <string.h>
#include <malloc.h>
#include "fileInfo.h"
#include "generateCRC32Value.h"
#include "jansson.h"
#include "JSON.h"
#include "fileHandling.h"
#include "CustomAssertions.h"
#include "Node.h"

void setUp(void){}
void tearDown(void){}

void test_createNode_should_create_empty_node(void){
	void *data = NULL;
	Node *newNode = NULL;
	
	newNode = createNode(data);
	
	TEST_ASSERT_NOT_NULL(newNode);
	TEST_ASSERT_EQUAL(newNode->data,data);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',newNode);
	
	free(newNode);
}

void test_createNode_should_create_a_node_to_store_file_information(void){
    FileInfo *info = initInfo();
	json_t *folderObj = createJsonFolderObject("TestJSON");
	json_t *fileArry = goIntoJsonArrayFrmFolderObj(folderObj);
	getFileInfoFromJsonObject(fileArry,info,3); //3 indicate the index inside the array
	Node *nodePtr = createNode(info);
	
	TEST_ASSERT_EQUAL_STRING("Testing 8.pdf",getNameFromNode(nodePtr));
	TEST_ASSERT_EQUAL(249159,getSizeFromNode(nodePtr));
	TEST_ASSERT_EQUAL(289821883,getCRCFromNode(nodePtr));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',nodePtr);
	
	free(nodePtr);
	free(info);
}
