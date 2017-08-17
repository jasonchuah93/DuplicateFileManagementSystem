#include "unity.h"
#include <dirent.h>
#include <malloc.h>
#include "fileHandling.h"

/*
#include <unistd.h>
#include <sys/types.h>
#include "jansson.h"
#include "JSON.h"
#include "generateCRC32Value.h"
#include "Node.h"
#include "errorNode.h"
#include "compareJSON.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "LinkedList.h"
#include "RedBlackTree.h"
#include "CException.h"
*/

void setUp(void){}
void tearDown(void){}

void test_createFileForTesting_should_create_a_txt_file_with_random_generator_number(void){
	char *testFile = createFileForTesting("FolderForTesting","TestFileA.txt",50);
	
	TEST_ASSERT_NOT_NULL(testFile);
	TEST_ASSERT_EQUAL_STRING(testFile,"FolderForTesting/TestFileA.txt");
	free(testFile);
}

void test_checkFileNumber_should_list_the_total_number_of_file_in_folder(void){
	TEST_ASSERT_EQUAL(14,checkFileNumberInFolder("forTesting"));
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

/*

void test_traverseFolder_should_scan_through_the_content_of_the_folder(void){
	traverseFolder("forTesting");
}

void test_createJSONFilePath_should_create_a_json_file_path(void){
	char *test = createJSONFilePath("TestJSON");
	TEST_ASSERT_EQUAL_STRING("TestJSON/fileInformation.json",test);
}
*/
/************************************************************
    1st RBT                    2nd RBT
       |                          |
	 Test 8                    Test 88--->Test 8   Test->
     /     \                    /    \
  Test 2 Test 9	             Test 4  Test 99
 *************************************************************/	  
/*
 void xtest_scanFolder_scan_folder_TestJSON(void){
	Node *root = NULL;
	Node *dupRoot = NULL;
	printf("test this\n");
	scanFolder(&root,&dupRoot,"TestJSON");
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(dupRoot);
	TEST_ASSERT_EQUAL_STRING("Testing 8.pdf",getName(root));
	TEST_ASSERT_EQUAL_STRING("Testing 2.xlsx",getName(root->left));
	TEST_ASSERT_EQUAL_STRING("Testing 9.jpg",getName(root->right));
	TEST_ASSERT_EQUAL_STRING("Testing 88.pdf",getNamefromList(dupRoot));
	TEST_ASSERT_EQUAL_STRING("Testing 8.pdf",((FileInfo*)((LinkedList*)((Node*)dupRoot)->data)->head->next->data)->fileName);
	TEST_ASSERT_EQUAL_STRING("Testing 4.xlsx",getNamefromList(dupRoot->left));
	TEST_ASSERT_EQUAL_STRING("Testing 99.jpg",getNamefromList(dupRoot->right));
	
}

void test_scanFolder_scan_folder_forTesting(void){
	Node *root = NULL;
	Node *dupRoot = NULL;
	scanFolder(&root,&dupRoot,"forTesting");
}

void xtest_traverseFolder_with_3_argument_should_traverse_main_folder(void){
	Node *root = NULL;
	Node *dupRoot = NULL;
	_traverseFolder(&root,&dupRoot,"TestJSON");
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(dupRoot);
	TEST_ASSERT_EQUAL_STRING("Testing 8.pdf",getName(root));
	TEST_ASSERT_EQUAL_STRING("Testing 2.xlsx",getName(root->left));
	TEST_ASSERT_EQUAL_STRING("Testing 9.jpg",getName(root->right));
	TEST_ASSERT_EQUAL_STRING("sysmem.c",getName(root->left->left));
	TEST_ASSERT_EQUAL_STRING("Testing 88.pdf",getNamefromList(dupRoot));
	TEST_ASSERT_EQUAL_STRING("Testing 4.xlsx",getNamefromList(dupRoot->left));
	TEST_ASSERT_EQUAL_STRING("Testing 99.jpg",getNamefromList(dupRoot->right));
	TEST_ASSERT_EQUAL_STRING("sysmem2.c",getNamefromList(dupRoot->left->left));
}

void xtest_traverseFolder_with_2_argument_should_traverse_main_folder(void){
	Node *root = NULL;
	Node *dupRoot = NULL;
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
	
void test_duplicateFileForTesting_should_copy_the_content_of_input_file(void){
	char *testFile = createFileForTesting("FolderForTesting/TestFileB.txt",100);
	char *dupFile = duplicateFileForTesting(testFile,"1");
	TEST_ASSERT_NOT_NULL(testFile);
	TEST_ASSERT_NOT_NULL(dupFile);
}

void test_deleteFile_should_throw_error_if_file_to_delete_not_exist(void){
	Error *e = NULL;
	char *fileToDelete = NULL;
	Try{
		deleteFile(fileToDelete);
		TEST_FAIL_MESSAGE("File to delete not exist\n");
	}Catch(e)
		TEST_ASSERT_EQUAL(e,ERR_FILE_NO_EXIST);
}

void test_deleteFile_should_delete_1_file_inside_folder(void){
	char *testFile = createFileForTesting("FolderForTesting/TestFileC.txt",110);
	deleteFile(testFile);
}
*/