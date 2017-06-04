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

//Test for getting file size
void test_checkFileSize_should_get_the_size_of_text_file(void){
	//test1.txt file size is 33 bytes.
	int fileSize=0;
	fileSize=checkFileSize("D:/jason/github/testFiles/test1.txt");
	TEST_ASSERT_EQUAL(fileSize,33);
}

void test_checkFileSize_should_get_the_size_of_mp3(void){
	//Song file size is 3965661 bytes.
	int fileSize=0;
	fileSize=checkFileSize("D:/jason/github/testFiles/Alan Walker - Alone.mp3");
	TEST_ASSERT_EQUAL(fileSize,3965661);
}

void test_checkFileSize_should_get_the_size_of_pdf(void){
	//PDF file size is 249159 bytes.
	int fileSize=0;
	fileSize=checkFileSize("D:/jason/github/testFiles/testPDF.pdf");
	TEST_ASSERT_EQUAL(fileSize,249159);
}

void test_checkFileSize_should_get_the_size_of_image_file(void){
	//Image file size is 1563175 bytes.
	int fileSize=0;
	fileSize=checkFileSize("D:/jason/github/testFiles/testPicture.jpg");
	TEST_ASSERT_EQUAL(fileSize,1563175);
}

void test_checkFileSize_should_get_the_size_of_words_file(void){
	//Microsoft Words file size is 15400 bytes.
	int fileSize=0;
	fileSize=checkFileSize("D:/jason/github/testFiles/TEST Words.docx");
	TEST_ASSERT_EQUAL(fileSize,15400);
}

void test_checkFileSize_should_get_the_size_of_video_file(void){
	//Microsoft Words file size is 20065907 bytes.
	int fileSize=0;
	fileSize=checkFileSize("D:/jason/github/testFiles/test Video.mp4");
	TEST_ASSERT_EQUAL(fileSize,20065907);
}

//Test for checking the file last modified time
void xtest_checkFileLatestTime_should_check_the_latest_modified_time_of_text_file(void){
	int fileTime=0;
	fileTime = checkFileLatestTime("D:/jason/github/testFiles/test1.txt");
	//TEST_ASSERT_EQUAL(fileTime,)
}
