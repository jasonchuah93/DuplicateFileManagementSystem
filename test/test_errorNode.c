#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "fileInfo.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "Node.h"
#include "jansson.h"
#include "JSON.h"
#include "errorNode.h"

void setUp(void){}
void tearDown(void){}

void test_createErr_should_create_errorPtr_store_nodePtr(void){
	FileInfo *info = initInfo();
	json_t *folderObj = createJsonFolderObject("TestJSON");
	json_t *fileArry = goIntoJsonArrayFrmFolderObj(folderObj);
	getFileInfoFromJsonObject(fileArry,info,3);
	Node *nodePtr = createNode(info);
	Error *errPtr = createErr("Try add node inside",nodePtr);
	
	TEST_ASSERT_EQUAL(nodePtr,errPtr->data);
	TEST_ASSERT_EQUAL_STRING("Testing 8.pdf",getNameInErr(errPtr));
	TEST_ASSERT_EQUAL(249159,getSizeInErr(errPtr));
	TEST_ASSERT_EQUAL(289821883,getCRCInErr(errPtr));
	TEST_ASSERT_EQUAL(errPtr->errCode,ERR_EQUIVALENT_NODE);
	TEST_ASSERT_EQUAL_STRING(errPtr->errorMsg,"Try add node inside");
	
	free(errPtr);
	free(nodePtr);
	free(info);
}


