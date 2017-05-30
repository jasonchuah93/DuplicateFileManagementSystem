#include "unity.h"
#include <stdbool.h>
#include "fileHandling.h"

#define TRUE 1
#define FALSE 0

void setUp(void){}
void tearDown(void){}

//Test for checking different types of file
void test_checkFile_if_the_parameter_is_text_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles/test1.txt"),TRUE);
}

void test_checkFile_if_the_parameter_is_image_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles/testPicture.jpg"),TRUE);
}

void test_checkFile_if_the_parameter_is_PDF_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles/testPDF.pdf"),TRUE);
}

void test_checkFile_if_the_parameter_is_Music_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles/test Song.mp3"),TRUE);
}

void test_checkFile_if_the_parameter_is_Exel_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles/test Exel.xlsx"),TRUE);
}

void test_checkFile_if_the_parameter_is_Words_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles/TEST Words.docx"),TRUE);
}

void test_checkFile_if_the_parameter_is_PowerPoint_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles/test p.point.pptx"),TRUE);
}

void test_checkFile_if_the_parameter_is_folder_should_return_FALSE(void){
	TEST_ASSERT_EQUAL(checkFile("test/testFiles"),FALSE);
}

//Test for checking folder
void test_checkFolder_if_the_parameter_is_folder_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFolder("test/testFiles"),TRUE);
}
void test_checkFolder_if_the_parameter_is_sub_folder_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFolder("test/testFiles/test folder"),TRUE);
}
void test_checkFolder_if_the_parameter_is_file_should_return_FALSE(void){
	TEST_ASSERT_EQUAL(checkFolder("test/testFiles/test1.txt"),FALSE);
}
