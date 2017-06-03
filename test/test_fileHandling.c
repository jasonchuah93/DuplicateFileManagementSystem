#include "unity.h"
#include "fileHandling.h"

void setUp(void){}
void tearDown(void){}

//Test for checking if is file
void test_checkFile_if_the_parameter_is_text_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/test1.txt"),TRUE);
}

void test_checkFile_if_the_parameter_is_image_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/testPicture.jpg"),TRUE);
}

void test_checkFile_if_the_parameter_is_PDF_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/testPDF.pdf"),TRUE);
}

void test_checkFile_if_the_parameter_is_Music_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/test Song.mp3"),TRUE);
}

void test_checkFile_if_the_parameter_is_Exel_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/test Exel.xlsx"),TRUE);
}

void test_checkFile_if_the_parameter_is_Words_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/TEST Words.docx"),TRUE);
}

void test_checkFile_if_the_parameter_is_PowerPoint_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/test folder/test p.point.pptx"),TRUE);
}

void test_checkFile_if_the_parameter_is_JSON_file_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/test.json"),TRUE);
}

void test_checkFile_if_the_parameter_is_folder_should_return_FALSE(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles"),FALSE);
}

//Test for checking if is folder

void test_checkFolder_if_the_parameter_is_folder_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFolder("D:/jason/github/testFiles"),TRUE);
}
void test_checkFolder_if_the_parameter_is_sub_folder_should_return_TRUE(void){
	TEST_ASSERT_EQUAL(checkFolder("D:/jason/github/testFiles/test folder"),TRUE);
}
void test_checkFolder_if_the_parameter_is_file_should_return_FALSE(void){
	TEST_ASSERT_EQUAL(checkFolder("D:/jason/github/testFiles/test1.txt"),FALSE);
}

//Test for checking folder or file 
void test_checkFileFolder_should_return_TRUE_and_list_out_content_if_folder_is_not_empty(void){
	TEST_ASSERT_EQUAL(checkFileFolder("D:/jason/github/testFiles"),TRUE);
}


