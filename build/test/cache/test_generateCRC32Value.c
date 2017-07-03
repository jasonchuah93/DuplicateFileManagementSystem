#include "generateCRC32Value.h"
#include "unity.h"


void setUp(void){}

void tearDown(void){}







void test_hashCRC_should_return_0_if_input_is_not_a_file_type(void){

 int checksum1=0;

 checksum1=hashCRC("forTesting");

 UnityAssertEqualNumber((_U_SINT)((checksum1)), (_U_SINT)((0)), (

((void *)0)

), (_U_UINT)(12), UNITY_DISPLAY_STYLE_INT);

}

void test_hashCRC_should_be_equal_for_two_file_with_same_content_but_different_name(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/test1.txt");

 checksum2=hashCRC("forTesting/test2.txt");

 UnityAssertEqualNumber((_U_SINT)((checksum1)), (_U_SINT)((checksum2)), (

((void *)0)

), (_U_UINT)(18), UNITY_DISPLAY_STYLE_INT);

}



void test_hashCRC_should_not_be_equal_if_file_content_is_different(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/testPicture.jpg");

 checksum2=hashCRC("forTesting/testPicture2.jpg");

 if (((checksum1) != (checksum2))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(25)));};

}



void test_hashCRC_should_not_be_equal_if_type_of_files_is_different(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/testPDF.pdf");

 checksum2=hashCRC("forTesting/TEST Words.docx");

 if (((checksum1) != (checksum2))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(32)));};

}



void test_hashCRC_should_be_equal_if_type_of_file_is_same_but_in_different_folder(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/test p.point.pptx");

 checksum2=hashCRC("forTesting/test folder/test p.point2.pptx");

 UnityAssertEqualNumber((_U_SINT)((checksum1)), (_U_SINT)((checksum2)), (

((void *)0)

), (_U_UINT)(39), UNITY_DISPLAY_STYLE_INT);

}



void test_hashCRC_should_be_equal_for_two_file_with_same_content_but_different_name_in_excel_format(void){

 int checksum1=0,checksum2=0;

 checksum1=hashCRC("forTesting/test Exel.xlsx");

 checksum2=hashCRC("forTesting/test Exel2.xlsx");

 UnityAssertEqualNumber((_U_SINT)((checksum1)), (_U_SINT)((checksum2)), (

((void *)0)

), (_U_UINT)(46), UNITY_DISPLAY_STYLE_INT);

}
