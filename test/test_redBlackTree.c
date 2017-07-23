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
	Error *e = NULL;
	Node *nodePtr = NULL;
	FileInfo *info = createInfo();
	LinkedList *list = createLinkedList();
	json_t *folderObj = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry = getJsonArrayFrmFolderObj(folderObj);
	getFileInfoFrmJson(fileArry,info,2);
	Element *ele = createElement(info);
    listAddFirst(ele,list);
	Node *fileNode = createNode(list);
	Try{
		addFileNode(&nodePtr,fileNode);
	}Catch(e){
		TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode);
	}
	
	free(info);
	free(list);
	free(ele);
	free(fileNode);
}

void test_addFileNode_should_add_n100_into_n200(void){
	Error *e = NULL;
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
	
	Try{
		addFileNode(&nodePtr,fileNode1);
		addFileNode(&nodePtr,fileNode2);
	}Catch(e){
		TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
		TEST_ASSERT_EQUAL_NODE(fileNode2,NULL,'b',nodePtr);
	}
	free(list1);
	free(list2);
	free(fileNode1);
	free(fileNode2);
}

void test_addFile_test_3_node_with_same_size_but_different_crc(void){
	int i = 0;
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
	
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode3);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode1,'b',fileNode3);

	free(list1);
	free(list2);
	free(list3);
	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
}

void test_addFile_test_5_node_with_same_size_but_different_crc(void){
	Node *nodePtr = NULL;
	FileInfo info1 = {.fileSize = 200, .fileCRC32Value = 111111111};
	FileInfo info2 = {.fileSize = 100, .fileCRC32Value = 121111111};
	FileInfo info3 = {.fileSize = 100, .fileCRC32Value = 321111111};
	FileInfo info4 = {.fileSize = 1000, .fileCRC32Value = 532111111};
	FileInfo info5 = {.fileSize = 22200, .fileCRC32Value = 1321111111};
	
	LinkedList *list1 = createLinkedList();
	LinkedList *list2 = createLinkedList();
	LinkedList *list3 = createLinkedList();
	LinkedList *list4 = createLinkedList();
	LinkedList *list5 = createLinkedList();
	Element ele1 = {.data = &info1};
	Element ele2 = {.data = &info2};
	Element ele3 = {.data = &info3};
	Element ele4 = {.data = &info4};
	Element ele5 = {.data = &info5};
    listAddFirst(&ele1,list1);
	listAddFirst(&ele2,list2);
	listAddFirst(&ele3,list3);
	listAddFirst(&ele4,list4);
	listAddFirst(&ele5,list5);
	Node *fileNode1 = createNode(list1);
	Node *fileNode2 = createNode(list2);
	Node *fileNode3 = createNode(list3);
	Node *fileNode4 = createNode(list4);
	Node *fileNode5 = createNode(list5);
	
	addFileNode(&nodePtr,fileNode1);
	addFileNode(&nodePtr,fileNode2);
	addFileNode(&nodePtr,fileNode3);
	addFileNode(&nodePtr,fileNode4);
	addFileNode(&nodePtr,fileNode5);
	
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode4);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode5);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode1,'r',fileNode3);
	TEST_ASSERT_EQUAL_NODE(fileNode3,fileNode5,'b',fileNode4);

	free(list1);
	free(list2);
	free(list3);
	free(list4);
	free(list5);
	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
	free(fileNode4);
	free(fileNode5);
}

void test_addFile_test_4_node_with_same_size_and_same_crc(void){
	Error *e = NULL;
	Node *nodePtr = NULL;
	FileInfo info1 = {.fileSize = 200, .fileCRC32Value = 111111111};
	FileInfo info2 = {.fileSize = 100, .fileCRC32Value = 121111111};
	FileInfo info3 = {.fileSize = 100, .fileCRC32Value = 321111111};
	FileInfo info4 = {.fileSize = 100, .fileCRC32Value = 121111111};
	LinkedList *list1 = createLinkedList();
	LinkedList *list2 = createLinkedList();
	LinkedList *list3 = createLinkedList();
	LinkedList *list4 = createLinkedList();
	Element ele1 = {.data = &info1};
	Element ele2 = {.data = &info2};
	Element ele3 = {.data = &info3};
	Element ele4 = {.data = &info4};
    listAddFirst(&ele1,list1);
	listAddFirst(&ele2,list2);
	listAddFirst(&ele3,list3);
	listAddFirst(&ele4,list4);
	Node *fileNode1 = createNode(list1);
	Node *fileNode2 = createNode(list2);
	Node *fileNode3 = createNode(list3);
	Node *fileNode4 = createNode(list4);
	
	addFileNode(&nodePtr,fileNode1);
	addFileNode(&nodePtr,fileNode2);
	addFileNode(&nodePtr,fileNode3);
	Try{
		addFileNode(&nodePtr,fileNode4);
		TEST_FAIL_MESSAGE("Same Size, same CRC");
	}Catch(e){
		TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode3);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode4);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode2);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode1);
		TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode1,'r',nodePtr);
		TEST_ASSERT_EQUAL_PTR(e->data,fileNode2);
		TEST_ASSERT_EQUAL(e->errCode,ERR_EQUIVALENT_NODE);
	}
	free(list1);
	free(list2);
	free(list3);
	free(list4);
	free(fileNode1);
	free(fileNode2);
	free(fileNode3);
	free(fileNode4);
}
