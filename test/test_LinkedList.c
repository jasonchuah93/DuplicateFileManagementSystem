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

void test_createElement_should_create_element_contain_mock_file_infomation(void){
	FileInfo info = {.fileName = "jason.txt", .fileSize = 3016, .fileCRC32Value = 110000};
	
	Element *ele = createElement(&info);
	
	TEST_ASSERT_EQUAL_STRING("jason.txt",getEleName(ele));
	TEST_ASSERT_EQUAL(3016,getEleSize(ele));
	TEST_ASSERT_EQUAL(110000,getEleCRC(ele));
	
	free(ele);
}

void test_createElement_should_create_element_with_real_file_infomation(void){
	FileInfo *info = initInfo();
	json_t *folderObj = createJsonFolderObject("TestJSON");
	json_t *fileArry = goIntoJsonArrayFrmFolderObj(folderObj);
	getFileInfoFromJsonObject(fileArry,info,1);
	Element *ele = createElement(info);
	
	TEST_ASSERT_EQUAL_STRING("Testing 3.xlsx",getEleName(ele));
	TEST_ASSERT_EQUAL(10038,getEleSize(ele));
	TEST_ASSERT_EQUAL(305591788,getEleCRC(ele));
	
	free(ele);
	free(info);
	
}

void test_createLinkedList_should_create_empty_link_list(void){
	LinkedList *list = createLinkedList();
	
	TEST_ASSERT_NOT_NULL(list);
	TEST_ASSERT_NULL(list->head);
	TEST_ASSERT_EQUAL(0,list->length);
	
	free(list);
}

void test_listAddFirst_should_add_element_into_linkedList(void){
	FileInfo *info = initInfo();
	LinkedList *list = createLinkedList();
	json_t *folderObj = createJsonFolderObject("TestJSON");
	json_t *fileArry = goIntoJsonArrayFrmFolderObj(folderObj);
	getFileInfoFromJsonObject(fileArry,info,3);
	Element *ele = createElement(info);
    listAddFirst(ele,list);
	
	TEST_ASSERT_EQUAL_STRING("Testing 8.pdf",getListName(list));
	TEST_ASSERT_EQUAL(249159,getListSize(list));
	TEST_ASSERT_EQUAL(289821883,getListCRC(list));
	
	free(ele);
	free(list);
	free(info);
}

void test_listAddFirst_should_add_2_element_into_linkedList(void){
	FileInfo *info = initInfo();
	FileInfo *info2 = initInfo();
	LinkedList *list = createLinkedList();
	json_t *folderObj = createJsonFolderObject("TestJSON");
	json_t *fileArry = goIntoJsonArrayFrmFolderObj(folderObj);
	getFileInfoFromJsonObject(fileArry,info,0);
	getFileInfoFromJsonObject(fileArry,info2,1);
	Element *ele = createElement(info);
	Element *ele2 = createElement(info2);
	listAddFirst(ele,list);
	listAddFirst(ele2,list);
	
	TEST_ASSERT_EQUAL_STRING("Testing 3.xlsx",getListName(list));
	TEST_ASSERT_EQUAL_STRING("Testing 2.xlsx",((FileInfo*)(list->head->next->data))->fileName );
	TEST_ASSERT_EQUAL_STRING("Testing 2.xlsx",((FileInfo*)(list->tail->data))->fileName );
	TEST_ASSERT_NULL(list->tail->next);
	
	free(ele2);
	free(ele);
	free(list);
	free(info2);
	free(info);
}

void test_listRemoveFirst_should_remove_5_element_from_linkedList(void){
	int len = 0;
	Element *removedEle = NULL;
	FileInfo *info = initInfo();
	FileInfo *info2 = initInfo();
	FileInfo *info3 = initInfo();
	FileInfo *info4 = initInfo();
	FileInfo *info5 = initInfo();
	LinkedList *list = createLinkedList();
	json_t *folderObj = createJsonFolderObject("TestJSON");
	json_t *fileArry = goIntoJsonArrayFrmFolderObj(folderObj);
	getFileInfoFromJsonObject(fileArry,info,0);
	getFileInfoFromJsonObject(fileArry,info2,1);
	getFileInfoFromJsonObject(fileArry,info3,2);
	getFileInfoFromJsonObject(fileArry,info4,3);
	getFileInfoFromJsonObject(fileArry,info5,4);
	Element *ele = createElement(info);
	Element *ele2 = createElement(info2);
	Element *ele3 = createElement(info3);
	Element *ele4 = createElement(info4);
	Element *ele5 = createElement(info5);
	listAddFirst(ele,list);
	listAddFirst(ele2,list);
	listAddFirst(ele3,list);
	listAddFirst(ele4,list);
	listAddFirst(ele5,list);
	for(len = 0; len < list->length; len = len){
		removedEle = listRemoveFirst(list);
		printf("%s\n",((FileInfo*)removedEle->data)->fileName);
		
	}
	
	TEST_ASSERT_NULL(list->head);
	TEST_ASSERT_EQUAL(0,list->length);
	
	free(ele5);
	free(ele4);
	free(ele3);
	free(ele2);
	free(ele);
	free(list);
	free(info5);
	free(info4);
	free(info3);
	free(info2);
	free(info);
	
}
