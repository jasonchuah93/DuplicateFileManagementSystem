#include "JSON.h"

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

int createJSON(const char* JSONpath,const char* filePath,char *filePathPtr[],int fileCount){
	FILE *fp = NULL ;
	int fileSize = 0, i = 0;
	unsigned int crc32Val = 0;
	unsigned long int epochSec = 0;
	char *cp = NULL, fileName[200]={0}, fileNamePath[200]={0};
	const char *newFilePath = NULL;
	fp = fopen(JSONpath,"w");
	if(fp == NULL){
		printf("Error!");
		exit(1);
	}
	
	json_t *jArray = json_array();
	json_t *fileTitle = json_object();
	
	//Set file title
	json_object_set_new(fileTitle,"File",jArray);
	while(i < fileCount){
		json_t *fileInfo = json_object();
		json_t *fileObject = json_object();
		json_t *fileObjectSize = json_integer(fileSize);
		json_t *fileObjectCRC = json_integer(crc32Val);
		//Set file info
		json_object_set_new(fileInfo,"File Info",fileObject);
		sprintf(fileNamePath,"%s/%s",filePath,filePathPtr[i]);
		//Get file name
		json_object_set_new(fileObject,"name",json_string(fileNamePath));
		//Get file size
		fileSize = getFileSize(fileNamePath);
		json_object_set_new(fileObject,"size",json_integer(fileSize));
		//printf("file size in json: %d\n",json_integer_value(fileObjectSize));
		//Get file crc32
		crc32Val = hashCRC(fileNamePath);
		json_object_set_new(fileObject,"crc32 value",json_integer(crc32Val));
		//Get file date and time in Epoch format
		fileDateTime(fileName,fileNamePath);
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

int delJSON(char *JSONfile){
	int check =0,ret = 0;
	check = checkJSON(JSONfile);
	if(check){
		ret = remove(JSONfile);
		if(ret == 0){
			return 1;
		}else{
			printf("JSON file does not exist!!!");
			return 0;
		}
	}else{
		printf("This is not JSON file!!!");
		return 0;
	}
}
