#include <string.h>
#include <malloc.h>
#include <dirent.h>
#include "fileInfo.h"
#include "generateCRC32Value.h"
#include "fileHandling.h"
#include "errorNode.h"
#include "CException.h"
#include "JSON.h"

struct dirent *dir = NULL;

json_t *updateJsonFolderObject(const char *folderName, const char *jsonFile){
	int countArraySize = 0, numOfFileInFolder = 0;
	unsigned long long int fileSize = 0;
	unsigned long int jsonFileEpoch = 0, otherFileEpoch = 0, fileCRC =0;
	char jsonFilePath[100] = {0}, otherFilePath[100] = {0}, fileToUpdate[100] = {0};
	json_error_t objError;
	json_t *loadedObj = NULL, *loadedArray = NULL, *fileObj = NULL;
	json_t *objName = NULL, *objSize = NULL, *objCRC = NULL, *objEpoch = NULL;
	json_t *updatedObj = json_object();
	numOfFileInFolder = checkFileNumberInFolder(folderName);
	DIR *dPtr = opendir(folderName);
	sprintf(jsonFilePath,"%s/%s",folderName,jsonFile);
	loadedObj = json_load_file(jsonFilePath,0,&objError);
	loadedArray = goIntoJsonArrayFrmFolderObj(loadedObj);
	size_t arraySize = json_array_size(loadedArray);
	while((dir = readdir(dPtr))!=NULL){
		if(dir->d_type == DT_REG){
			if(strcmp("fileInformation.json",dir->d_name) != 0){
				sprintf(otherFilePath,"%s/%s",folderName,dir->d_name);
				otherFileEpoch = getFileEpoch(otherFilePath);
				fileObj = json_array_get(loadedArray,countArraySize);
				if(json_is_object(fileObj)){
					objName = json_object_get(fileObj,"name");
					objEpoch = json_object_get(fileObj,"epoch");
					countArraySize++;						
				}
				if(numOfFileInFolder == arraySize){
					if(otherFileEpoch > json_integer_value(objEpoch)){
						printf("file: %s\n",dir->d_name);
						fileSize = getFileSize(otherFilePath);
						fileCRC = hashCRC(otherFilePath);
						json_object_set_new(updatedObj,"name",json_string(otherFilePath));
						json_object_set_new(updatedObj,"size",json_integer(fileSize));
						json_object_set_new(updatedObj,"crc",json_integer(fileCRC));
						json_object_set_new(updatedObj,"epoch",json_integer(otherFileEpoch));
						json_object_update_existing(fileObj,updatedObj);
					}
				}else{
					loadedObj = createJsonFolderObject(folderName);
				}
			}
		}
	}
	closedir(dPtr);		
	return loadedObj;
}

int checkFilesLatestThanJson(const char *folderName,char *jsonFile){
	unsigned long int currentTime = 0, previousTime = 0;
	DIR *dPtr = opendir(folderName);
	char currentfilePath[200] = {0};
	char *latestFilePath = NULL;
	
	while((dir = readdir(dPtr))!=NULL){
		if(dir->d_type == DT_REG){
			sprintf(currentfilePath,"%s/%s",folderName,dir->d_name);
			currentTime = getFileEpoch(currentfilePath);
			if(currentTime > previousTime){
				latestFilePath = (char *)malloc(strlen(dir->d_name)+1);
				strcpy(latestFilePath,dir->d_name);
				previousTime = currentTime;
			}
		}
	}
	if(strcmp(latestFilePath,jsonFile)==0){
		closedir(dPtr);
		return 1;
	}else{
		closedir(dPtr);
		return -1;
	}
}

void writeJsonObjectIntoFile(const char *jsonFile,json_t *jsonObject){
	FILE *fptr = fopen(jsonFile,"w");
	json_dumpf(jsonObject,fptr,100);
	fclose(fptr);
}

void getFileInfoFromJsonObject(json_t *fileArray,FileInfo *fptr,int counter){
	json_t *fileObject = NULL, *objName = NULL, *objSize = NULL, *objCRC = NULL;
	if(json_is_array(fileArray)){
		fileObject = json_array_get(fileArray,counter);
		if(json_is_object(fileObject)){
			if(objName = json_object_get(fileObject,"name")){
				//Get file name put into fptr	
				if(json_is_string(objName))
					fptr->fileName = json_string_value(objName);
				else
					Throw((Error*)ERR_NOT_STRING_OBJECT);
			}
			if(objSize = json_object_get(fileObject,"size")){
				//Get file size put into fptr
				if(json_is_integer(objSize))
					fptr->fileSize = json_integer_value(objSize);
				else
					Throw((Error*)ERR_NOT_INTEGER_OBJECT);
			}
			if(objCRC = json_object_get(fileObject,"crc")){
				//Get file crc put into fptr
				if(json_is_integer(objCRC))
					fptr->fileCRC32Value = json_integer_value(objCRC);
				else
					Throw((Error*)ERR_NOT_INTEGER_OBJECT);
			}
		}else
			Throw((Error*)ERR_NOT_JSON_OBJECT);
	}else
		Throw((Error*)ERR_NOT_JSON_ARRAY);
}

json_t *createJsonFolderObject(const char *folderPath){
	unsigned long long int fileSize = 0;
	unsigned long int fileCRC32Value = 0, fileEpochSec = 0;
	char fileName[100] = {0}, fileDateTime[50] = {0};
	DIR *dPtr = opendir(folderPath);
	json_t *fileInfo = json_object();
	json_t *jArray = json_array();
	json_object_set_new(fileInfo,"File Info",jArray);
	while((dir = readdir(dPtr))!=NULL){
		json_t *fileObject = json_object();
		sprintf(fileName,"%s/%s",folderPath,dir->d_name);
		if(dir->d_type == DT_REG){
			if(strcmp(dir->d_name,"fileInformation.json")!=0){
				//Set File Name
				json_object_set_new(fileObject,"name",json_string(fileName));
				//Set File Size
				fileSize = getFileSize(fileName);
				json_object_set_new(fileObject,"size",json_integer(fileSize));
				//Set File CRC32 Value
				fileCRC32Value = hashCRC(fileName);
				json_object_set_new(fileObject,"crc",json_integer(fileCRC32Value));
				//Set File Last Modified Date & Time
				fileEpochSec = getFileEpoch(fileName);
				json_object_set_new(fileObject,"epoch",json_integer(fileEpochSec));
				json_array_append(jArray,fileObject);
			}
		}
	}
	closedir(dPtr);
	return fileInfo;		
}

json_t *goIntoJsonArrayFrmFolderObj(json_t *folderObject){
	json_t *folderArray = NULL;
	if(json_is_object(folderObject)){
		void *iter = json_object_iter(folderObject);
		folderArray = json_object_iter_value(iter);
	}else
		Throw((Error*)ERR_NOT_JSON_OBJECT);
	return folderArray;
}

int checkJsonFileExistInFolder(const char *folder, const char *jsonFile){
	DIR *dPtr = opendir(folder);
	while((dir = readdir(dPtr))!=NULL){
			if(strcmp(dir->d_name,jsonFile) == 0){
				closedir(dPtr);
				return 1;
			}	
	}
	closedir(dPtr);
	return -1;
}

int checkJsonTypeFile(const char *jsonFilePath){
	const char ext = '.';
	char *jsonExt = strrchr(jsonFilePath,ext);
	if(strcmp(jsonExt,".json") == 0)
		return 1;
	else
		return 0;
}
