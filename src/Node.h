#ifndef Node_H
#define Node_H

#define getName(node) (((FileInfo*)((Node*)(node))->data))->fileName
#define getSize(node) (((FileInfo*)((Node*)(node))->data))->fileSize
#define getCRC(node) (((FileInfo*)((Node*)(node))->data))->fileCRC32Value

typedef struct Node Node;
struct Node {
 Node *left;
 Node *right;
 char color; // 'b' or 'r'(black or red)
 void *data;
};

Node *createNode(void *fileInfo);

#endif // Node_H
