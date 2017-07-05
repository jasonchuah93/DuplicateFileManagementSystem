#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"
#include "compareJSON.h"

//Make these define for easy programming
#define addRecord(rootPtr,newNode) genericAddRedBlackTree(rootPtr,newNode,addRecordCompare)
#define removeRecord(rootPtr,delNode) genericDelRedBlackTree(rootPtr,delNode,addRecordCompare)
#define findRecord(rootPtr,targetMemory) genericFindRedBlackTree(rootPtr,targetMemory,findRecordCompare)
#define find(rootPtr,targetMemory) findRedBlackTree(rootPtr,targetMemory,findRecordCompare)
#define leftChild (*rootPtr)->left
#define rightChild (*rootPtr)->right
#define leftGrandChild (*rootPtr)->left->left
#define rightGrandChild (*rootPtr)->right->right
#define leftRightGrandChild (*rootPtr)->left->right
#define rightLeftGrandChild (*rootPtr)->right->left

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*addRecordCompare)(Node **rootPtr,Node *newNode));
void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareRecord)(Node **rootPtr,Node *newNode));

Node *genericDelRedBlackTree(Node **rootPtr,Node *delNode, int(*addRecordCompare)(Node **rootPtr,Node *delNode));
Node *_genericDelRedBlackTree(Node **rootPtr,Node *delNode, int(*compareRecord)(Node **rootPtr,Node *delNode));

Node *genericFindRedBlackTree(Node **rootPtr,void *targetMemory,int(*findRecordCompare)(Node **rootPtr,void *targetMemory));
int findRedBlackTree(Node **rootPtr,void *targetMemory,int(*findRecordCompare)(Node **rootPtr,void *targetMemory));

Node *removeNextLargerSuccessor(Node **rootPtr);

#endif // redBlackTree_H
