#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"

#define addFileNode(rootPtr,newNode) genericAddRedBlackTree(rootPtr,newNode,compareFileSize)
#define removeFileNode(rootPtr,delNode) genericDelRedBlackTree(rootPtr,delNode,compareFileSize)

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareFileSize)(Node **rootPtr,Node *newNode));
void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareRecord)(Node **rootPtr,Node *newNode));
Node *genericDelRedBlackTree(Node **rootPtr,Node *delNode, int(*compareFileSize)(Node **rootPtr,Node *delNode));
Node *_genericDelRedBlackTree(Node **rootPtr,Node *delNode, int(*compareRecord)(Node **rootPtr,Node *delNode));
void handleColor(Node **rootPtr,Node *deleteNode);
Node *removeNextLargerSuccessor(Node **rootPtr);

#endif // redBlackTree_H
