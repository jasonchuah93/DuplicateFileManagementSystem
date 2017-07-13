#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "Node.h"
#include "errorNode.h"
#include "compareJSON.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "CException.h"

static char* fileArray[2] = {"TestJSON/Testing 2.xlsx","TestJSON/Testing 3.xlsx"};

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

/*
This test will delete JSON file
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

void test_createJSON_should_able_to_create_JSON_file(void){
	createJSON("TestJSON/fileInfo.json","TestJSON",fileArray,2);
	
}

