#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "jansson.h"
#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "Node.h"
#include "errorNode.h"
#include "LinkedList.h"
#include "CustomAssertions.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_createErr_should_create_errorPtr_store_nodePtr(void){
	FileInfo *info = createInfo();
	json_t *folderObj = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry = getJsonArrayFrmFolderObj(folderObj);
	getFileInfoFrmJson(fileArry,info,3);
	Node *nodePtr = createNode(info);
	Error *errPtr = createErr("Try add node inside",nodePtr);
	
	TEST_ASSERT_EQUAL(nodePtr,errPtr->data);
	TEST_ASSERT_EQUAL_STRING("Testing 8.pdf",getNameInErr(errPtr));
	TEST_ASSERT_EQUAL(249159,getSizeInErr(errPtr));
	TEST_ASSERT_EQUAL(289821883,getCRCInErr(errPtr));
}


