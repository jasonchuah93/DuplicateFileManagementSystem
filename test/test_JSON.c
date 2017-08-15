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
#include "errorNode.h"
#include "compareJSON.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "LinkedList.h"
#include "main.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_checkJSON_should_return_1_if_the_file_type_is_json(void){
	int check = 0;
	check = checkJSON("forTesting/J.json");
	TEST_ASSERT_EQUAL(check,1);
}

void test_checkJSON_should_return_0_if_the_file_type_is_not_json(void){
	int check = 0;
	check = checkJSON("forTesting/test p.point.pptx");
	TEST_ASSERT_EQUAL(check,0);
}

void test_getJsonArrayFrmFolderObj_should_throw_error_if_input_is_not_an_json_object(void){
	Error *e = NULL;
	json_t *folderObj = json_array();
	
	Try{
		getJsonArrayFrmFolderObj(folderObj);
		TEST_FAIL_MESSAGE("Expected ERR_NOT_JSON_OBJECT to be thrown.");
	}Catch(e){
		TEST_ASSERT_EQUAL(e,ERR_NOT_JSON_OBJECT);
	}	
}

void test_getFileInfoFrmJson_should_throw_error_if_input_is_not_an_array(void){
	FileInfo *info = NULL;
	Error *e = NULL;
	json_t *fileArray = json_object();
	Try{
		getFileInfoFrmJson(fileArray,info,0);
		TEST_FAIL_MESSAGE("Expected ERR_NOT_JSON_ARRAY to be thrown.");
	}Catch(e){
		TEST_ASSERT_EQUAL(e,ERR_NOT_JSON_ARRAY);
	}	
}

void test_getFileInfoFrmJson_should_get_Testing_8_info_from_json_array(void){
	FileInfo *info = createInfo();
	json_t *folderObj = createJsonObjectFrmFolder("TestJSON");
	json_t *fileArry = getJsonArrayFrmFolderObj(folderObj);
	getFileInfoFrmJson(fileArry,info,3);
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL_STRING(info->fileName,"Testing 8.pdf");
	TEST_ASSERT_EQUAL(info->fileSize,249159);
	TEST_ASSERT_EQUAL(info->fileCRC32Value,289821883);
	
}

void test_checkJsonFile_should_return_0_if_folder_contain_json_file(void){
	int check = 1;
	check = checkJsonFile("forTesting","fileInformation.json");
	TEST_ASSERT_EQUAL(0,check);
}
/*
void test_checkFileLaterThanJson_should_return_0_if_json_file_is_latest_inside_folder(void){
	int check = 1;
	check = checkFileLaterThanJson("TestJSON","fileInformation.json");
	TEST_ASSERT_EQUAL(0,check);
}

void test_checkFileLaterThanJson_should_return_1_if_json_file_is_not_latest_inside_folder(void){
	int check = 0;
	check = checkFileLaterThanJson("forTesting/test folder","fileInformation.json");
	TEST_ASSERT_EQUAL(1,check);
}
*/
void test_load_existing_json_file_to_read_the_object_inside(void){
	json_t *folderObj = NULL;
	json_t *fileArray = NULL;
	size_t arraySize = 0;
	json_error_t jError;
	folderObj = json_load_file("TestJSON/fileInformation.json",0,&jError);
	
	if(json_is_object(folderObj)){
		fileArray = getJsonArrayFrmFolderObj(folderObj);
		arraySize = json_array_size(fileArray);
		//printf("array size:%d\n",arraySize);
	}
}

void test_updateJson_should_check_file_date_time_compare_to_json_file(void){
	Node *dupRoot = NULL;
	//char *testFile1 = createFileForTesting("FolderForTesting/TestFileP.txt",5000);
	//duplicateFileForTesting(testFile1,"5");
	traverseFolder(&dupRoot,"FolderForTesting");
	summariseFolder(&dupRoot);
	
	//TEST_ASSERT_NOT_NULL(removedEle);
	//TEST_ASSERT_NOT_NULL(removedNode);
}

/*
void test_updateJson_should_check_file_number_compare_to_json_file_array_size(void){
	json_t *obj = NULL;
	Node *dupRoot = NULL;
	
	//traverseFolder(&dupRoot,"FolderForTesting");
	//obj = updateJson("FolderForTesting","fileInformation.json");
	//TEST_ASSERT_NOT_NULL(obj);
}


These test will delete JSON file
void test_delJSON_should_delete_JSON_type_file_inside_folder_and_return_1(void){
	int deletedFile = 0;
	deletedFile = delJSONFile("forTesting/jsonInfo.json");
	TEST_ASSERT_EQUAL(deletedFile,1);
}

void test_delJSON_should_return_0_if_no_JSON_file_type(void){
	int deletedFile = 0;
	deletedFile = delJSONFile("forTesting/jsonInfo.json");
	TEST_ASSERT_EQUAL(deletedFile,0);
}

void test_delJSON_should_return_0_if_not_JSON_file_type(void){
	int deletedFile = 0;
	deletedFile = delJSONFile("forTesting/Testing 1.mp3");
	TEST_ASSERT_EQUAL(deletedFile,0);
}
*/
