#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"

int checkJSON(const char* path){
	//FILE *JSONF = fopen(path,"r");
	int cmp = 0;
	const char ext = '.';
	char *jsonExt;
	jsonExt = strrchr(path,ext);
	cmp = strcmp(jsonExt,".json");
	if(cmp == 0)
		return 1;
	else
		return 0;
}

int createJSON(const char* JSONpath,const char* filePath){
	FILE *fp = NULL ;
	int fileSize = 0,crc32Val = 0;
	unsigned long int epochSec = 0;
	char *cp = NULL, fileName[100];
	fp = fopen(JSONpath,"w");
	if(fp == NULL){
		printf("Error!");
		exit(1);
	}
	json_t *jObject = json_object();
	json_t *jArray = json_array();
	
	//Get file name
	json_object_set_new(jObject,"name",json_string(filePath));
	//Get file size
	fileSize = getFileSize(filePath);
	json_object_set_new(jObject,"size",json_integer(fileSize));
	//Get file crc32
	crc32Val = hashCRC(filePath);
	json_object_set_new(jObject,"crc32 value",json_integer(crc32Val));
	//Get file date and time in Epoch format
	fileDateTime(fileName,filePath);
	epochSec = convertEpoch(fileName);
	json_object_set_new(jObject,"Epoch Sec",json_integer(epochSec));
	
	cp = json_dumps(jObject,0);
	json_dumpf(jObject,fp,100);
	puts(cp);
	json_decref(jObject);
	fclose(fp);
	return 0;
}