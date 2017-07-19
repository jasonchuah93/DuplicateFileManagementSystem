#ifndef compareJSON_H
#define compareJSON_H

#include "Node.h"
#include "JSON.h"
#include "errorNode.h"

#define getFilePathFrmErr(errorNode) (((FileInfo*)((Node*)((Error*)(errorNode))->data)->data))->fileName

int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare);
int compareFileCRC(Node **crcFromRBT,Node *crcToCompare);
int compareFileByte(Error *nodeFromRBT,Node *nodeToCompare);

#endif // compareJSON_H
