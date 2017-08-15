#include "unity.h"
#include <string.h>
#include <malloc.h>
#include "fileInfo.h"

void setUp(void){}
void tearDown(void){}

void test_initFileInfo_should_initialize_the_file_information(void){
	FileInfo *info = NULL;
	
	info = initInfo();
	
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(info->fileName,NULL);
	TEST_ASSERT_EQUAL(info->fileSize,0);
	TEST_ASSERT_EQUAL(info->fileCRC32Value,0);
	
	free(info);
}