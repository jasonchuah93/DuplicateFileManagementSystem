#ifndef compareJSON_H
#define compareJSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "fileHandling.h"
#include "Node.h"
#include "errorNode.h"

#define getFileSize(node) (((Node*)node)->fileSize)
#define getFileCrc(node)  (((Node*)node)->crc32Value)
#define getFilePathLocationFrmErr(errorNode)  (((Node*)((Error*)(errorNode))->data)->pathName)
#define getFilePathLocationFrmNode(node)  (((Node*)node)->pathName)

int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare);
int compareFileCRC(Node **crcFromRBT,Node *crcToCompare);
int compareFileByte(Error *nodeFromRBT,Node *nodeToCompare);

#endif // compareJSON_H
