#ifndef compareJSON_H
#define compareJSON_H

#include "Node.h"
#include "errorNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define getFileSize(node) (((Node*)node)->fileSize)
#define getFileCrc(node)  (((Node*)node)->crc32Value)
#define getFilePathLocation(errorNode)  (((Node*)((Error*)(errorNode))->data)->pathName)

int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare);
int compareFileCRC(Node **crcFromRBT,Node *crcToCompare);
int compareFilePath(Error *pathFromRBT,Error *pathToCompare);

#endif // compareJSON_H
