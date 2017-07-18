#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
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

struct dirent *dir = NULL;

void getFileInfoFrmJson(json_t *fileArray,FileInfo *fptr,int counter){
	void *iter = NULL;
	json_t *fileObject = NULL;
	json_t *objName = NULL;
	json_t *objSize = NULL;
	json_t *objCRC = NULL;
	if(json_is_array(fileArray)){
		fileObject = json_array_get(fileArray,counter);
		if(json_is_object(fileObject)){
			objName = json_object_get(fileObject,"name");
			printf("file name: %s\n",json_string_value(objName));
		}else
			Throw((Error*)ERR_NOT_JSON_OBJECT);
	}else
		Throw((Error*)ERR_NOT_JSON_ARRAY);
}

json_t *getJsonArrayFrmFolderObj(json_t *folderObject){
	json_t *fileArray = NULL;
	if(json_is_object(folderObject)){
		void *iter = json_object_iter(folderObject);
		fileArray = json_object_iter_value(iter);
	}else
		Throw((Error*)ERR_NOT_JSON_OBJECT);
	return fileArray;
}

json_t *createJsonObjectFrmFolder(const char *folderPath){
	unsigned long long int fileSize = 0;
	unsigned long int fileCRC32Value = 0, fileEpochSec = 0;
	char filePath[100] = {0}, fileDateTime[50] = {0};
	DIR *d = opendir(folderPath);
	json_t *fileInfo = json_object();
	json_t *jArray = json_array();
	json_object_set_new(fileInfo,"File Info",jArray);
	while((dir = readdir(d))!=NULL){
		json_t *fileObject = json_object();
		strcpy(filePath,folderPath);
		strcat(filePath,"/");
		strcat(filePath,dir->d_name);
		if(dir->d_type == DT_REG){
			if(strcmp(dir->d_name,"fileInformation.json")!=0){
				//Set File Name
				json_object_set_new(fileObject,"name",json_string(dir->d_name));
				//Set File Size
				fileSize = getFileSize(filePath);
				json_object_set_new(fileObject,"size",json_integer(fileSize));
				//Set File CRC32 Value
				fileCRC32Value = hashCRC(filePath);
				json_object_set_new(fileObject,"crc",json_integer(fileCRC32Value));
				//Set File Date & Time
				getFileDateTime(fileDateTime,filePath);
				fileEpochSec = convertEpoch(fileDateTime);
				json_object_set_new(fileObject,"epoch seconds",json_integer(fileEpochSec));
				json_array_append(jArray,fileObject);
			}
		}
	}
	closedir(d);
	return fileInfo;		
}

void writeJsonIntoFile(const char *jsonFile,json_t *jsonObject){
	FILE *fptr = NULL;
	fptr = fopen(jsonFile,"w");
	json_dumpf(jsonObject,fptr,100);
	json_decref(jsonObject);
	
	fclose(fptr);
}

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
		getFileDateTime(fileDate,fileNamePath);
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
