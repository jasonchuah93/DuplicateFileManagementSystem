#ifndef Node_H
#define Node_H

#define createRBTNode(fileObjectName,fileObjectSize,fileObjectCRC) createNodeWithFileInfo(fileObjectName,fileObjectSize,fileObjectCRC)

typedef struct Node Node;
struct Node {
 Node *left;
 Node *right;
 char color; // 'b' or 'r'(black or red)
 unsigned long long int fileSize;
 unsigned long int crc32Value;
 const char *pathName;
};

Node *createNode();
Node *createNodeWithFileInfo();

#endif // Node_H
