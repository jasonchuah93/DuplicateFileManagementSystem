#ifndef compareFileInfo_H
#define compareFileInfo_H

#include "Node.h"

int compareLinkedListSize(Node **sizeFromElement, Node *sizeToCompare);
int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare);
int compareFileCRC(Node **crcFromRBT,Node *crcToCompare);
int compareFileByte(char *rootFile,char *fileToCompare);

#endif // compareFileInfo_H
