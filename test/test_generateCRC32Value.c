#include "unity.h"
#include "generateCRC32Value.h"

void setUp(void){}
void tearDown(void){}

//Test for checking CRC32 Value

void test_hashCRC_should_be_equal_for_two_file_with_same_content_but_different_name(void){
	int checksum1=0,checksum2=0;
	checksum1=hashCRC("D:/jason/github/testFiles/test1.txt");
	checksum2=hashCRC("D:/jason/github/testFiles/test2.txt");
	TEST_ASSERT_EQUAL(checksum1,checksum2);
}

void test_hashCRC_should_not_be_equal_if_file_content_is_different(void){
	int checksum1=0,checksum2=0;
	checksum1=hashCRC("D:/jason/github/testFiles/testPicture.jpg");
	checksum2=hashCRC("D:/jason/github/testFiles/testPicture2.jpg");
	TEST_ASSERT_NOT_EQUAL(checksum1,checksum2);
}

void test_hashCRC_should_not_be_equal_if_type_of_files_is_different(void){
	int checksum1=0,checksum2=0;
	checksum1=hashCRC("D:/jason/github/testFiles/testPDF.pdf");
	checksum2=hashCRC("D:/jason/github/testFiles/TEST Words.docx");
	TEST_ASSERT_NOT_EQUAL(checksum1,checksum2);
}

void test_hashCRC_should_be_equal_if_type_of_file_is_same_but_in_different_folder(void){
	int checksum1=0,checksum2=0;
	checksum1=hashCRC("D:/jason/github/testFiles/test p.point.pptx");
	checksum2=hashCRC("D:/jason/github/testFiles/test folder/test p.point2.pptx");
	TEST_ASSERT_EQUAL(checksum1,checksum2);
}

void test_hashCRC_should_be_equal_for_two_file_with_same_content_but_different_name_in_excel_format(void){
	int checksum1=0,checksum2=0;
	checksum1=hashCRC("D:/jason/github/testFiles/test Exel.xlsx");
	checksum2=hashCRC("D:/jason/github/testFiles/test Exel2.xlsx");
	TEST_ASSERT_EQUAL(checksum1,checksum2);
}
