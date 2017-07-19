#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "JSON.h"
#include "jansson.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "Node.h"
#include "errorNode.h"
#include "compareJSON.h"

void setUp(void){}
void tearDown(void){}

void test_compareFileSize_should_compare_2_files_size_and_return_1(void){
	int compare = 0;
	FileInfo info1 = {.fileSize = 3016};
	FileInfo info2 = {.fileSize = 1016};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	compare = compareFileSize(&node1,node2);
	 
	TEST_ASSERT_EQUAL(1,compare);
	 
	free(node1);
	free(node2);
}

void test_compareFileSize_should_compare_2_files_size_and_return_negative_1(void){
	int compare = 0;
	FileInfo info1 = {.fileSize = 0016};
	FileInfo info2 = {.fileSize = 3016};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	compare = compareFileSize(&node1,node2);
	 
	TEST_ASSERT_EQUAL(-1,compare);
	 
	free(node1);
	free(node2);
}

void test_compareFileSize_should_call_compareFileCRC_and_return_1_if_2_file_size_are_same(void){
	int compare = 0;
	FileInfo info1 = {.fileSize = 3016, .fileCRC32Value = 852147963};
	FileInfo info2 = {.fileSize = 3016, .fileCRC32Value = 352147963};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	compare = compareFileSize(&node1,node2);
	 
	TEST_ASSERT_EQUAL(1,compare);
	 
	free(node1);
	free(node2);
}

void test_compareFileSize_should_call_compareFileCRC_and_return_negative_1_if_2_file_size_are_same(void){
	int compare = 0;
	FileInfo info1 = {.fileSize = 3016, .fileCRC32Value = 654747963};
	FileInfo info2 = {.fileSize = 3016, .fileCRC32Value = 811147963};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	compare = compareFileSize(&node1,node2);
	 
	TEST_ASSERT_EQUAL(-1,compare);
	 
	free(node1);
	free(node2);
}

void test_compareFileSize_should_return_0_if_file_size_and_crc_are_same_in_2_files(void){
	int compare = 0;
	FileInfo info1 = {.fileSize = 3016, .fileCRC32Value = 654747963};
	FileInfo info2 = {.fileSize = 3016, .fileCRC32Value = 654747963};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	compare = compareFileSize(&node1,node2);
	 
	TEST_ASSERT_EQUAL(0,compare);
	 
	free(node1);
	free(node2);
}

void test_compareFileSize_for_2_different_real_files_should_return_negative_1(void){
	int compare = 0;
	FileInfo *info1 = createInfo();
	json_t *folderObj1 = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry1 = getJsonArrayFrmFolderObj(folderObj1);
	getFileInfoFrmJson(fileArry1,info1,1);
	Node *node1 = createNode(info1);
	
	FileInfo *info2 = createInfo();
	json_t *folderObj2 = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry2 = getJsonArrayFrmFolderObj(folderObj2);
	getFileInfoFrmJson(fileArry2,info2,2);
	Node *node2 = createNode(info2);
	
	compare = compareFileSize(&node1,node2);
	 
	TEST_ASSERT_EQUAL(-1,compare);
	 
	free(node1);
	free(node2);
}

void test_compareFileSize_for_2_similar_real_files_should_return_0(void){
	int compare = 0;
	FileInfo *info1 = createInfo();
	json_t *folderObj1 = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry1 = getJsonArrayFrmFolderObj(folderObj1);
	getFileInfoFrmJson(fileArry1,info1,1);
	Node *node1 = createNode(info1);
	
	FileInfo *info2 = createInfo();
	json_t *folderObj2 = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry2 = getJsonArrayFrmFolderObj(folderObj2);
	getFileInfoFrmJson(fileArry2,info2,0);
	Node *node2 = createNode(info2);
	
	compare = compareFileSize(&node1,node2);
	 
	TEST_ASSERT_EQUAL(0,compare);
	 
	free(node1);
	free(node2);
}

void test_compareFileByte_should_compare_2_similar_files_byte_by_byte_and_return_0(void){
	int compare = 0;
	FileInfo info1 = {.fileName = "TestJSON/Testing 2.xlsx"};
	FileInfo info2 = {.fileName = "TestJSON/Testing 3.xlsx"};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	Error *errNode = createErr("Duplicated Node",node1);
	compare = compareFileByte(errNode,node2);
	
	TEST_ASSERT_EQUAL(0,compare);
	
	free(node1);
	free(node2);
	freeErr(errNode);
}

void test_compareFileByte_should_compare_2_different_files_byte_by_byte_and_return_negative_one(void){
	int compare = 0;
	FileInfo info1 = {.fileName = "TestJSON/Testing 2.xlsx"};
	FileInfo info2 = {.fileName = "TestJSON/Testing 8.pdf"};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	Error *errNode = createErr("Not Duplicated Node",node1);
	compare = compareFileByte(errNode,node2);
	
	TEST_ASSERT_EQUAL(-1,compare);
	
	free(node1);
	free(node2);
	freeErr(errNode);
}

void test_compareFileByte_for_2_similar_real_files_should_return_0(void){
	int compare = 0;
	FileInfo *info1 = createInfo();
	json_t *folderObj1 = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry1 = getJsonArrayFrmFolderObj(folderObj1);
	getFileInfoFrmJson(fileArry1,info1,1);
	Node *node1 = createNode(info1);
	
	FileInfo *info2 = createInfo();
	json_t *folderObj2 = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry2 = getJsonArrayFrmFolderObj(folderObj2);
	getFileInfoFrmJson(fileArry2,info2,0);
	Node *node2 = createNode(info2);
	
	Error *errNode = createErr("Duplicated Node",node1);
	compare = compareFileSize(&node1,node2);
	 
	TEST_ASSERT_EQUAL(0,compare);
	 
	free(node1);
	free(node2);
	freeErr(errNode);
}

void test_compareFileByte_for_2_similar_real_files_should_return_negative_1(void){
	int compare = 0;
	FileInfo *info1 = createInfo();
	json_t *folderObj1 = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry1 = getJsonArrayFrmFolderObj(folderObj1);
	getFileInfoFrmJson(fileArry1,info1,0);
	Node *node1 = createNode(info1);
	
	FileInfo *info2 = createInfo();
	json_t *folderObj2 = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry2 = getJsonArrayFrmFolderObj(folderObj2);
	getFileInfoFrmJson(fileArry2,info2,2);
	Node *node2 = createNode(info2);
	
	Error *errNode = createErr("Not Duplicated Node",node1);
	compare = compareFileSize(&node1,node2);
	 
	TEST_ASSERT_EQUAL(-1,compare);
	 
	free(node1);
	free(node2);
	freeErr(errNode);
}