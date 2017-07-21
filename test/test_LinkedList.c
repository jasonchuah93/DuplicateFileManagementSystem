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

#define getEleName(ele) (((FileInfo*)((Element*)(ele))->data))->fileName
#define getEleSize(ele) (((FileInfo*)((Element*)(ele))->data))->fileSize
#define getEleCRC(ele) (((FileInfo*)((Element*)(ele))->data))->fileCRC32Value

void test_createElement_should_create_element_with_mock_file_infomation(void){
	FileInfo info = {.fileName = "jason.txt",.fileSize = 3016,. fileCRC32Value = 110000};
	Element *ele = createElement(&info);
	TEST_ASSERT_EQUAL_STRING(getEleName(ele),"jason.txt");
	TEST_ASSERT_EQUAL(getEleSize(ele),3016);
	TEST_ASSERT_EQUAL(getEleCRC(ele),110000);
	
	free(ele);
}

void test_createElement_should_create_element_with_real_file_infomation(void){
	FileInfo *info = createInfo();
	json_t *folderObj = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry = getJsonArrayFrmFolderObj(folderObj);
	getFileInfoFrmJson(fileArry,info,1);
	Element *ele = createElement(info);
	
	TEST_ASSERT_EQUAL_STRING(getEleName(ele),"Testing 3.xlsx");
	TEST_ASSERT_EQUAL(getEleSize(ele),10038);
	TEST_ASSERT_EQUAL(getEleCRC(ele),305591788);
	
	free(info);
	free(ele);
}
