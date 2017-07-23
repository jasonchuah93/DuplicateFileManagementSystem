#ifndef Node_H
#define Node_H

#define getName(node) ((FileInfo*)((LinkedList*)((Node*)(node))->data)->head->data)->fileName
#define getSize(node) ((FileInfo*)((LinkedList*)((Node*)(node))->data)->head->data)->fileSize
#define getCRC(node) ((FileInfo*)((LinkedList*)((Node*)(node))->data)->head->data)->fileCRC32Value

typedef struct Node Node;
struct Node {
 Node *left;
 Node *right;
 char color; // 'b' or 'r'(black or red)
 void *data;
};

Node *createNode(void *list);

#endif // Node_H
