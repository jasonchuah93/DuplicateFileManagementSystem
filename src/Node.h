#ifndef Node_H
#define Node_H

#include "JSON.h"

#define getFileName(nodePtr) ((FileInfo*)(nodePtr->data))->fileName
#define getFileSize(nodePtr) ((FileInfo*)(nodePtr->data))->fileSize
#define getFileCRC(nodePtr) ((FileInfo*)(nodePtr->data))->fileCRC32Value

typedef struct Node Node;
struct Node {
 Node *left;
 Node *right;
 char color; // 'b' or 'r'(black or red)
 void *data;
};

Node *createNode(FileInfo *fileInfo);

#endif // Node_H
