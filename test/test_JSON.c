#include "unity.h"
//#include <string.h>
//#include <stdio.h>
#include <stdlib.h>
#include "fileInfo.h"
#include "generateCRC32Value.h"
#include "fileHandling.h"
/*



#include <malloc.h>
#include "jansson.h"


#include "Node.h"

#include "compareJSON.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "LinkedList.h"

*/
#include "errorNode.h"
#include "CException.h"
#include "JSON.h"

void setUp(void){}
void tearDown(void){}

void test_checkFilesLatestThanJson_should_return_negative_1_if_json_file_is_not_latest_inside_folder(void){
	TEST_ASSERT_EQUAL(-1,checkFilesLatestThanJson("forTesting","fileInformation.json"));
	
}

void test_checkFilesLatestThanJson_should_return_1_if_json_file_is_latest_inside_folder(void){
	TEST_ASSERT_EQUAL(1,checkFilesLatestThanJson("TestJSON/SubFolder1","fileInformation.json"));
}

void test_writeJsonObjectIntoFile_should_write_json_object_into_emtpy_json_file(void){
	json_t *folderObject = createJsonFolderObject("TestJSON");
	writeJsonObjectIntoFile("FolderForTesting/jsonFile.json",folderObject);
}

void test_getFileInfoFromJsonObject_should_get_file_information_from_json_object(void){
	FileInfo *info = initInfo();
	json_t *folderObject = NULL, *folderArray = NULL;
	folderObject = createJsonFolderObject("TestJSON");
	folderArray = goIntoJsonArrayFrmFolderObj(folderObject);
	getFileInfoFromJsonObject(folderArray,info,1);
	
	TEST_ASSERT_NOT_NULL(folderObject);
	TEST_ASSERT_NOT_NULL(folderArray);
	TEST_ASSERT_EQUAL_STRING("Testing 3.xlsx",info->fileName);
	TEST_ASSERT_EQUAL(10038,info->fileSize);
	TEST_ASSERT_EQUAL(305591788,info->fileCRC32Value);
}

void test_getFileInfoFromJsonObject_should_throw_error_if_json_object_is_not_integer_for_crc(void){
	Error *e = NULL;
	FileInfo *info = initInfo();
	//Mock a folder object with a crc in string format
	json_t *fobj = json_object();
	json_t *jArray = json_array();
	json_object_set_new(fobj,"crc",json_string("testing"));
	json_array_append(jArray,fobj);
	
	Try{
		getFileInfoFromJsonObject(jArray,info,0);
		TEST_FAIL_MESSAGE("Expected ERR_NOT_INTEGER_OBJECT to be thrown.");
	}Catch(e){
		TEST_ASSERT_EQUAL(e,ERR_NOT_INTEGER_OBJECT);
	}	
}

void test_getFileInfoFromJsonObject_should_throw_error_if_json_object_is_not_integer_for_size(void){
	Error *e = NULL;
	FileInfo *info = initInfo();
	//Mock a folder object with a size in string format
	json_t *fobj = json_object();
	json_t *jArray = json_array();
	json_object_set_new(fobj,"size",json_string("testing"));
	json_array_append(jArray,fobj);
	
	Try{
		getFileInfoFromJsonObject(jArray,info,0);
		TEST_FAIL_MESSAGE("Expected ERR_NOT_INTEGER_OBJECT to be thrown.");
	}Catch(e){
		TEST_ASSERT_EQUAL(e,ERR_NOT_INTEGER_OBJECT);
	}	
}

void test_getFileInfoFromJsonObject_should_throw_error_if_json_object_is_not_string_for_name(void){
	Error *e = NULL;
	FileInfo *info = initInfo();
	//Mock a folder object with a name in integer format
	json_t *fobj = json_object();
	json_t *jArray = json_array();
	json_object_set_new(fobj,"name",json_integer(100));
	json_array_append(jArray,fobj);
	
	Try{
		getFileInfoFromJsonObject(jArray,info,0);
		TEST_FAIL_MESSAGE("Expected ERR_NOT_STRING_OBJECT to be thrown.");
	}Catch(e){
		TEST_ASSERT_EQUAL(e,ERR_NOT_STRING_OBJECT);
	}	
}

void test_getFileInfoFromJsonObject_should_throw_error_if_json_object_not_inside_json_array(void){
	Error *e = NULL;
	FileInfo *info = initInfo();
	//Mock an array within an array. 
	json_t *jArray = json_array();
	json_t *fileArray = json_array();
	json_array_append(jArray,fileArray);
	
	Try{
		getFileInfoFromJsonObject(jArray,info,0);
		TEST_FAIL_MESSAGE("Expected ERR_NOT_JSON_OBJECT to be thrown.");
	}Catch(e){
		TEST_ASSERT_EQUAL(e,ERR_NOT_JSON_OBJECT);
	}	
}

void test_getFileInfoFromJsonObject_should_throw_error_if_first_argument_is_not_an_array(void){
	Error *e = NULL;
	FileInfo *info = initInfo();
	json_t *fileArray = json_object();
	Try{
		getFileInfoFromJsonObject(fileArray,info,0);
		TEST_FAIL_MESSAGE("Expected ERR_NOT_JSON_ARRAY to be thrown.");
	}Catch(e){
		TEST_ASSERT_EQUAL(e,ERR_NOT_JSON_ARRAY);
	}	
}

void test_createJsonFolderObject_should_create_json_object_stored_file_info(void){
	json_t *folderObject = NULL, *folderArray = NULL, *fileObject = NULL;
	
	folderObject = createJsonFolderObject("TestJSON");
	folderArray = goIntoJsonArrayFrmFolderObj(folderObject);
	fileObject = json_array_get(folderArray,0); // 0 indicate get first file info in folder
	json_t *fileName = json_object_get(fileObject,"name");
	json_t *fileSize = json_object_get(fileObject,"size");
	json_t *fileCRC = json_object_get(fileObject,"crc");
	json_t *fileTime = json_object_get(fileObject,"epoch");
	
	TEST_ASSERT_NOT_NULL(folderObject);
	TEST_ASSERT_NOT_NULL(folderArray);
	TEST_ASSERT_NOT_NULL(fileObject);
	TEST_ASSERT_EQUAL_STRING("Testing 2.xlsx",json_string_value(fileName));
	TEST_ASSERT_EQUAL(10038,json_integer_value(fileSize));
	TEST_ASSERT_EQUAL(305591788,json_integer_value(fileCRC));
	TEST_ASSERT_EQUAL(1500185350,json_integer_value(fileTime));
}

void test_goIntoJsonArrayFrmFolderObj_should_throw_error_if_input_is_not_an_json_object(void){
	Error *e = NULL;
	json_t *folderObj = json_array();
	
	Try{
		goIntoJsonArrayFrmFolderObj(folderObj);
		TEST_FAIL_MESSAGE("Expected ERR_NOT_JSON_OBJECT to be thrown.");
	}Catch(e){
		TEST_ASSERT_EQUAL(e,ERR_NOT_JSON_OBJECT);
	}	
}

void test_checkJsonFileExistInFolder_should_return_1_if_folder_contain_json_file(void){
	TEST_ASSERT_EQUAL(checkJsonFileExistInFolder("forTesting","fileInformation.json"),1);
}

void test_checkJsonFileExistInFolder_should_return_negative_1_if_folder_no_contain_json_file(void){
	TEST_ASSERT_EQUAL(checkJsonFileExistInFolder("FolderForTesting","fileInformation.json"),-1);
}

void test_checkJsonTypeFile_should_return_1_if_the_file_type_is_json(void){
	TEST_ASSERT_EQUAL(checkJsonTypeFile("forTesting/J.json"),1);
}

void test_test_checkJsonTypeFile_should_return_1_if_the_file_type_is_json_should_return_0_if_the_file_type_is_not_json(void){
	TEST_ASSERT_EQUAL(checkJsonTypeFile("forTesting/J.docx"),0);
}



/*


void test_checkFileLaterThanJson_should_return_0_if_json_file_is_latest_inside_folder(void){
	int check = 1;
	check = checkFileLaterThanJson("TestJSON","fileInformation.json");
	TEST_ASSERT_EQUAL(0,check);
}

void test_checkFileLaterThanJson_should_return_1_if_json_file_is_not_latest_inside_folder(void){
	int check = 0;
	check = checkFileLaterThanJson("forTesting/test folder","fileInformation.json");
	TEST_ASSERT_EQUAL(1,check);
}

void test_load_existing_json_file_to_read_the_object_inside(void){
	json_t *folderObj = NULL;
	json_t *fileArray = NULL;
	size_t arraySize = 0;
	json_error_t jError;
	folderObj = json_load_file("TestJSON/fileInformation.json",0,&jError);
	
	if(json_is_object(folderObj)){
		fileArray = getJsonArrayFrmFolderObj(folderObj);
		arraySize = json_array_size(fileArray);
		//printf("array size:%d\n",arraySize);
	}
}

void test_updateJson_should_check_file_date_time_compare_to_json_file(void){
	Node *dupRoot = NULL;
	//char *testFile1 = createFileForTesting("FolderForTesting/TestFileP.txt",5000);
	//duplicateFileForTesting(testFile1,"5");
	traverseFolder(&dupRoot,"FolderForTesting");
	summariseFolder(&dupRoot);
	
	//TEST_ASSERT_NOT_NULL(removedEle);
	//TEST_ASSERT_NOT_NULL(removedNode);
}


void test_updateJson_should_check_file_number_compare_to_json_file_array_size(void){
	json_t *obj = NULL;
	Node *dupRoot = NULL;
	
	//traverseFolder(&dupRoot,"FolderForTesting");
	//obj = updateJson("FolderForTesting","fileInformation.json");
	//TEST_ASSERT_NOT_NULL(obj);
}
*/

