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

void mainProgram(const char *folderPath){
	Node *duplicatedFileRoot = NULL;
	//Call traverseAllFolder(duplicatedFileRoot,mainFolder); This function scan all folder
	traverseFolder(&duplicatedFileRoot,folderPath);
	//Call summariesMainFolder(duplicatedFileRoot); This function printf all the duplicated file from root
	summariseFolder(&duplicatedFileRoot);
}


