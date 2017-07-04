#ifndef compareJSON_H
#define compareJSON_H

#include "Node.h"

#define getFileSize(node) (((Node*)node)->fileSize)
#define getFileCrc(node)  (((Node*)node)->crc32Value)

int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare);
int compareFileCRC(Node **crcFromRBT,Node *crcToCompare);

#endif // compareJSON_H
