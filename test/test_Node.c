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
#include "CustomAssertions.h"

void setUp(void){}
void tearDown(void){}

void test_createNode_should_create_node_with_mock_file_info(void){
    FileInfo info = {.fileName = "jason.txt",.fileSize = 3016,. fileCRC32Value = 110000};
	Node *nodePtr = createNode(&info);
	TEST_ASSERT_EQUAL_STRING(getFileName(nodePtr),"jason.txt");
	TEST_ASSERT_EQUAL(getFileSize(nodePtr),3016);
	TEST_ASSERT_EQUAL(getFileCRC(nodePtr),110000);
}

void test_createNode_should_create_node_with_real_file_info(void){
	FileInfo *info = createInfo();
	json_t *folderObj = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry = getJsonArrayFrmFolderObj(folderObj);
	getFileInfoFrmJson(fileArry,info,1);
	Node *nodePtr = createNode(info);
	TEST_ASSERT_EQUAL_STRING(getFileName(nodePtr),"Testing 3.xlsx");
	TEST_ASSERT_EQUAL(getFileSize(nodePtr),10038);
	TEST_ASSERT_EQUAL(getFileCRC(nodePtr),305591788);
}
