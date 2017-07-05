#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"
#include "compareJSON.h"

//Make these define for easy programming
#define addFile(rootPtr,newNode) genericAddRedBlackTree(rootPtr,newNode,compareFileSize)
#define leftChild (*rootPtr)->left
#define rightChild (*rootPtr)->right
#define leftGrandChild (*rootPtr)->left->left
#define rightGrandChild (*rootPtr)->right->right
#define leftRightGrandChild (*rootPtr)->left->right
#define rightLeftGrandChild (*rootPtr)->right->left

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareFileSize)(Node **rootPtr,Node *newNode));
void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareRecord)(Node **rootPtr,Node *newNode));
void handleColor(Node **rootPtr,Node *deleteNode);
Node *removeNextLargerSuccessor(Node **rootPtr);

#endif // redBlackTree_H
