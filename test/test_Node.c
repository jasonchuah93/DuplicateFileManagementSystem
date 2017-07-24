#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "jansson.h"
#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "Node.h"
#include "LinkedList.h"
#include "CustomAssertions.h"

void setUp(void){}
void tearDown(void){}

void test_createNode_should_create_node_to_store_element(void){
    FileInfo *info = createInfo();
	json_t *folderObj = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry = getJsonArrayFrmFolderObj(folderObj);
	getFileInfoFrmJson(fileArry,info,2);
	Element *ele = createElement(info);
	Node *nodePtr = createNode(ele);
	
	TEST_ASSERT_EQUAL_STRING("Testing 8.pdf",getName(nodePtr));
	TEST_ASSERT_EQUAL(249159,getSize(nodePtr));
	TEST_ASSERT_EQUAL(289821883,getCRC(nodePtr));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',nodePtr);
	
	free(info);
	free(ele);
	free(nodePtr);
}
