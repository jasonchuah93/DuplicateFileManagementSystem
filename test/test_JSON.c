#include "unity.h"
#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"


void setUp(void){}

void tearDown(void){}

void test_checkJSON_should_return_1_if_the_file_type_is_json(void){
	int check = 0;
	check = checkJSON("forTesting/JSONTest1.json");
	TEST_ASSERT_EQUAL(check,1);
}

void test_checkJSON_should_return_0_if_the_file_type_is_not_json(void){
	int check = 0;
	check = checkJSON("forTesting/test p.point.pptx");
	TEST_ASSERT_EQUAL(check,0);
}

void test_createJSON_should_create_file_in_JSON_format(void){
	//createJSON("forTesting/jsonINFO.json","forTesting/testPicture.jpg",fptr,1);
}