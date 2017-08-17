/*
#include "jansson.h"
#include "JSON.h"
#include "fileInfo.h"
#include "generateCRC32Value.h"
#include "errorNode.h"
#include "compareFileInfo.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "LinkedList.h"
#include "CException.h"
#include <unistd.h>
*/
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <malloc.h>
#include "fileHandling.h"

struct stat attr;
struct dirent *dir;
struct tm t;
//static char* lastFile[MaxFile] = {0};
//static int lastFileCount;

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
void summariseFolder(Node **dupRoot){
	int i = 0;
	Node *removedNode = NULL;
	Element *removedEle = NULL;
	removedNode = removeFileNode(dupRoot,*dupRoot);
	if(removedNode != NULL){
		printf("The following files are duplicated\n");
		for(i=0;i<=((LinkedList*)removedNode->data)->length;i++){
			removedEle = listRemoveFirst(((LinkedList*)removedNode->data));
			printf("%s\n",getEleName(removedEle));
		}
		printf("--------------------------------------\n");
	}
}

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

void deleteFile(char *filePathToDelete){
	if(filePathToDelete == NULL)
		Throw((Error*)ERR_FILE_NO_EXIST);
	else
		remove(filePathToDelete);
}

char *duplicateFileForTesting(char *fileToDuplicate, char *number){
	char duplicateFileArray[100] = {0}, numArray[50] = {0}, tempNameArray[50] = {0}, ch;
	char *tempName = NULL, *duplicateFilePath = NULL;
	int bytes = 0;
	FILE *fPtr = fopen(fileToDuplicate,"r+");
	FILE *dupFPtr = NULL;
	if(fPtr == NULL)
		Throw((Error*)ERR_FILE_NOT_OPEN);
	else{
		tempName = strrchr(fileToDuplicate,'.');
		strcpy(numArray,number);
		strcpy(tempNameArray,tempName);
		strcat(numArray,tempNameArray);
		strncpy(duplicateFileArray,fileToDuplicate,26);
		strcat(duplicateFileArray,numArray);
		duplicateFilePath = (char *)malloc(strlen(duplicateFileArray)+1);
		strcpy(duplicateFilePath,duplicateFileArray);
		dupFPtr = fopen(duplicateFilePath,"w+");
		while((ch = fgetc(fPtr))!=EOF)
			fputc(ch,dupFPtr);
	}
	free(duplicateFilePath);
	fclose(fPtr);
	fclose(dupFPtr);
	return duplicateFilePath;
}


*/
/*************************************************************
*   Scan the folder, traverse all content inside
*
*	Input: 	path		the path of the folder we want to scan  
*			
*	Output: size		size of the file 
*			
*	Destroy: none
**************************************************************/
/*
void traverseFolder(Node **duplicatedFileRoot,const char *folderPath){
	Node *root = NULL;
	_traverseFolder(&root,duplicatedFileRoot,folderPath);
}

void _traverseFolder(Node **root,Node **duplicatedRoot,const char *folderPath){
	char subFolderPath[500] = {0};
	scanFolder(root,duplicatedRoot,folderPath);
	DIR *d = getFolderPtr(folderPath);
	while((dir = readdir(d)) != NULL){
		if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			sprintf(subFolderPath,"%s/%s",folderPath,dir->d_name);
			_traverseFolder(root,duplicatedRoot,subFolderPath);
		}
	}
	closedir(d);
}

void scanFolder(Node **nodeRoot, Node **duplicatedFileRoot,const char *folderName){
	int cmpFileByte = 0, i = 0, numOfFiles = 0;
	size_t arraySize = 0;
	char *jsonPath = NULL, *errNodeFilePath = NULL, *targetNodeFilePath = NULL;
	const char *fullJsonPath = NULL;
	json_t *folderObj = NULL, *existingFolderObj = NULL, *updateObj = NULL;
	json_t *fileArray = NULL;
	json_error_t jError;
	Element *fileElementFromErr = NULL, *duplicatedFileEle = NULL, *previousEleFromErr = NULL;
	Node *fileNode = NULL, *listNode = NULL;
	Error *errNode = NULL;
	FileInfo *information = NULL;
	LinkedList *duplicatedList = NULL; 
	folderObj = createJsonObjectFrmFolder(folderName);
	fileArray = getJsonArrayFrmFolderObj(folderObj);
	arraySize = json_array_size(fileArray);
	for(i=0;i<arraySize;i=i+1){
		information = createInfo();
		getFileInfoFrmJson(fileArray,information,i);
		fileNode = createNode(information);
		Try{
			addFileNode(nodeRoot,fileNode);
			//printf("fileNode: %s\n",getName(nodeRoot));
		}Catch(errNode){
			errNodeFilePath = addFolderPathToFilePath(folderName,getNameInErr(errNode));
			targetNodeFilePath = addFolderPathToFilePath(folderName,getName(fileNode));
			cmpFileByte = compareFileByte(errNodeFilePath,targetNodeFilePath);
			if(cmpFileByte == 0){ // 0 means content of 2 files is the same
				fileElementFromErr = createElement(((Node*)errNode->data)->data);
				//printf("current: %s\n",((FileInfo*)fileElementFromErr->data)->fileName);
				if(fileElementFromErr!=NULL && previousEleFromErr == NULL){
					previousEleFromErr = fileElementFromErr;
					duplicatedFileEle = createElement(fileNode->data);
					duplicatedList = createLinkedList();
					if(duplicatedList->head == NULL){
						listAddFirst(fileElementFromErr,duplicatedList);
						listAddFirst(duplicatedFileEle,duplicatedList);
						listNode = createNode(duplicatedList);
						//if(*duplicatedFileRoot == NULL){
							addFileNodeForList(duplicatedFileRoot,listNode);
						//}
					}
				}else if(previousEleFromErr != NULL){
					if(((FileInfo*)previousEleFromErr->data)->fileName == ((FileInfo*)fileElementFromErr->data)->fileName){
						duplicatedFileEle = createElement(fileNode->data);
						listAddFirst(duplicatedFileEle,duplicatedList);
						listNode = createNode(duplicatedList);
						//printf("list data:%s\n",((FileInfo*)duplicatedList->head->data)->fileName);
						//printf("list len: %d\n",duplicatedList->length);
						//printf("next: %s\n",((FileInfo*)duplicatedFileEle->data)->fileName);
					}else{
						duplicatedFileEle = createElement(fileNode->data);
						//printf("current: %s\n",((FileInfo*)duplicatedFileEle->data)->fileName);
						duplicatedList = createLinkedList();
						if(duplicatedList->head == NULL){
							listAddFirst(fileElementFromErr,duplicatedList);
							listAddFirst(duplicatedFileEle,duplicatedList);
							listNode = createNode(duplicatedList);
							addFileNodeForList(duplicatedFileRoot,listNode);
							//printf("list len 2: %d\n",duplicatedList->length);
							//printf("list data:%s\n",((FileInfo*)duplicatedList->head->data)->fileName);
						}
					}
				}
			}
		}
	}
	jsonPath = createJSONFilePath(folderName);
	if(checkJsonFile(folderName,"fileInformation.json")==0){
		updateJson(folderName,"fileInformation.json");
		//writeJsonIntoFile(jsonPath,updateObj);
	}else{
		writeJsonIntoFile(jsonPath,folderObj);
	}
	
	free(duplicatedList);
	free(fileNode);
	free(information);
}




*/



