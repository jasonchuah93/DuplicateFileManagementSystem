#ifndef Node_H
#define Node_H

#include "JSON.h"
#include "fileHandling.h"
#include "generateCRC32Value.h"

typedef struct Node Node;

struct Node {
 Node *left;
 Node *right;
 char color; // 'b' or 'r'(black or red)
 unsigned long long int fileSize;
 unsigned long int crc32Value;
 const char *pathName;
};

Node *createNode(json_t *fileObjectSize,json_t *fileObjectCRC);
Node *createNodeWithFileInfo(json_t *fileObjectSize,json_t *fileObjectCRC,json_t *fileObjectName);

#endif // Node_H
