#ifndef compareJSON_H
#define compareJSON_H

#include "Node.h"

int compareList(Node **sizeFromElement, Node *sizeToCompare);
int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare);
int compareFileCRC(Node **crcFromRBT,Node *crcToCompare);
int compareFileByte(char *rootFile,char *fileToCompare);

#endif // compareJSON_H
