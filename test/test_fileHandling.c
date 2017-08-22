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

void setUp(void){}
void tearDown(void){}

void test_summariseFolder_should_summarise_the_folder_and_send_message_if_have_duplicate_file_in_folder(void){
	Node *dupRoot = NULL;
	traverseFolder(&dupRoot,"TestJSON");
	summariseFolder(&dupRoot);
	free(dupRoot);
}

void test_traverseFolder_should_scan_for_duplicate_file_in_two_folder(void){
	Node *root = NULL;
	Node *dupRoot = NULL;
	_traverseFolder(&root,&dupRoot,"TestJSON");
	TEST_ASSERT_NOT_NULL(dupRoot);
	free(root);
	free(dupRoot);
}

void test_scanFolder_should_scan_for_duplicate_file_in_one_folder(void){
	Node *root = NULL;
	Node *dupRoot = NULL;
	scanFolder(&root,&dupRoot,"TestJSON");
	free(root);
	free(dupRoot);
}

void test_deleteFile_should_delete_the_input_file_from_folder(void){
	char *testFile = createFileForTesting("FolderForTesting","TestFileZ.txt",520);
	deleteFile(testFile);
}

void test_duplicateFileForTesting_should_duplicate_file_when_pass_in_the_original_file_pointer(void){
	char *testFile = createFileForTesting("FolderForTesting","TestFileA.txt",50);
	char *duplicateFile = duplicateFileForTesting(testFile,"2");
	
	TEST_ASSERT_NOT_NULL(testFile);
	TEST_ASSERT_NOT_NULL(duplicateFile);
	
	free(testFile);
	free(duplicateFile);
}

void test_duplicateFileForTesting_should_throw_error_if_file_to_duplicate_not_exist(void){
	Error *e = NULL;
	char *fileToDuplicate = NULL;
	Try{
		duplicateFileForTesting(fileToDuplicate,"1");
		TEST_FAIL_MESSAGE("File to duplicate not exist\n");
	}Catch(e)
		TEST_ASSERT_EQUAL(e,ERR_FILE_NOT_OPEN);
}

void test_createFileForTesting_should_create_a_txt_file_with_random_generator_number(void){
	char *testFile = createFileForTesting("FolderForTesting","TestFileA.txt",50);
	TEST_ASSERT_NOT_NULL(testFile);
	TEST_ASSERT_EQUAL_STRING(testFile,"FolderForTesting/TestFileA.txt");
	free(testFile);
}

void test_checkFileNumber_should_list_the_total_number_of_file_in_folder(void){
	TEST_ASSERT_EQUAL(15,checkFileNumberInFolder("forTesting"));
}

void test_getFileEpoch_should_get_the_file_time_in_epoch_format(void){
	TEST_ASSERT_EQUAL(1501433860,getFileEpoch("forTesting/sysmem.c"));
}

void test_convertEpoch_should_convert_the_file_dateTime_to_Epoch_format(void){
	unsigned long int epochSecs = 0;
	char dateTime[100]={0};
	getFileDateTime(dateTime,"forTesting/sysmem.c");
	epochSecs = convertEpoch(dateTime);
	TEST_ASSERT_EQUAL(epochSecs,1501433860);
}

void test_getFileDateTime_should_check_the_latest_modified_time_of_text_file(void){
	char dateTime[100]={0};
	getFileDateTime(dateTime,"forTesting/sysmem.c");
	TEST_ASSERT_EQUAL_STRING(dateTime,"2017/07/31 00:57:40");
}

void test_getFileSize_should_get_the_size_of_image_file(void){
	TEST_ASSERT_EQUAL(1886286,getFileSize("forTesting/Testing 9.jpg"));
}

void test_checkFileSize_should_get_the_size_of_mp3(void){
	TEST_ASSERT_EQUAL(3965661,getFileSize("forTesting/Testing 1.mp3"));
}

