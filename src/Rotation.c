#include <stdio.h>
#include "Rotation.h"
#include "Node.h"
#include "InitNode.h"

/***
* The following functions below used for addRedBlackTree functions 
* 
***/
void rightRotate(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->left; 
	Node *newRoot = currentRoot->right;
	currentRoot->right=(*nodePtr);
	(*nodePtr)->left = newRoot;
    *nodePtr = currentRoot;
	if(currentRoot->right->left!=NULL || currentRoot->right->right!=NULL){
		currentRoot->right->color='b';
	}else{
		currentRoot->right->color='r';
	}
}

void leftRotate(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->right;
	Node *newRoot = currentRoot->left;
	currentRoot->left=(*nodePtr);
	(*nodePtr)->right = newRoot;
	*nodePtr = currentRoot;
	if(currentRoot->left->left!=NULL || currentRoot->left->right!=NULL){
		currentRoot->left->color='b';
	}else{
		currentRoot->left->color='r';
	}
}

void leftRightRotate(Node **nodePtr){
	Node *currentRoot = *nodePtr;
	leftRotate(&currentRoot->left);
	rightRotate(&(*nodePtr));
}

void rightLeftRotate(Node **nodePtr){
	Node *currentRoot = *nodePtr;
	rightRotate(&currentRoot->right);
	leftRotate(&(*nodePtr));
}

/***
* The following functions below used for delRedBlackTree functions 
* 
***/
void rightRotateVer2(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->left; 
	Node *newRoot = currentRoot->right;
	currentRoot->right=(*nodePtr);
	(*nodePtr)->left = newRoot;
    *nodePtr = currentRoot;
}

void leftRotateVer2(Node **nodePtr){
	Node *currentRoot = (*nodePtr)->right;
	Node *newRoot = currentRoot->left;
	currentRoot->left=(*nodePtr);
	(*nodePtr)->right = newRoot;
	*nodePtr = currentRoot;
}

void leftRightRotateVer2(Node **nodePtr){
	Node *currentRoot = *nodePtr;
	leftRotateVer2(&currentRoot->left);
	rightRotateVer2(&(*nodePtr));
}

void rightLeftRotateVer2(Node **nodePtr){
	Node *currentRoot = *nodePtr;
	rightRotateVer2(&currentRoot->right);
	leftRotateVer2(&(*nodePtr));
}