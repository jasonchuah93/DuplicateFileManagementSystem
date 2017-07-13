#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include "jansson.h"
#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "Node.h"
#include "errorNode.h"
#include "compareJSON.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "CException.h"

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

void createJSON(const char* JSONpath,const char* filePath,char *filePathPtr[],int fileCount){
	FILE *fp = NULL;
	int fileSize = 0, i = 0;
	unsigned int crc32Val = 0;
	unsigned long int epochSec = 0;
	char *cp = NULL, *jsonExt = NULL, fileDate[200]={0}, fileNamePath[200]={0};
	const char ext = '/';
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
		json_t *fileObjectName = json_string(filePath);
		json_t *fileObjectSize = json_integer(fileSize);
		json_t *fileObjectCRC = json_integer(crc32Val);
		//Set file info
		json_object_set_new(fileInfo,"File Info",fileObject);
		sprintf(fileNamePath,"%s/%s",filePath,filePathPtr[i]);
		//Get file name
		jsonExt = strrchr(fileNamePath,ext);
		json_object_set_new(fileObject,"name",json_string(jsonExt+1));
		//Get file size
		fileSize = getFileSize(fileNamePath);
		json_object_set_new(fileObject,"size",json_integer(fileSize));
		//printf("file size in json: %d\n",json_integer_value(fileObjectSize));
		//Get file crc32
		crc32Val = hashCRC(fileNamePath);
		json_object_set_new(fileObject,"crc32 value",json_integer(crc32Val));
		//Get file date and time in Epoch format
		fileDateTime(fileDate,fileNamePath);
		epochSec = convertEpoch(fileDate);
		json_object_set_new(fileObject,"Epoch Sec",json_integer(epochSec));
		json_array_append(jArray,fileInfo);
		i++;
	}
	cp = json_dumps(fileTitle,0);
	json_dumpf(fileTitle,fp,100);
	puts(cp);
	json_decref(fileTitle);
	fclose(fp);
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
