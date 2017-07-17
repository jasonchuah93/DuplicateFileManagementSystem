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
#include "main.h"
#include "CException.h"

int scanFolder(const char *folderName){
	json_t *fileObj = createJsonObject(folderName);
	char *jsonPath = createJSONFilePath(folderName);
	writeJsonIntoFile(jsonPath,fileObj);
}