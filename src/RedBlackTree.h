#ifndef RedBlackTree_H
#define RedBlackTree_H

void handleColor(Node **rootPtr,Node *deleteNode);
void addRedBlackTree(Node **rootPtr,Node *deleteNode);
Node *delRedBlackTree(Node **rootPtr,Node *deleteNode);
Node *removeNextLargerSuccessor(Node **parentPtr);

#endif // RedBlackTree_H

