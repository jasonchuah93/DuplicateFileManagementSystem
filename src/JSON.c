#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"

int checkJSON(const char* path){
	int cmp = 0;
	char *jsonExt = NULL;
	const char ext = '.';
	jsonExt = strrchr(path,ext);
	cmp = strcmp(jsonExt,".json");
	if(cmp == 0)
		return 1;
	else
		return 0;
}

int createJSON(const char* JSONpath,const char* filePath,int fileCount){
	FILE *fp = NULL ;
	int fileSize = 0, i = 0;
	unsigned int crc32Val = 0;
	unsigned long int epochSec = 0;
	char *cp = NULL, fileName[100]={0};
	const char *newFilePath = NULL;
	fp = fopen(JSONpath,"w");
	if(fp == NULL){
		printf("Error!");
		exit(1);
	}
	
	json_t *jArray = json_array();
	json_t *fileTitle = json_object();
	json_t *fileInfo = json_object();
	json_t *fileObject = json_object();
	//Set file title
	json_object_set_new(fileTitle,"File",jArray);
	while(i < fileCount){
		//Set file info
		json_object_set_new(fileInfo,"File Info",fileObject);
		//Get file name
		json_object_set_new(fileObject,"name",json_string(filePath));
		//Get file size
		fileSize = getFileSize(filePath);
		json_object_set_new(fileObject,"size",json_integer(fileSize));
		//Get file crc32
		crc32Val = hashCRC(filePath);
		json_object_set_new(fileObject,"crc32 value",json_integer(crc32Val));
		//Get file date and time in Epoch format
		fileDateTime(fileName,filePath);
		epochSec = convertEpoch(fileName);
		json_object_set_new(fileObject,"Epoch Sec",json_integer(epochSec));
		
		json_array_append(jArray,fileInfo);
		i++;
	}
	cp = json_dumps(fileTitle,0);
	json_dumpf(fileTitle,fp,100);
	puts(cp);
	json_decref(fileTitle);
	fclose(fp);
	return 0;
}