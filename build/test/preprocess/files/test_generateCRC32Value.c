#include "generateCRC32Value.h"
#include "unity.h"


void setUp(void){}

void tearDown(void){}







void test_hashCRC_should_be_equal_for_two_file_with_same_content_but_different_name(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/test1.txt");

 checksum2=hashCRC("forTesting/test2.txt");

 UnityAssertEqualNumber((_U_SINT)((checksum1)), (_U_SINT)((checksum2)), (

((void *)0)

), (_U_UINT)(13), UNITY_DISPLAY_STYLE_INT);

}



void test_hashCRC_should_not_be_equal_if_file_content_is_different(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/testPicture.jpg");

 checksum2=hashCRC("forTesting/testPicture2.jpg");

 if (((checksum1) != (checksum2))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(20)));};

}



void test_hashCRC_should_not_be_equal_if_type_of_files_is_different(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/testPDF.pdf");

 checksum2=hashCRC("forTesting/TEST Words.docx");

 if (((checksum1) != (checksum2))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(27)));};

}



void test_hashCRC_should_be_equal_if_type_of_file_is_same_but_in_different_folder(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/test p.point.pptx");

 checksum2=hashCRC("forTesting/test folder/test p.point2.pptx");

 UnityAssertEqualNumber((_U_SINT)((checksum1)), (_U_SINT)((checksum2)), (

((void *)0)

), (_U_UINT)(34), UNITY_DISPLAY_STYLE_INT);

}



void test_hashCRC_should_be_equal_for_two_file_with_same_content_but_different_name_in_excel_format(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/test Exel.xlsx");

 checksum2=hashCRC("forTesting/test Exel2.xlsx");

 UnityAssertEqualNumber((_U_SINT)((checksum1)), (_U_SINT)((checksum2)), (

((void *)0)

), (_U_UINT)(41), UNITY_DISPLAY_STYLE_INT);

}
