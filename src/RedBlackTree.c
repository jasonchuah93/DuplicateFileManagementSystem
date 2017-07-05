#include <stdio.h>
#include "Node.h"
#include "Rotation.h"
#include "compareJSON.h"
#include "redBlackTree.h"
#include "RestructureNode.h"
#include "ErrorCode.h"

/*********************************************************************
* This function will add a new record into the red black tree
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
	int compare=0;
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
		else if(compare == 0)
			printf("Both files are equal\n");
		
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

