#include "unity.h"
#include <dirent.h>
#include <malloc.h>
#include "generateCRC32Value.h"
#include "fileInfo.h"
#include "jansson.h"
#include "JSON.h"
#include "Node.h"
#include "compareFileInfo.h"
#include "LinkedList.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "errorNode.h"
#include "CException.h"
#include "fileHandling.h"
#include "CustomAssertions.h"

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
	TEST_ASSERT_EQUAL_STRING("TestJSON/Testing 8.pdf",getNameInErr(errPtr));
	TEST_ASSERT_EQUAL(249159,getSizeInErr(errPtr));
	TEST_ASSERT_EQUAL(289821883,getCRCInErr(errPtr));
	TEST_ASSERT_EQUAL(errPtr->errCode,ERR_EQUIVALENT_NODE);
	TEST_ASSERT_EQUAL_STRING(errPtr->errorMsg,"Try add node inside");
	
	free(errPtr);
	free(nodePtr);
	free(info);
}


