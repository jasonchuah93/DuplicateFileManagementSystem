#ifndef Node_H
#define Node_H

#define getName(node) ((FileInfo*)((Node*)node)->data)->fileName
#define getSize(node) ((FileInfo*)((Node*)node)->data)->fileSize
#define getCRC(node) ((FileInfo*)((Node*)node)->data)->fileCRC32Value

#define getNamefromList(node) ((FileInfo*)((LinkedList*)((Node*)node)->data)->head->data)->fileName
#define getSizefromList(node) ((FileInfo*)((LinkedList*)((Node*)node)->data)->head->data)->fileSize

typedef struct Node Node;
struct Node {
 Node *left;
 Node *right;
 char color; // 'b' or 'r'(black or red)
 void *data;
};

Node *createNode(void *fileInfo);
Node *initNode();

#endif // Node_H
