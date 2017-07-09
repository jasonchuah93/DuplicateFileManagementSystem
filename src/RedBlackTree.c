#include <stdio.h>
#include "RedBlackTree.h"
#include "CException.h"

/*********************************************************************
* This function will add a new file info into the red black tree
*
*	Input: 	rootPtr			the root of the tree
*			newNode			the new member of the tree
			compare			pointer to a function to decide the rules to add record
*
*	Destroy: none
*	
**********************************************************************/

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareFileSize)(Node **rootPtr,Node *newNode)){
    _genericAddRedBlackTree(rootPtr,newNode,compareFileSize);    
    (*rootPtr)->color='b';
}

void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareFile)(Node **rootPtr,Node *newNode)){
	int compare = 0;
	Error *duplicatedNode = NULL;
	if(*rootPtr == NULL){
		*rootPtr = newNode;
        (*rootPtr)->color='r';
	}else{
		if ((*rootPtr)->left!=NULL && (*rootPtr)->right!=NULL){
			handleColor(rootPtr,newNode);
		}
		compare = compareFile(rootPtr,newNode);
		if(compare == 1)
			_genericAddRedBlackTree(&(*rootPtr)->left,newNode,compareFile);
		else if(compare == -1)
			_genericAddRedBlackTree(&(*rootPtr)->right,newNode,compareFile);
		else if(compare == 0){
			printf("come in here same crc\n");
			duplicatedNode = createErr(*rootPtr);
			Throw(duplicatedNode);
		}
		if(((*rootPtr)->left!=NULL) && (*rootPtr)->left->left !=NULL){
			if((*rootPtr)->left->color == 'r' && (*rootPtr)->left->left->color == 'r'){
				rightRotate(rootPtr);
				(*rootPtr)->right->color = 'r';
			}
		}else if(((*rootPtr)->left!=NULL) && (*rootPtr)->left->right !=NULL){
			if((*rootPtr)->left->color == 'r' && (*rootPtr)->left->right->color == 'r'){
				leftRightRotate(rootPtr);
				(*rootPtr)->right->color = 'r';
			}
		}else if(((*rootPtr)->right!=NULL) && (*rootPtr)->right->right != NULL){
			if((*rootPtr)->right->color == 'r' && (*rootPtr)->right->right->color == 'r'){
				leftRotate(rootPtr);
				(*rootPtr)->left->color = 'r';
			}
		}else if(((*rootPtr)->right!=NULL) && (*rootPtr)->right->left !=NULL){
			if((*rootPtr)->right->color == 'r' && (*rootPtr)->right->left->color == 'r'){
				rightLeftRotate(rootPtr);
				(*rootPtr)->left->color = 'r';
			}
		}
		if((*rootPtr)->right !=NULL && (*rootPtr)->right->left !=NULL){
			if((*rootPtr)->right->color == 'r' && (*rootPtr)->right->left->color == 'r'){
				(*rootPtr)->right->color = 'b';
				(*rootPtr)->right->left->color = 'r';
				(*rootPtr)->right->right->color = 'r';
			}
		}
		
	}
}

/*********************************************************************
* This function will delete file info in the red black tree
*
*	Input: 	rootPtr			the root of the tree
*			deleteNode		the record that will delete
			compare			pointer to a function to decide the rules to delete record
*	
*	Output: targerRoot		the deleted record
*
*	Destroy: none
*	
**********************************************************************/
Node *genericDelRedBlackTree(Node **rootPtr,Node *delNode, int(*compareFileSize)(Node **rootPtr,Node *delNode)){
    Node *node = _genericDelRedBlackTree(rootPtr,delNode,compareFileSize);
    if(*rootPtr!=NULL)
        (*rootPtr)->color='b';
    return node;
}

Node *_genericDelRedBlackTree(Node **rootPtr,Node *delNode, int(*compareRecord)(Node **rootPtr,Node *delNode)){
    int compare ; char tempColor; 
    Node *node , *tempRoot ,*tempLeftChild, *tempRightChild,*removeSuccessor,tempSuccessor;
	compare = compareRecord(rootPtr,delNode);
	if(compare == 0){
		if(rightChild != NULL){
			node = *rootPtr;
			removeSuccessor = removeNextLargerSuccessor(&rightChild);
			tempSuccessor = *removeSuccessor;
			tempLeftChild = leftChild ; 
			tempRightChild = rightChild;
			tempColor = (*rootPtr)->color; 
			*rootPtr = removeSuccessor;
			leftChild = tempLeftChild; 
			rightChild = tempRightChild;
			(*rootPtr)->color = tempColor;
			node->left = NULL;
			node->right = NULL;
			restructureRedBlackTree(rootPtr,&tempSuccessor);
			return node;
		}else if(leftChild != NULL){
			rightRotate(rootPtr);
			node = removeNextLargerSuccessor(&rightChild);
			(*rootPtr)->color = 'b';
		}else{
			node = *rootPtr;
			*rootPtr=NULL;
			return node;
		}
	}else if(compare == 1){
		node = _genericDelRedBlackTree(&leftChild,delNode,compareRecord);
	}else if(compare == -1){
		node = _genericDelRedBlackTree(&rightChild,delNode,compareRecord);
	}
	restructureRedBlackTree(rootPtr,delNode);
	return node;
}

/*******************************************
    This function use handle the color
    of node in the RedBlackTree
*********************************************/

void handleColor(Node **rootPtr,Node *deleteNode){
if((*rootPtr)->left->color == 'r' && (*rootPtr)->right->color == 'r'){
		(*rootPtr)->color ='r';
		(*rootPtr)->left->color ='b';
		(*rootPtr)->right->color ='b';
	}
}

/*******************************************
    This function use to remove the most 
    left node in the RedBlackTree
*********************************************/
Node *removeNextLargerSuccessor(Node **rootPtr){
	Node *removeNode;
	
	if(leftChild !=NULL){
        removeNode = removeNextLargerSuccessor(&leftChild);
    }else if(rightChild == NULL){
		removeNode = *rootPtr;
        *rootPtr = NULL;
        return removeNode;
	}else if(rightChild->color == 'r'){
		removeNode = *rootPtr;
		*rootPtr = rightChild;
		(*rootPtr)->color = 'b';
        return removeNode;
	}
    restructureRedBlackTree(rootPtr,removeNode);
    return removeNode;
}

