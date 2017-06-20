#include "unity.h"
#include "fileHandling.h"

void setUp(void){}
void tearDown(void){}

//TRUE is 1
//FALSE is 0

//Test for checking if is file
void test_checkFile_should_return_FALSE_if_file_is_not_exist_in_folder(void){
	int check;
	check = checkFile("D:/jason/github/testFiles/testJason.txt");
	TEST_ASSERT_EQUAL(check,FALSE);
}

void test_checkFile_should_return_TRUE_if_file_is_text_file(void){
	int check;
	check = checkFile("D:/jason/github/testFiles/test1.txt");
	TEST_ASSERT_EQUAL(check,TRUE);
}

void test_checkFile_should_return_TRUE_if_is_image_file_(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/testPicture.jpg"),TRUE);
}

void test_checkFile_if_should_return_TRUE_if_is_PDF_file(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/testPDF.pdf"),TRUE);
}

void test_checkFile_should_return_TRUE_if_is_Music_file_(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/testSong.mp3"),TRUE);
}

void test_checkFile_should_return_TRUE_if_is_Exel_file(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/test Exel.xlsx"),TRUE);
}

void test_checkFile_should_return_TRUE_if_is_Words_file_(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/TEST Words.docx"),TRUE);
}

void test_checkFile_should_return_TRUE_if_is_PowerPoint_file(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/test folder/test p.point2.pptx"),TRUE);
}

void test_checkFile_should_return_TRUE_if_is_JSON_file(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles/test.json"),TRUE);
}

void test_checkFile_should_return_FALSE_if_is_folder(void){
	TEST_ASSERT_EQUAL(checkFile("D:/jason/github/testFiles"),FALSE);
}

//Test for checking if is folder
void test_checkFolder_should_return_FALSE_if_is_invalid_folder(void){
	TEST_ASSERT_EQUAL(checkFolder("D:/jason/github/testtestfolder"),FALSE);
}

void test_checkFolder_should_return_TRUE_if_is_folder_(void){
	TEST_ASSERT_EQUAL(checkFolder("D:/jason/github/testFiles"),TRUE);
}

void test_checkFolder_should_return_TRUE_if_is_sub_folder_(void){
	TEST_ASSERT_EQUAL(checkFolder("D:/jason/github/testFiles/test folder"),TRUE);
}

void test_checkFolder_should_return_FALSE_if_is_file(void){
	TEST_ASSERT_EQUAL(checkFolder("D:/jason/github/testFiles/test1.txt"),FALSE);
}


//Test for getting file size
void test_getFileSize_should_get_the_size_of_text_file(void){
	//test1.txt file size is 33 bytes.
	int fileSize=0;
	fileSize=getFileSize("D:/jason/github/testFiles/test1.txt");
	TEST_ASSERT_EQUAL(fileSize,33);
}

void test_checkFileSize_should_get_the_size_of_mp3(void){
	//Song file size is 3965661 bytes.
	int fileSize=0;
	fileSize=getFileSize("D:/jason/github/testFiles/Alan Walker - Alone.mp3");
	TEST_ASSERT_EQUAL(fileSize,3965661);
}

void test_checkFileSize_should_get_the_size_of_pdf(void){
	//PDF file size is 249159 bytes.
	int fileSize=0;
	fileSize=getFileSize("D:/jason/github/testFiles/testPDF.pdf");
	TEST_ASSERT_EQUAL(fileSize,249159);
}

void test_checkFileSize_should_get_the_size_of_image_file(void){
	//Image file size is 1563175 bytes.
	int fileSize=0;
	fileSize=getFileSize("D:/jason/github/testFiles/testPicture.jpg");
	TEST_ASSERT_EQUAL(fileSize,1563175);
}

void test_checkFileSize_should_get_the_size_of_words_file(void){
	//Microsoft Words file size is 15400 bytes.
	int fileSize=0;
	fileSize=getFileSize("D:/jason/github/testFiles/TEST Words.docx");
	TEST_ASSERT_EQUAL(fileSize,15400);
}

void test_checkFileSize_should_get_the_size_of_video_file(void){
	//Video file size is 20065907 bytes.
	int fileSize=0;
	fileSize=getFileSize("D:/jason/github/testFiles/test Video.mp4");
	TEST_ASSERT_EQUAL(fileSize,20065907);
}

//Test for checking the file last modified time
void test_fileDateTime_should_check_the_latest_modified_time_of_text_file(void){
	//Text 1 last modified time is 2017/06/05 22:48:10
	char textFile[20]={0};
	fileDateTime(textFile,"D:/jason/github/testFiles/test1.txt");
	TEST_ASSERT_EQUAL_STRING(textFile,"2017/06/05 22:48:10");
}

void test_fileDateTime_should_check_the_latest_modified_time_of_video_file(void){
	//Video file last modified time is 2017/06/03 13:36:23
	char videoFile[20]={0};
	fileDateTime(videoFile,"D:/jason/github/testFiles/test Video.mp4");
	TEST_ASSERT_EQUAL_STRING(videoFile,"2017/06/03 13:36:23");
}

void test_fileDateTime_should_check_the_latest_modified_time_of_PDF_file(void){
	//PDF file last modified time is 2012/12/22 10:51:56
	char pdfFile[20]={0};
	fileDateTime(pdfFile,"D:/jason/github/testFiles/testPDF.pdf");
	TEST_ASSERT_EQUAL_STRING(pdfFile,"2012/12/22 10:51:56");
}

void test_fileDateTime_should_check_the_latest_modified_time_of_Words_file(void){
	//Words file last modified time is 2016/04/08 17:38:03
	char wordsFile[20]={0};
	fileDateTime(wordsFile,"D:/jason/github/testFiles/TEST Words.docx");
	TEST_ASSERT_EQUAL_STRING(wordsFile,"2016/04/08 17:38:03");
}

void test_fileDateTime_should_check_the_latest_modified_time_of_image_file(void){
	//Image file last modified time is 2017/06/03 00:46:57
	char imageFile[20]={0};
	fileDateTime(imageFile,"D:/jason/github/testFiles/testPicture2.jpg");
	TEST_ASSERT_EQUAL_STRING(imageFile,"2017/06/03 00:46:57");
}

void test_convertEpoch_should_return_convert_the_file_dateTime_to_Epoch_format(void){
	//Words file last modified time is 2016/04/08 17:38:03
	//Words file epoch seconds is 1460108283
	unsigned long int epochSecs = 0;
	char wordsFile[20]={0};
	fileDateTime(wordsFile,"D:/jason/github/testFiles/TEST Words.docx");
	epochSecs = convertEpoch(wordsFile);
	TEST_ASSERT_EQUAL(epochSecs,1460108283);
}

void test_compareDateTime_should_return_1_if_the_file_dateTime_is_latest_than_input_path(void){
	//Image file last modified time is 2017/06/03 00:46:57
	//MP3 file last modified time is 2016/12/15 01:33:38
	int check = 0;
	char imageFile[20]={0};
	//fileDateTime(imageFile,"D:/jason/github/testFiles/testPicture2.jpg");
	//check = compareDateTime(imageFile,"D:/jason/github/testFiles/Alan Walker - Alone.mp3");
	//TEST_ASSERT_EQUAL(check,1);
}

//Test for listFileNumber
void test_listFileNumber_should_list_the_total_number_of_file_in_folder(void){
	int fileNumber=0;
	fileNumber = listFileNumber("D:/jason/github/testFiles"); //Number of file in this folder is 15
	TEST_ASSERT_EQUAL(fileNumber,15);
}

//Test for listSubFolderNumber
void test_listSubFolderNumber_should_list_the_total_number_of_sub_folder_in_folder(void){
	int subFolderNumber=0;
	subFolderNumber = listSubFolderNumber("D:/jason/github/testFiles"); //Number of subfolder in this folder is 3
	TEST_ASSERT_EQUAL(subFolderNumber,2);
}

void test_traverseFolder_should_scan_through_the_content_of_the_folder(void){
	traverseFolder("D:/jason/github/testFiles");
}

