#include <stdio.h>
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "ErrorCode.h"
#include "CException.h"

#define leftChild (*nodePtr)->left
#define rightChild (*nodePtr)->right
#define leftGrandChild (*nodePtr)->left->left
#define rightGrandChild (*nodePtr)->right->right
#define leftRightGrandChild (*nodePtr)->left->right
#define rightLeftGrandChild (*nodePtr)->right->left

/********************************************************
    This function will return 1 if the color node
    is black
********************************************************/

int isNodeBlack(Node **node){
	if(*node!=NULL && (*node)->color=='b'){
		return 1;
	}else{
		return 0;
	}
}

/********************************************************
    This function will return 1 if the color node
    is red
********************************************************/

int isNodeRed(Node **node){
	if(*node!=NULL && (*node)->color=='r'){
		return 1;
	}else{
		return 0;
	}
}

/**
	* Node : x = not possible
	*
	*	node			removeNode				return
	*  --------------------------------------------------
	*   NULL		 		NULL				 NULL
	*	NULL				red					  0
	*	NULL				black				  1	
	*	NULL				double black		  x	
	*	red					NULL				  x	
	*	red					red					  0
	*	red					black                 0
	*	red					double black          x
	*	black				NULL                  x
	*	black				red	                  0
	*	black				black	              0
	*	black				double black          x
	*	double black		NULL                  x
	*	double black		red                   1
	*	double black		black                 1 
	*	double black		double black          x 
**/

int isDoubleNodeBlack(Node *node , Node *removeNode){
	if(node==NULL && removeNode->color =='b'){
		return 1;
	}
	else if(node!=NULL && node->color=='d'){
		return 1;
	}else
		return 0;
}

/*************************

 CASE 1 SUB-FUNCTION
*************************/
void restructureBlackRightWithOneRedChild(Node **nodePtr){
	char parentColor = (*nodePtr)->color;
	if(isNodeRed(&rightGrandChild)){
		rightChild->color = parentColor;
        leftRotateVer2(nodePtr);
    }else if(isNodeRed(&rightLeftGrandChild)){
		rightLeftGrandChild->color = parentColor;
        rightLeftRotateVer2(nodePtr);
	}
    if(leftChild)
        leftChild->color='b';
    if(rightChild)
        rightChild->color='b';
}

void restructureBlackLeftWithOneRedChild(Node **nodePtr){
	char parentColor = (*nodePtr)->color;
	if(isNodeRed(&leftGrandChild)){
		leftChild->color = parentColor;
        rightRotateVer2(nodePtr);
    }else if(isNodeRed(&leftRightGrandChild)){
		leftRightGrandChild->color = parentColor;
        leftRightRotateVer2(nodePtr);
	}
    if(leftChild)
        leftChild->color='b';
    if(rightChild)
        rightChild->color='b';
}

/*************************

 CASE 2 SUB-FUNCTION
*************************/

void restructureBlackRightWithBlackChildren(Node **nodePtr){
	if(isNodeBlack(nodePtr)){
		(*nodePtr)->color = 'd';
	}else if(isNodeRed(nodePtr)){
		(*nodePtr)->color = 'b';
	}
    if(leftChild!=NULL){
        leftChild->color='b';
    }
    if(rightChild!=NULL){
        rightChild->color='r';
    }
    
}

void restructureBlackLeftWithBlackChildren(Node **nodePtr){
	char parentColor=(*nodePtr)->color;
	if(parentColor =='b'){
		(*nodePtr)->color = 'd';
	}else if(parentColor == 'r'){
		(*nodePtr)->color = 'b';
	}
	if(leftChild!=NULL){
        leftChild->color='r';
    }
    if(rightChild!=NULL){
        rightChild->color='b';
    }
}

/*************************

 CASE 3 SUB-FUNCTION
*************************/

void restructureRedRight(Node **nodePtr,Node *delNode){
	leftRotate(nodePtr);
    (*nodePtr)->color = 'b';
	if(isNodeRed(&leftRightGrandChild->right)){
		restructureBlackRightWithOneRedChild(&leftChild);
		leftChild->color='r';
	}else if(isDoubleNodeBlack(leftGrandChild,delNode) && isNodeBlack(&leftRightGrandChild)){
		restructureBlackRightWithBlackChildren(&leftChild);
		leftChild->color='b';
	}
}

void restructureRedLeft(Node **nodePtr,Node *delNode){
	rightRotate(nodePtr);
	(*nodePtr)->color = 'b';
	if(isNodeRed(&rightLeftGrandChild->left)){
		restructureBlackLeftWithOneRedChild(&rightChild);
		rightChild->color='r';
	}else if(isDoubleNodeBlack(rightGrandChild,delNode) && isNodeBlack(&rightLeftGrandChild)){
		restructureBlackLeftWithBlackChildren(&rightChild);
		rightChild->color='b';
	}
}

/**************************************************
  This function combined all the sub functions
  above for each cases
**************************************************/

void restructureRedBlackTree(Node **nodePtr,Node *removeNode){
    if(isDoubleNodeBlack(leftChild,removeNode)){
        if(isNodeRed(&rightChild)){
            if(rightLeftGrandChild !=NULL && rightGrandChild !=NULL){
                restructureRedRight(nodePtr,removeNode);
            }
        }else if(isNodeBlack(&rightChild) && isNodeRed(&rightLeftGrandChild)){
            restructureBlackRightWithOneRedChild(nodePtr);
        }else if(isNodeBlack(&rightChild)){
           restructureBlackRightWithBlackChildren(nodePtr);
        }
    }else if(isDoubleNodeBlack(rightChild,removeNode)){
        if(isNodeRed(&leftChild)){
            if(leftRightGrandChild!=NULL && leftGrandChild!=NULL){
                restructureRedLeft(nodePtr,removeNode);
            }
        }else if(isNodeBlack(&leftChild) && isNodeRed(&leftRightGrandChild)){
            restructureBlackLeftWithOneRedChild(nodePtr);
        }else if(isNodeBlack(&leftChild)){
            restructureBlackLeftWithBlackChildren(nodePtr);
        }
    }
}   

