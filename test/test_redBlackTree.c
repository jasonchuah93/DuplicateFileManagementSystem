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

void test_removeFileNode_should_remove_all_fileNode_from_RBT(void){
	Error *e = NULL;
	Node *nodePtr = NULL;
	Node *removeNode = NULL;
	FileInfo *info = initInfo();
	FileInfo info1 = {.fileSize = 200};
	FileInfo info2 = {.fileSize = 100};
	FileInfo info3 = {.fileSize = 300};
	FileInfo info4 = {.fileSize = 50};
	FileInfo info5 = {.fileSize = 10};
	Node *fileNode1 = createNode(&info1);
	Node *fileNode2 = createNode(&info2);
	Node *fileNode3 = createNode(&info3);
	Node *fileNode4 = createNode(&info4);
	Node *fileNode5 = createNode(&info5);
	addFileNode(&nodePtr,fileNode1);
	addFileNode(&nodePtr,fileNode2);
	addFileNode(&nodePtr,fileNode3);
	addFileNode(&nodePtr,fileNode4);
	addFileNode(&nodePtr,fileNode5);
	while(nodePtr!=NULL){
		removeNode = removeFileNode(&nodePtr,nodePtr);
		printf("node: %d\n",getSizeFromNode(removeNode));
	}
	
	TEST_ASSERT_EQUAL(nodePtr,NULL);
	
	free(fileNode5);
	free(fileNode4);
	free(fileNode3);
	free(fileNode2);
	free(fileNode1);
}

void test_removeFileNode_should_remove_fileNode_from_RBT(void){
	Error *e = NULL;
	Node *nodePtr = NULL;
	FileInfo *info = initInfo();
	FileInfo info1 = {.fileSize = 200};
	FileInfo info2 = {.fileSize = 100};
	Node *fileNode1 = createNode(&info1);
	Node *fileNode2 = createNode(&info2);
	addFileNode(&nodePtr,fileNode1);
	addFileNode(&nodePtr,fileNode2);
	
	Node *removeNode = removeFileNode(&nodePtr,nodePtr);
	
	TEST_ASSERT_EQUAL(nodePtr,fileNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode2);
	
	free(fileNode2);
	free(fileNode1);
}

void test_addFileNode_should_add_fileNode_into_empty_root(void){
	Error *e = NULL;
	Node *nodePtr = NULL;
	FileInfo *info = initInfo();
	json_t *folderObj = createJsonFolderObject("TestJSON");
	json_t *fileArry = goIntoJsonArrayFrmFolderObj(folderObj);
	getFileInfoFromJsonObject(fileArry,info,2);
	Node *fileNode = createNode(info);
	Try{
		addFileNode(&nodePtr,fileNode);
	}Catch(e){
		TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode);
	}
	
	free(fileNode);
	free(info);
}

void test_addFileNode_should_add_n100_into_n200(void){
	Error *e = NULL;
	Node *nodePtr = NULL;
	FileInfo info1 = {.fileSize = 200};
	FileInfo info2 = {.fileSize = 100};
	Node *fileNode1 = createNode(&info1);
	Node *fileNode2 = createNode(&info2);
	
	Try{
		addFileNode(&nodePtr,fileNode1);
		addFileNode(&nodePtr,fileNode2);
	}Catch(e){
		TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
		TEST_ASSERT_EQUAL_NODE(fileNode2,NULL,'b',nodePtr);
	}
	
	free(fileNode2);
	free(fileNode1);
}

void test_addFile_test_3_node_with_same_size_but_different_crc(void){
	int i = 0;
	Node *nodePtr = NULL;
	FileInfo info1 = {.fileSize = 200, .fileCRC32Value = 111111111};
	FileInfo info2 = {.fileSize = 100, .fileCRC32Value = 121111111};
	FileInfo info3 = {.fileSize = 100, .fileCRC32Value = 321111111};
	Node *fileNode1 = createNode(&info1);
	Node *fileNode2 = createNode(&info2);
	Node *fileNode3 = createNode(&info3);
	
	addFileNode(&nodePtr,fileNode1);
	addFileNode(&nodePtr,fileNode2);
	addFileNode(&nodePtr,fileNode3);
	
	TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode3);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
	TEST_ASSERT_EQUAL_NODE(fileNode2,fileNode1,'b',fileNode3);

	free(fileNode3);
	free(fileNode2);
	free(fileNode1);
}

void test_addFile_test_5_node_with_same_size_but_different_crc(void){
	Node *nodePtr = NULL;
	FileInfo info1 = {.fileSize = 200, .fileCRC32Value = 111111111};
	FileInfo info2 = {.fileSize = 100, .fileCRC32Value = 121111111};
	FileInfo info3 = {.fileSize = 100, .fileCRC32Value = 321111111};
	FileInfo info4 = {.fileSize = 1000, .fileCRC32Value = 532111111};
	FileInfo info5 = {.fileSize = 22200, .fileCRC32Value = 1321111111};
	Node *fileNode1 = createNode(&info1);
	Node *fileNode2 = createNode(&info2);
	Node *fileNode3 = createNode(&info3);
	Node *fileNode4 = createNode(&info4);
	Node *fileNode5 = createNode(&info5);
	
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

	free(fileNode5);
	free(fileNode4);
	free(fileNode3);
	free(fileNode2);
	free(fileNode1);
}

void test_addFile_test_2_node_with_same_size_and_same_crc(void){
	Error *e = NULL;
	Node *nodePtr = NULL;
	FileInfo info1 = {.fileSize = 200, .fileCRC32Value = 111111111};
	FileInfo info2 = {.fileSize = 200, .fileCRC32Value = 111111111};
	Node *fileNode1 = createNode(&info1);
	Node *fileNode2 = createNode(&info2);
	Try{
		addFileNode(&nodePtr,fileNode1);
		addFileNode(&nodePtr,fileNode2);
		TEST_FAIL_MESSAGE("Same Size, same CRC");
	}Catch(e){
		TEST_ASSERT_EQUAL_PTR(nodePtr,fileNode1);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',fileNode2);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',fileNode1);
		TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',nodePtr);
		TEST_ASSERT_EQUAL_PTR(e->data,fileNode1);
		TEST_ASSERT_EQUAL(e->errCode,ERR_EQUIVALENT_NODE);
	}
	free(fileNode2);
	free(fileNode1);
}

void test_addFile_test_4_node_with_same_size_and_same_crc(void){
	Error *e = NULL;
	Node *nodePtr = NULL;
	FileInfo info1 = {.fileSize = 200, .fileCRC32Value = 111111111};
	FileInfo info2 = {.fileSize = 100, .fileCRC32Value = 121111111};
	FileInfo info3 = {.fileSize = 100, .fileCRC32Value = 321111111};
	FileInfo info4 = {.fileSize = 100, .fileCRC32Value = 121111111};
	Node *fileNode1 = createNode(&info1);
	Node *fileNode2 = createNode(&info2);
	Node *fileNode3 = createNode(&info3);
	Node *fileNode4 = createNode(&info4);
	
	Try{
		addFileNode(&nodePtr,fileNode1);
		addFileNode(&nodePtr,fileNode2);
		addFileNode(&nodePtr,fileNode3);
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
	
	free(fileNode4);
	free(fileNode3);
	free(fileNode2);
	free(fileNode1);
}

void test_addFileNodeForList_should_add_node_into_RBT(void){
	Node *testRoot = NULL;
	FileInfo info1 = {.fileSize = 100, .fileCRC32Value = 111111111};
	FileInfo info2 = {.fileSize = 200, .fileCRC32Value = 121111111};
	FileInfo info3 = {.fileSize = 300, .fileCRC32Value = 121111111};
	FileInfo info4 = {.fileSize = 100, .fileCRC32Value = 111111111};
	FileInfo info5 = {.fileSize = 200, .fileCRC32Value = 121111111};
	FileInfo info6 = {.fileSize = 300, .fileCRC32Value = 121111111};
	Element *ele1 = createElement(&info1);
	Element *ele2 = createElement(&info2);
	Element *ele3 = createElement(&info3);
	Element *ele4 = createElement(&info4);
	Element *ele5 = createElement(&info5);
	Element *ele6 = createElement(&info6);
	LinkedList *list1 = createLinkedList();
	LinkedList *list2 = createLinkedList();
	LinkedList *list3 = createLinkedList();
	listAddFirst(ele1,list1);
	listAddFirst(ele2,list2);
	listAddFirst(ele3,list3);
	listAddFirst(ele4,list1);
	listAddFirst(ele5,list2);
	listAddFirst(ele6,list3);
	Node *node1 = createNode(list1);
	Node *node2 = createNode(list2);
	Node *node3 = createNode(list3);
	addListNode(&testRoot,node1);
	addListNode(&testRoot,node2);
	addListNode(&testRoot,node3);
	
	TEST_ASSERT_EQUAL_PTR(node2,testRoot);
	TEST_ASSERT_EQUAL_NODE(node1,node3,'b',testRoot);
	
	free(node3);
	free(node2);
	free(node1);
	free(list3);
	free(list2);
	free(list1);
	free(ele6);
	free(ele5);
	free(ele4);
	free(ele3);
	free(ele2);
	free(ele1);
}
