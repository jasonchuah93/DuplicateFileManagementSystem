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
#include "main.h"

void mainProgram(const char *folderName){
	Node *duplicatedFileRoot = NULL;
	traverseFolder(&duplicatedFileRoot,folderName);
	summariseFolder(&duplicatedFileRoot);
}


