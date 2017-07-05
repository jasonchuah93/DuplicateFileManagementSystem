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
};

Node *createNode(json_t *fileObjectSize,json_t *fileObjectCRC);

#endif // Node_H
