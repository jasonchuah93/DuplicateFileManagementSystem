#ifndef Node_H
#define Node_H

#define getName(node) ((FileInfo*)((Element*)node->data)->data)->fileName
#define getSize(node) ((FileInfo*)((Element*)node->data)->data)->fileSize
#define getCRC(node) ((FileInfo*)((Element*)node->data)->data)->fileCRC32Value

typedef struct Node Node;
struct Node {
 Node *left;
 Node *right;
 char color; // 'b' or 'r'(black or red)
 void *data;
};

Node *createNode(void *element);

#endif // Node_H
