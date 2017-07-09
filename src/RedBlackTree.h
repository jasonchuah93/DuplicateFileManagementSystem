#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"
#include "errorNode.h"
#include "compareJSON.h"
#include "Rotation.h"
#include "compareJSON.h"
#include "RedBlackTree.h"
#include "RestructureNode.h"
#include <malloc.h>

//Make these define for easy programming
#define addFile(rootPtr,newNode) genericAddRedBlackTree(rootPtr,newNode,compareFileSize)
#define removeFile(rootPtr,delNode) genericDelRedBlackTree(rootPtr,delNode,compareFileSize)
#define leftChild (*rootPtr)->left
#define rightChild (*rootPtr)->right
#define leftGrandChild (*rootPtr)->left->left
#define rightGrandChild (*rootPtr)->right->right
#define leftRightGrandChild (*rootPtr)->left->right
#define rightLeftGrandChild (*rootPtr)->right->left

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareFileSize)(Node **rootPtr,Node *newNode));
void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareRecord)(Node **rootPtr,Node *newNode));
Node *genericDelRedBlackTree(Node **rootPtr,Node *delNode, int(*compareFileSize)(Node **rootPtr,Node *delNode));
Node *_genericDelRedBlackTree(Node **rootPtr,Node *delNode, int(*compareRecord)(Node **rootPtr,Node *delNode));
void handleColor(Node **rootPtr,Node *deleteNode);
Node *removeNextLargerSuccessor(Node **rootPtr);

#endif // redBlackTree_H
