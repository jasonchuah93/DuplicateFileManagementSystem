#ifndef Node_H
#define Node_H

#define getNameFromNode(node) ((FileInfo*)((Node*)node)->data)->fileName
#define getSizeFromNode(node) ((FileInfo*)((Node*)node)->data)->fileSize
#define getCRCFromNode(node) ((FileInfo*)((Node*)node)->data)->fileCRC32Value
#define getNamefromList(node) ((FileInfo*)((LinkedList*)((Node*)node)->data)->head->data)->fileName
#define getSizefromList(node) ((FileInfo*)((LinkedList*)((Node*)node)->data)->head->data)->fileSize
#define getLinkedListLength(node) ((LinkedList*)node->data)->length   
#define fileInfoFromErrorNode ((Node*)errNode->data)->data 
#define linkedListFromNode ((LinkedList*)removedNode->data)

typedef struct Node Node;
struct Node {
 Node *left;
 Node *right;
 char color; // 'b' or 'r'(black or red)
 void *data;
};

Node *createNode(void *fileInfo);

#endif // Node_H
