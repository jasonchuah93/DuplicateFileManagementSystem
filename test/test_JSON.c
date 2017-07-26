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
These test will delete JSON file
void test_delJSON_should_delete_JSON_type_file_inside_folder_and_return_1(void){
	int deletedFile = 0;
	deletedFile = delJSON("forTesting/jsonInfo.json");
	TEST_ASSERT_EQUAL(deletedFile,1);
}

void test_delJSON_should_return_0_if_no_JSON_file_type(void){
	int deletedFile = 0;
	deletedFile = delJSON("forTesting/jsonInfo.json");
	TEST_ASSERT_EQUAL(deletedFile,0);
}

void test_delJSON_should_return_0_if_not_JSON_file_type(void){
	int deletedFile = 0;
	deletedFile = delJSON("forTesting/Testing 1.mp3");
	TEST_ASSERT_EQUAL(deletedFile,0);
}
*/
