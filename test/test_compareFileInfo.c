#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "Node.h"
#include "errorNode.h"
#include "LinkedList.h"
#include "fileInfo.h"
#include "compareFileInfo.h"

void setUp(void){}
void tearDown(void){}

void test_compareList_should_compare_2_element_size_from_linkedlist_and_return_1(void){
	int compare = 0;
	FileInfo info1 = {.fileSize = 3016};
	FileInfo info2 = {.fileSize = 1016};
	Element *ele1 = createElement(&info1);
	Element *ele2 = createElement(&info2);
	LinkedList *list1 = createLinkedList();
	LinkedList *list2 = createLinkedList();
	listAddFirst(ele1,list1);
	listAddFirst(ele2,list2);
	Node *node1 = createNode(list1);
	Node *node2 = createNode(list2);
	
	compare = compareList(&node1,node2);
	TEST_ASSERT_EQUAL(1,compare);
	
	free(node1);
	free(node2);	
	free(list1);
	free(list2);
	free(ele1);
	free(ele2);
}

void test_compareList_should_compare_2_element_size_from_linkedlist_return_negative_1(void){
	int compare = 0;
	FileInfo info1 = {.fileSize = 3016};
	FileInfo info2 = {.fileSize = 9016};
	Element *ele1 = createElement(&info1);
	Element *ele2 = createElement(&info2);
	LinkedList *list1 = createLinkedList();
	LinkedList *list2 = createLinkedList();
	listAddFirst(ele1,list1);
	listAddFirst(ele2,list2);
	Node *node1 = createNode(list1);
	Node *node2 = createNode(list2);
	
	compare = compareList(&node1,node2);
	 
	TEST_ASSERT_EQUAL(-1,compare);
	 
	free(node1);
	free(node2);	
	free(list1);
	free(list2);
	free(ele1);
	free(ele2);
}

void test_compareFileSize_should_compare_2_info_size_and_return_1(void){
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

void test_compareFileSize_should_compare_2_info_size_and_return_negative_1(void){
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

void test_ompareFileCRC_should_compare_2_info_crc_and_return_1(void){
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

void test_compareFileCRC_should_compare_2_info_crc_and_return_negative_1(void){
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

void test_compareFileCRC_should_compare_2_info_crc_and_return_0(void){
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

void test_compareFileByte_should_compare_2_info_byte_by_byte_and_return_1_if_both_info_are_the_same(void){
	int compare = 0;
	char *folderName = "TestJSON";
	char fullFilePath1[100] = {0}, fullFilePath2[100] = {0}; 
	FileInfo info1 = {.fileName = "Testing 2.xlsx"};
	FileInfo info2 = {.fileName = "Testing 3.xlsx"};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	Error *errNode = createErr("Duplicated Node",node1);
	sprintf(fullFilePath1,"%s/%s",folderName,getNameInErr(errNode));
	sprintf(fullFilePath2,"%s/%s",folderName,getNameFromNode(node2));
	
	compare = compareFileByte(fullFilePath1,fullFilePath2);
	
	TEST_ASSERT_EQUAL(1,compare);
	
	freeErr(errNode);
	free(node1);
	free(node2);
}

void test_compareFileByte_should_compare_2_different_files_byte_by_byte_and_return_negative_one(void){
	int compare = 0;
	char *folderName = "TestJSON";
	char fullFilePath1[100] = {0}, fullFilePath2[100] = {0}; 
	FileInfo info1 = {.fileName = "Testing 3.xlsx"};
	FileInfo info2 = {.fileName = "Testing 8.pdf"};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	Error *errNode = createErr("Not Duplicated Node",node1);
	sprintf(fullFilePath1,"%s/%s",folderName,getNameInErr(errNode));
	sprintf(fullFilePath2,"%s/%s",folderName,getNameFromNode(node2));
	
	compare = compareFileByte(fullFilePath1,fullFilePath2);
	
	TEST_ASSERT_EQUAL(-1,compare);
	
	freeErr(errNode);
	free(node1);
	free(node2);
	
}

void test_compareFileByte_should_compare_image_and_song_files_byte_by_byte_and_return_negative_one(void){
	int compare = 0;
	char *folderName = "forTesting";
	char fullFilePath1[100] = {0}, fullFilePath2[100] = {0}; 
	FileInfo info1 = {.fileName = "Testing 10.jpg"};
	FileInfo info2 = {.fileName = "Testing 1.mp3"};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	Error *errNode = createErr("Not Duplicated Node",node1);
	sprintf(fullFilePath1,"%s/%s",folderName,getNameInErr(errNode));
	sprintf(fullFilePath2,"%s/%s",folderName,getNameFromNode(node2));
	
	compare = compareFileByte(fullFilePath1,fullFilePath2);
	
	TEST_ASSERT_EQUAL(-1,compare);
	
	freeErr(errNode);
	free(node1);
	free(node2);
}

void test_compareFileByte_should_compare_words_and_powerpoint_files_byte_by_byte_and_return_negative_one(void){
	int compare = 0;
	char *folderName = "forTesting";
	char fullFilePath1[100] = {0}, fullFilePath2[100] = {0}; 
	FileInfo info1 = {.fileName = "Testing 4.docx"};
	FileInfo info2 = {.fileName = "Testing 10.jpg"};
	Node *node1 = createNode(&info1);
	Node *node2 = createNode(&info2);
	Error *errNode = createErr("Not Duplicated Node",node1);
	sprintf(fullFilePath1,"%s/%s",folderName,getNameInErr(errNode));
	sprintf(fullFilePath2,"%s/%s",folderName,getNameFromNode(node2));
	
	compare = compareFileByte(fullFilePath1,fullFilePath2);
	
	TEST_ASSERT_EQUAL(-1,compare);
	
	freeErr(errNode);
	free(node1);
	free(node2);
}
