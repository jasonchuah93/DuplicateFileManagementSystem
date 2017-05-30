#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generateCRC32Value.h"

void setUp(void){}
void tearDown(void){}

void test_generate_CRC32Value_from_text_file(void){
	FILE *testFile;
	char buff[255];
	testFile = fopen("D:/Jason/Github/fileDuplicateSearch/test/testFiles","r");
	fscanf(testFile,"%s",buff);
	printf("File: %s\n",buff);
	//Crc32_ComputeFile(testFile,0);
}
