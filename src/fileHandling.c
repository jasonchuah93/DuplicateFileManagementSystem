#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <malloc.h>
#include "generateCRC32Value.h"
#include "fileInfo.h"
#include "jansson.h"
#include "JSON.h"
#include "compareFileInfo.h"
#include "LinkedList.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "errorNode.h"
#include "CException.h"
#include "fileHandling.h"

struct stat attr;
struct dirent *dir;
struct tm t;

void summariseFolder(Node **dupRoot){
	int i = 0;
	Node *removedNode = NULL;
	Element *removedEle = NULL;
	if(*dupRoot !=NULL){
		printf("The following files are duplicated\n");
		while(*dupRoot!=NULL){
			removedNode = removeFileNode(dupRoot,*dupRoot);
			for(i=0;i<((LinkedList*)removedNode->data)->length;i=i){
				removedEle = listRemoveFirst(((LinkedList*)removedNode->data));
				printf("%s\n",getEleName(removedEle));
			}
			printf("---------------------------------------\n");
		}
	}
}

void traverseFolder(Node **duplicatedFileRoot,const char *folderName){
	Node *root = NULL;
	_traverseFolder(&root,duplicatedFileRoot,folderName);
	
}

void _traverseFolder(Node **root,Node **duplicatedRoot,const char *folderName){
	char subFolderPath[100] = {0};
	DIR *d = opendir(folderName);
	while((dir = readdir(d)) != NULL){
		if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			sprintf(subFolderPath,"%s/%s",folderName,dir->d_name);
			_traverseFolder(root,duplicatedRoot,subFolderPath);
		}
	}
	scanFolder(root,duplicatedRoot,folderName);
	closedir(d);
}

void scanFolder(Node **nodeRoot, Node **duplicatedFileRoot,const char *folderName){
	int arrayCounter = 0;
	size_t arraySize = 0;
	char jsonFilePath[100] = {0}, getErrorFilePath[100] = {0}, getDuplicateFilePath[100] = {0};
	json_t *folderObj = NULL, *folderArray = NULL;
	FileInfo *info = NULL;
	Node *fileNode = NULL, *linkedListNode = NULL;
	Error *errNode = NULL;
	Element *errElement = NULL, *duplicatedFileElement = NULL, *similarErrElement = NULL;
	LinkedList *duplicatedFileList = NULL;
	sprintf(jsonFilePath,"%s/%s",folderName,"fileInformation.json");
	if(checkJsonFileExistInFolder(folderName,"fileInformation.json") == 1){
		folderObj = updateJsonFolderObject(folderName,"fileInformation.json");
		deleteFile(jsonFilePath);
	}else{
		folderObj = createJsonFolderObject(folderName);
	}
	folderArray = goIntoJsonArrayFrmFolderObj(folderObj);
	arraySize = json_array_size(folderArray);
	for(arrayCounter=0;arrayCounter<arraySize;arrayCounter++){
		info = initInfo();
		getFileInfoFromJsonObject(folderArray,info,arrayCounter);
		fileNode = createNode(info);
		Try{
			addFileNode(nodeRoot,fileNode);
		}Catch(errNode){ //Error Node is the node copy from 1st RBT which is similar with the node trying to add to the 1st RBT
			sprintf(getErrorFilePath,"%s/%s",folderName,getNameInErr(errNode));
			sprintf(getDuplicateFilePath,"%s/%s",folderName,getNameFromNode(fileNode));
			if(compareFileByte(getErrorFilePath,getDuplicateFilePath) == 1){
				errElement = createElement(fileInfoFromErrorNode);
				duplicatedFileElement = createElement(fileNode->data);
				if(similarErrElement == NULL){
					similarErrElement = errElement;
					duplicatedFileList = createLinkedList();
					if(duplicatedFileList->head == NULL){
						listAddFirst(errElement,duplicatedFileList);
						listAddFirst(duplicatedFileElement,duplicatedFileList);
					}
				}else{
					if(strcmp(getEleName(similarErrElement),getEleName(errElement)) == 0){
						listAddFirst(duplicatedFileElement,duplicatedFileList);
					}else{
						duplicatedFileList = createLinkedList();
						if(duplicatedFileList->head == NULL){
							listAddFirst(errElement,duplicatedFileList);
							listAddFirst(duplicatedFileElement,duplicatedFileList);
						}
					}
				}
				linkedListNode = createNode(duplicatedFileList);
				addListNode(duplicatedFileRoot,linkedListNode);	
			}
		}
	}
	if(checkFileNumberInFolder(folderName) != 0){
		writeJsonObjectIntoFile(jsonFilePath,folderObj);
	}
}

char *duplicateFileForTesting(char *fileToDuplicate, char *number){
	int ch = 0;
	char tempNum[10] = {0}, tempDot[10] = {0}, tempDuplicateFileName[100] = {0};
	char folderName[100] = {0};
	char *lookForDot = NULL, *getFolderName = NULL, *getFileName = NULL, *duplicateFileName = NULL;
	FILE *fPtr = fopen(fileToDuplicate,"r+"); 
	FILE *duplicatePtr = NULL;
	if(fPtr == NULL)
		Throw((Error*)ERR_FILE_NOT_OPEN);
	else{
		strcpy(folderName,fileToDuplicate);
		lookForDot = strrchr(fileToDuplicate,'.');
		strcpy(tempNum,number);
		strcpy(tempDot,lookForDot);
		strcat(tempNum,tempDot);
		strncpy(tempDuplicateFileName,fileToDuplicate,26);
		strcat(tempDuplicateFileName,tempNum);
		duplicateFileName = (char*)malloc(strlen(tempDuplicateFileName)+1);
		strcpy(duplicateFileName,tempDuplicateFileName);
		duplicatePtr = fopen(duplicateFileName,"w+");
		while((ch = fgetc(fPtr))!=EOF)
			fputc(ch,duplicatePtr);
	}
	fclose(duplicatePtr);
	fclose(fPtr);
	return duplicateFileName;
}

void deleteFile(char *filePathToDelete){
	if(filePathToDelete == NULL)
		Throw((Error*)ERR_FILE_NO_EXIST);
	else
		remove(filePathToDelete);
}

char *createFileForTesting(char *folderName,char *fileName,int size){
	int counter = 0;
	char *filePath = (char*)malloc(strlen(folderName)+strlen(fileName)+1);
	time_t t; 
	sprintf(filePath,"%s/%s",folderName,fileName);
	FILE *fPtr = NULL;
	DIR *dPtr = opendir(folderName);
	while((dir = readdir(dPtr)) != NULL){
		if(dir->d_type == DT_REG){
			if(strcmp(dir->d_name,"fileInformation.json")!=0){
				if(strcmp(fileName,dir->d_name) == 0){
					break;
				}else{
					fPtr = fopen(filePath,"w+");
					srand((unsigned)time(&t));
					for(counter=0;counter<size;counter++){
						fprintf(fPtr,"%d\n",rand()%1000);
					}
				}
			}
		}
	}
	fclose(fPtr);
	closedir(dPtr);
	return filePath;
}

/*************************************************************
* Check the total number of file in folder 
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: count		number of file inside a folder 
*			
*	Destroy: none
**************************************************************/

int checkFileNumberInFolder(const char *folderName){
	int count = 0;
	DIR *dPtr = opendir(folderName);
	while((dir=readdir(dPtr))!=NULL){
		if(dir->d_type == DT_REG){
			if(strcmp(dir->d_name,"fileInformation.json")!=0)
				count++;
		}
	}
	closedir(dPtr);
	return count;
}

/*************************************************************
* Call getFileDateTime & convertEpoch into this function
*
*	Input: 	 dateTime       Initially is NULL
*			 filepath		the path of the file we want to get the time

*	Output:  epochSecs		date and time of the file 
*			
*	Destroy: none
**************************************************************/

int getFileEpoch(char *filePath){
	unsigned long int epochSecs = 0;
	char dateTime[50] = {0};
	getFileDateTime(dateTime,filePath);
	epochSecs = convertEpoch(dateTime);
	return epochSecs;
}

/*************************************************************
* Check the last modified date & time of the file 
*
*	Input: 	 dateTime       Initially is NULL
*			 path			the path of the file we want to check  

*	Output:  dateTimes		date and time of the file 
*			
*	Destroy: none
**************************************************************/

int getFileDateTime(char *dateTime,char *path){
	char times[50]={0};
	time_t t = time(NULL);
	stat(path, &attr);
	strftime(times,20,"%Y/%m/%d %H:%M:%S",localtime(&(attr.st_mtime)));
	strcpy(dateTime,times);
}

/*************************************************************
* Convert date and time of given file to epoch format
*
*	Input: 	 dateTime       Initially is NULL
*
*	Output:  epochSecs		date and time of the file in epoch format
*			
*	Destroy: none
**************************************************************/

int convertEpoch(char *fileDateTime){
	unsigned long int epochSecs = 0;
	time_t epoch = 0;
	char year[5] = {0},month[5] = {0},day[5] = {0};
	char hr[5] = {0},min[5] = {0},sec[5] = {0};
	int yearVal = 0,monthVal = 0,dayVal = 0;
	int hrVal = 0,minVal = 0,secVal = 0;
	strncpy(year,fileDateTime,4);strncpy(month,fileDateTime+5,2);strncpy(day,fileDateTime+8,2);
	strncpy(hr,fileDateTime+11,2);strncpy(min,fileDateTime+14,2);strncpy(sec,fileDateTime+17,2);
	yearVal = atoi(year);monthVal = atoi(month);dayVal = atoi(day);
	hrVal = atoi(hr);minVal = atoi(min);secVal = atoi(sec);
	t.tm_year  = yearVal-1900;
	t.tm_mon   = monthVal-1;           
    t.tm_mday  = dayVal;
    t.tm_hour  = hrVal;
    t.tm_min   = minVal;
    t.tm_sec   = secVal;
    t.tm_isdst = -1; 
	epoch = mktime(&t);
	epochSecs = (unsigned long int)epoch;
	return epochSecs;
}

/*************************************************************
* Check the size of a given file
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: size		size of the file 
*			
*	Destroy: none
**************************************************************/

int getFileSize(const char *path){
	int size = 0;
	FILE *fPtr = fopen(path,"r");
	fseek(fPtr,0,SEEK_END);    
	size = ftell(fPtr);   
	fclose(fPtr);
    return size;
}


/*


void deleteAllContentInFolder(char *folderPath){
	int i=0,check = 0;
	char filePath[100] = {0}, subPath[100] = {0};
	DIR *dPtr = opendir(folderPath);
	while((dir=readdir(dPtr))!=NULL){
		if(dir->d_type == DT_REG){
			sprintf(filePath,"%s/%s",folderPath,dir->d_name);
			remove(filePath);
		}else if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			sprintf(subPath,"%s/%s",folderPath,dir->d_name);
			deleteAllContentInFolder(subPath);
			rmdir(subPath);
		}
	}
	closedir(dPtr);
}

*/



