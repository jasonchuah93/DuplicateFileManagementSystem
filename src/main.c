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
#include "jansson.h"
#include "LinkedList.h"
#include "main.h"
#include "CException.h"

int scanFolder(const char *folderName){
	
	int cmpFileByte = 0, checkFileNum = 0, i = 0;
	char *jsonPath = NULL, *errNodeFilePath = NULL, *targetNodeFilePath = NULL;
	json_t *folderObj = NULL;
	json_t *fileArray = NULL;
	Element *fileElement = NULL;
	Node *fileNode = NULL;
	Node *nodeRoot = NULL;
	Error *errNode = NULL;
	
	checkFileNum = listFileNumber(folderName);
	folderObj = createJsonObjectFrmFolder(folderName);
	fileArray = getJsonArrayFrmFolderObj(folderObj);
	//Check is there any json file inside the folder
	if(checkJsonFile(folderName,"fileInformation.json")==0)
		printf("json file exist in folder\n");
	//UpdateJSON here
	else{
		printf("json file no exist in folder\n");
		jsonPath = createJSONFilePath(folderName);
		writeJsonIntoFile(jsonPath,folderObj);
	}
	for(i=0;i<checkFileNum;i=i+1){
		FileInfo *information = createInfo();
		LinkedList *list = createLinkedList();
		getFileInfoFrmJson(fileArray,information,i);
		fileElement = createElement(information);
		listAddFirst(fileElement,list);
		fileNode = createNode(list);
		Try{
			addFileNode(&nodeRoot,fileNode);
		}Catch(errNode){
			errNodeFilePath = addFolderPathToFilePath(folderName,getNameInErr(errNode));
			targetNodeFilePath = addFolderPathToFilePath(folderName,getName(fileNode));
			cmpFileByte = compareFileByte(errNodeFilePath,targetNodeFilePath);
			if(cmpFileByte == 0){
				printf("%s & %s are duplicated files\n",errNodeFilePath,targetNodeFilePath);
			}
		}
	}
}