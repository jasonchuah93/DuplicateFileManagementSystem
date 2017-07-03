#ifndef RestructureNode_H
#define RestructureNode_H

int isNodeBlack(Node **node);
int isNodeRed(Node **node);
int isDoubleNodeBlack(Node *node,Node *removeNode);

void restructureBlackRightWithOneRedChild(Node **nodePtr);
void restructureBlackLeftWithOneRedChild(Node **nodePtr);

void restructureBlackRightWithBlackChildren(Node **nodePtr);
void restructureBlackLeftWithBlackChildren(Node **nodePtr);

void restructureRedRight(Node **nodePtr,Node *delNode);
void restructureRedLeft(Node **nodePtr,Node *delNode);

void restructureBlackRight(Node **nodePtr);
void restructureBlackLeft(Node **nodePtr);

void restructureBlackRightWithBlackChildrenForRedRight(Node **nodePtr);
void restructureBlackLeftWithBlackChildrenForRedLeft(Node **nodePtr);

void restructureRedBlackTree(Node **nodePtr,Node *removeNode);

#endif // RestructureNode_H
