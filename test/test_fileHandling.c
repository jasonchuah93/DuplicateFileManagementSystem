#include "unity.h"
#include <stdbool.h>
#include "fileHandling.h"

#define TRUE 1
#define FALSE 0

void setUp(void){}
void tearDown(void){}

void test_checkFile_if_the_parameter_is_file(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles/test1.txt"),TRUE);
}

void test_checkFile_if_the_parameter_is_not_file(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles"),FALSE);
}

void test_checkFolder_if_the_parameter_is_folder(void){
	TEST_ASSERT_EQUAL(checkFolder("test/testFiles"),TRUE);
}

void test_checkFolder_if_the_parameter_is_not_folder(void){
	TEST_ASSERT_EQUAL(checkFolder("test/testFiles/test1.txt"),FALSE);
}
