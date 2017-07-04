#ifndef compareJSON_H
#define compareJSON_H

#include "Node.h"

#define getFileSize(node) ((Node*)node)->fileSize)

int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare);
int compareFileCRC(Node **sizeFromRBT,Node *sizeToCompare);

#endif // compareJSON_H
