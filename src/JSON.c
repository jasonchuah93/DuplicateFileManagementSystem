#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include "JSON.h"
#include "generateCRC32Value.h"
#include "Node.h"
#include "errorNode.h"
#include "compareJSON.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "CException.h"

struct dirent *dir = NULL;
/*
FileInfo *createInfo(){
	FileInfo *info = malloc(sizeof(FileInfo));
	info->fileName = NULL;
	info->fileSize = 0;
	info->fileCRC32Value = 0;
	return info;
}

json_t *updateJson(const char *folderPath, const char *jsonFile){
	int countArray = 0,i = 0;
	char jsonPath[100] = {0}, filePath[100] = {0}, subFolderPath[100] = {0}, filePath2[100] = {0};
	size_t arraySize = 0;
	unsigned long int fileEpochSec = 0, fileCRC32Value =0;
	unsigned long long int fileSize = 0;
	char *updatedJsonPath = NULL;
	json_t *loadObj = NULL, *loadArray = NULL, *fileObj = NULL;
	json_t *objName = NULL, *objEpoch = NULL;
	json_t *newObj = json_object();
	json_t *updateObj = json_object();
	json_error_t objError;
	DIR *dPtr = getFolderPtr(folderPath);
	int fileNum = checkFileNumber(folderPath);
	sprintf(jsonPath,"%s/%s",folderPath,jsonFile);
	loadObj = json_load_file(jsonPath,0,&objError);
	loadArray = getJsonArrayFrmFolderObj(loadObj);
	arraySize = json_array_size(loadArray);
	while((dir = readdir(dPtr))!=NULL){
		if(dir->d_type == DT_REG){
			if(strcmp(dir->d_name,"fileInformation.json")!=0){
				sprintf(filePath,"%s/%s",folderPath,dir->d_name);
				//fileSize = getFileSize(filePath);
				//fileCRC32Value = hashCRC(filePath);
				//fileEpochSec = getFileEpoch(filePath);		
				fileObj = json_array_get(loadArray,countArray);
				if(json_is_object(fileObj)){
					objName = json_object_get(fileObj,"name");
					if(strcmp(json_string_value(objName),dir->d_name) == 0){
						fileEpochSec = getFileEpoch(filePath);
						objEpoch = json_object_get(fileObj,"epoch seconds");
						if(fileEpochSec > json_integer_value(objEpoch)){
							fileSize = getFileSize(filePath);
							fileCRC32Value = hashCRC(filePath);
							json_object_set_new(fileObj,"size",json_integer(fileSize));
							json_object_set_new(fileObj,"crc",json_integer(fileCRC32Value));
							json_object_set_new(fileObj,"epoch seconds",json_integer(fileEpochSec));
							writeJsonIntoFile(jsonPath,loadObj);
						}
						
					}		
				}
				countArray++;
			}
		}else if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			sprintf(subFolderPath,"%s/%s",folderPath,dir->d_name);
			updateJson(subFolderPath,jsonFile);
		}
	}
	if(countArray != arraySize){
		fileObj = createJsonObjectFrmFolder(folderPath);
		writeJsonIntoFile(jsonPath,fileObj);
	}
	closedir(dPtr);		
	//return fileObj;
}

void getFileInfoFrmJson(json_t *fileArray,FileInfo *fptr,int counter){
	void *iter = NULL;
	json_t *fileObject = NULL;
	json_t *objName = NULL;
	json_t *objSize = NULL;
	json_t *objCRC = NULL;
	if(json_is_array(fileArray)){
		fileObject = json_array_get(fileArray,counter);
		if(json_is_object(fileObject)){
			//Get file name put into fptr
			objName = json_object_get(fileObject,"name");
			if(json_is_string(objName)){
				fptr->fileName = json_string_value(objName);
				//printf("file name in ptr: %s\n",fptr->fileName);	
			}else
				Throw((Error*)ERR_NOT_STRING_OBJECT);
			//Get file size put into fptr
			objSize = json_object_get(fileObject,"size");
			if(json_is_integer(objSize)){
				fptr->fileSize = json_integer_value(objSize);
				//printf("file size in ptr: %llu\n",fptr->fileSize);	
			}else
				Throw((Error*)ERR_NOT_INTEGER_OBJECT);
			//Get file crc put into fptr
			objCRC = json_object_get(fileObject,"crc");
			if(json_is_integer(objCRC)){
				fptr->fileCRC32Value = json_integer_value(objCRC);
				//printf("file crc in ptr: %lu\n",fptr->fileCRC32Value);	
			}else
				Throw((Error*)ERR_NOT_INTEGER_OBJECT);
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

int checkJsonFile(const char *folder, const char *jsonFile){
	int cmp = 0;
	DIR *dPtr = opendir(folder);
	while((dir = readdir(dPtr))!=NULL){
		if(strcmp(dir->d_name,jsonFile) == 0){
			//printf("file name: %s\n",dir->d_name);
			return 0;
		}
	}
	return -1;
}

int checkFileLaterThanJson(const char *folder,char *jsonFile){
	unsigned long int currentSec = 0, previousSec = 0;
	DIR *dPtr = getFolderPtr(folder);
	char dateTime[100] = {0}, filePath[200] = {0}, newFilePath[200] = {0};
	
	while((dir = readdir(dPtr))!=NULL){
		if(dir->d_type == DT_REG){
			sprintf(filePath,"%s/%s",folder,dir->d_name);
			getFileDateTime(dateTime,filePath);
			currentSec = convertEpoch(dateTime);
			if(currentSec > previousSec){
				strcpy(newFilePath,dir->d_name);
				previousSec = currentSec;
			}
		}
	}
	if(strcmp(newFilePath,jsonFile)==0){
		//printf("JSON File is latest at %s\n",folder);
		return 0 ;
	}else
		return 1;
	
	closedir(dPtr);
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

int delJSONFile(const char *JSONfile){
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
*/