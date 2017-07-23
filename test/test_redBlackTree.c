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
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "LinkedList.h"
#include "CustomAssertions.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_addFileNode_should_add_fileNode_into_empty_root(void){
	Node *nodePtr = NULL;
	FileInfo *info = createInfo();
	LinkedList *list = createLinkedList();
	json_t *folderObj = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry = getJsonArrayFrmFolderObj(folderObj);
	getFileInfoFrmJson(fileArry,info,2);
	Element *ele = createElement(info);
    listAddFirst(ele,list);
	Node *fileNode = createNode(list);
	addFileNode(&nodePtr,fileNode);
	
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode);
	
	free(info);
	free(list);
	free(ele);
	free(fileNode);
}

void test_addFileNode_should_add_n100_into_n200(void){
	Node *nodePtr = NULL;
	FileInfo info1 = {.fileSize = 200};
	FileInfo info2 = {.fileSize = 100};
	LinkedList *list1 = createLinkedList();
	LinkedList *list2 = createLinkedList();
	Element ele1 = {.data = &info1};
	Element ele2 = {.data = &info2};
    listAddFirst(&ele1,list1);
	listAddFirst(&ele2,list2);
	Node *fileNode1 = createNode(list1);
	Node *fileNode2 = createNode(list2);
	
	addFileNode(&nodePtr,fileNode1);
	addFileNode(&nodePtr,fileNode2);
	
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode2,NULL,'b',nodePtr);

	free(list1);
	free(list2);
	free(fileNode1);
	free(fileNode2);
}

void test_addFile_test_3_node_with_same_size(void){
	Node *nodePtr = NULL;
	FileInfo info1 = {.fileSize = 200, .fileCRC32Value = 111111111};
	FileInfo info2 = {.fileSize = 100, .fileCRC32Value = 121111111};
	FileInfo info3 = {.fileSize = 100, .fileCRC32Value = 321111111};
	LinkedList *list1 = createLinkedList();
	LinkedList *list2 = createLinkedList();
	LinkedList *list3 = createLinkedList();
	Element ele1 = {.data = &info1};
	Element ele2 = {.data = &info2};
	Element ele3 = {.data = &info3};
    listAddFirst(&ele1,list1);
	listAddFirst(&ele2,list2);
	listAddFirst(&ele3,list3);
	Node *fileNode1 = createNode(list1);
	Node *fileNode2 = createNode(list2);
	Node *fileNode3 = createNode(list3);
	
	addFileNode(&nodePtr,fileNode1);
	addFileNode(&nodePtr,fileNode2);
	addFileNode(&nodePtr,fileNode3);
	
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode2,NULL,'b',nodePtr);

	free(list1);
	free(list2);
	free(fileNode1);
	free(fileNode2);
}
