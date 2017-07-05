#include "unity.h"
#include "compareJSON.h"
#include "Node.h"

void setUp(void){}
void tearDown(void){}

void test_compareFileSize_should_compare_2_files_size_and_return_1(void){
	Node *rootNodePtr = NULL,*targetNodePtr = NULL;
	int compare = 0;
	unsigned long long int size1 = 5555555555;
	unsigned long long int size2 = 3333333333;
	unsigned long int crc1 = 1231234567;
	unsigned long int crc2 = 2331234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	
	rootNodePtr = createNode(fileObjectSize1,fileObjectCRC1);
	targetNodePtr = createNode(fileObjectSize2,fileObjectCRC2);
	
	compare = compareFileSize(&rootNodePtr,targetNodePtr);
	TEST_ASSERT_EQUAL(1,compare);
}

void test_compareFileSize_should_compare_2_files_size_and_return_negative_1(void){
	Node *rootNodePtr = NULL,*targetNodePtr = NULL;
	int compare = 0;
	unsigned long long int size1 = 2345678945;
	unsigned long long int size2 = 3333333333;
	unsigned long int crc1 = 1231234567;
	unsigned long int crc2 = 2331234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	
	rootNodePtr = createNode(fileObjectSize1,fileObjectCRC1);
	targetNodePtr = createNode(fileObjectSize2,fileObjectCRC2);
	
	compare = compareFileSize(&rootNodePtr,targetNodePtr);
	TEST_ASSERT_EQUAL(-1,compare);
}

void test_compareFileSize_should_compare_2_files_size_and_call_compareFileCRC_to_return_1(void){
	Node *rootNodePtr = NULL,*targetNodePtr = NULL;
	int compare = 0;
	unsigned long long int size1 = 2345678945;
	unsigned long long int size2 = 2345678945;
	unsigned long int crc1 = 4294967291;
	unsigned long int crc2 = 2331234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	
	rootNodePtr = createNode(fileObjectSize1,fileObjectCRC1);
	targetNodePtr = createNode(fileObjectSize2,fileObjectCRC2);
	
	compare = compareFileSize(&rootNodePtr,targetNodePtr);
	TEST_ASSERT_EQUAL(1,compare);
}

void test_compareFileSize_should_compare_2_files_size_and_call_compareFileCRC_to_return_negative_1(void){
	Node *rootNodePtr = NULL,*targetNodePtr = NULL;
	int compare = 0;
	unsigned long long int size1 = 2345678945;
	unsigned long long int size2 = 2345678945;
	unsigned long int crc1 = 1231234567;
	unsigned long int crc2 = 2331234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	
	rootNodePtr = createNode(fileObjectSize1,fileObjectCRC1);
	targetNodePtr = createNode(fileObjectSize2,fileObjectCRC2);
	
	compare = compareFileSize(&rootNodePtr,targetNodePtr);
	TEST_ASSERT_EQUAL(-1,compare);
}

void test_compareFileSize_should_compare_2_files_size_and_call_compareFileCRC_to_return_0(void){
	Node *rootNodePtr = NULL,*targetNodePtr = NULL;
	int compare = 0;
	unsigned long long int size1 = 2345678945;
	unsigned long long int size2 = 2345678945;
	unsigned long int crc1 = 2331234567;
	unsigned long int crc2 = 2331234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	
	rootNodePtr = createNode(fileObjectSize1,fileObjectCRC1);
	targetNodePtr = createNode(fileObjectSize2,fileObjectCRC2);
	
	compare = compareFileSize(&rootNodePtr,targetNodePtr);
	TEST_ASSERT_EQUAL(0,compare);
}

void test_compareFileCRC_should_compare_2_files_size_and_return_1(void){
	Node *rootNodePtr = NULL,*targetNodePtr = NULL;
	int compare = 0;
	unsigned long long int size1 = 5555555555;
	unsigned long long int size2 = 3333333333;
	unsigned long int crc1 = 2331234567;
	unsigned long int crc2 = 1231234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	
	rootNodePtr = createNode(fileObjectSize1,fileObjectCRC1);
	targetNodePtr = createNode(fileObjectSize2,fileObjectCRC2);
	
	compare = compareFileCRC(&rootNodePtr,targetNodePtr);
	TEST_ASSERT_EQUAL(1,compare);
}

void test_compareFileCRC_should_compare_2_files_size_and_return_negative_1(void){
	Node *rootNodePtr = NULL,*targetNodePtr = NULL;
	int compare = 0;
	unsigned long long int size1 = 5555555555;
	unsigned long long int size2 = 3333333333;
	unsigned long int crc1 = 1231234567;
	unsigned long int crc2 = 2331234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	
	rootNodePtr = createNode(fileObjectSize1,fileObjectCRC1);
	targetNodePtr = createNode(fileObjectSize2,fileObjectCRC2);
	
	compare = compareFileCRC(&rootNodePtr,targetNodePtr);
	TEST_ASSERT_EQUAL(-1,compare);
}

void test_compareFileCRC_should_compare_2_files_size_and_return_0(void){
	Node *rootNodePtr = NULL,*targetNodePtr = NULL;
	int compare = 0;
	unsigned long long int size1 = 5555555555;
	unsigned long long int size2 = 3333333333;
	unsigned long int crc1 = 2331234567;
	unsigned long int crc2 = 2331234567;
	json_t *fileObjectSize1 = json_integer(size1);
	json_t *fileObjectCRC1 = json_integer(crc1);
	json_t *fileObjectSize2 = json_integer(size2);
	json_t *fileObjectCRC2 = json_integer(crc2);
	
	rootNodePtr = createNode(fileObjectSize1,fileObjectCRC1);
	targetNodePtr = createNode(fileObjectSize2,fileObjectCRC2);
	
	compare = compareFileCRC(&rootNodePtr,targetNodePtr);
	TEST_ASSERT_EQUAL(0,compare);
}