#include <stdio.h>
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CException.h"

#define leftChild (*rootPtr)->left
#define rightChild (*rootPtr)->right
#define leftGrandChild (*rootPtr)->left->left
#define rightGrandChild (*rootPtr)->right->right
#define leftRightGrandChild (*rootPtr)->left->right
#define rightLeftGrandChild (*rootPtr)->right->left

void _addRedBlackTree(Node **rootPtr,Node *deleteNode);
Node *_delRedBlackTree(Node **rootPtr,Node *deleteNode);
Node *_delRedBlackTreeVer2(Node **rootPtr,Node *deleteNode);

/**************************
    Sub function to deal
    with nodes color 
**************************/

void handleColor(Node **rootPtr,Node *deleteNode){
  Node *root = *rootPtr;
  if(root->left->color == 'r' && root->right->color == 'r'){
        root->left->color ='b';
        root->right->color ='b';
        root->color ='r';
      }
}
/***********************************
    This function use to add node 
    into the RedBlackTree
***********************************/
void addRedBlackTree(Node **rootPtr,Node *deleteNode){
	_addRedBlackTree(rootPtr,deleteNode);
	(*rootPtr)->color='b';
}

void _addRedBlackTree(Node **rootPtr,Node *deleteNode){
  Node *root = *rootPtr;
  if(root == NULL){
	*rootPtr = deleteNode;
    return;
  }
  if (root->left!=NULL && root->right!=NULL){
    handleColor(rootPtr,deleteNode); 
  }
  if(root->data > deleteNode->data){
	_addRedBlackTree(&root->left,deleteNode);
  }else if(root->data < deleteNode->data){
	_addRedBlackTree(&root->right,deleteNode);
  }else{
	Throw(ERR_EQUIVALENT_NODE);
  }
  if(root->left!=NULL && root->right==NULL){
	if(root->left->left !=NULL){
		if(root->left->color == 'r' && root->left->left->color == 'r'){
			rightRotate(rootPtr);
		}
	}else if(root->left->right !=NULL){
		if(root->left->color == 'r' && root->left->right->color == 'r'){
			leftRightRotate(rootPtr);
		}
	}
  }else if(root->left==NULL && root->right!=NULL){
	if(root->right->right !=NULL){
		if(root->right->color == 'r' && root->right->right->color == 'r'){
			leftRotate(rootPtr);
		}
	}else if(root->right->left !=NULL){
		if(root->right->color == 'r' && root->right->left->color == 'r'){
			rightLeftRotate(rootPtr);
		}
	}
  }
}

/***********************************
    This function use to delete node 
    into the RedBlackTree
***********************************/

Node *delRedBlackTree(Node **rootPtr,Node *deleteNode){
  Node *node =_delRedBlackTree(rootPtr,deleteNode);
  if(*rootPtr!=NULL)
    (*rootPtr)->color='b';
  return node;
}

Node *_delRedBlackTree(Node **rootPtr,Node *deleteNode){
  char tempColor;
  Node *node , *tempRoot ,*tempLeftChild, *tempRightChild, *root = *rootPtr;
  if(root==deleteNode){
    if(rightChild){
        tempRoot = removeNextLargerSuccessor(&rightChild);
        tempLeftChild = leftChild ; tempRightChild = rightChild;
        tempColor = (*rootPtr)->color; 
        *rootPtr = tempRoot;
        leftChild=tempLeftChild; rightChild = tempRightChild;
        (*rootPtr)->color=tempColor;
        restructureRedBlackTree(rootPtr,deleteNode);
    }else if(leftChild){
        rightRotate(rootPtr);
        node = removeNextLargerSuccessor(&rightChild);
        (*rootPtr)->color = 'b';
    }else{
        *rootPtr=NULL;
    }
    return node;
  }else{
	if(leftChild == NULL && rightChild == NULL){
		 Throw(ERR_NODE_UNAVAILABLE);
    }else if((*rootPtr)->data > deleteNode->data){
        node= _delRedBlackTree(&leftChild,deleteNode);
    }else if((*rootPtr)->data < deleteNode->data){
		node= _delRedBlackTree(&rightChild,deleteNode);
    }
  }
  restructureRedBlackTree(rootPtr,deleteNode);
  return node;
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

/******************************************************]
	********************
		Old function 
	********************
Node *_delRedBlackTree(Node **rootPtr,Node *deleteNode){
  Node *node;
  Node *root = *rootPtr;
  if(root==deleteNode){
    *rootPtr=NULL;
    return;
  }else{
	if(root->left == NULL && root->right == NULL){
        Throw(ERR_NODE_UNAVAILABLE);
    }else if(root->data > deleteNode->data){
		if(root->left->left!=NULL || root->left->right!=NULL){
			root->left->color='b';
			root->left->left->color='r';
			root->left->right->color='r';
		}
		node=_delRedBlackTree(&root->left,deleteNode);
		if(root->left==NULL && root->right!=NULL){
			if(root->right->right!=NULL){
				if(root->right->left->color=='b' && root->right->right->color=='b'){
					leftRotate(rootPtr);
					(*rootPtr)->left->right->color='r';
				}
			}
		}
	}else if(root->data < deleteNode->data){
		if(root->right->left!=NULL || root->right->right!=NULL){
			root->right->color='b';
			root->right->left->color='r';
			root->right->right->color='r';
		}
		node=_delRedBlackTree(&root->right,deleteNode);
		if(root->left!=NULL && root->right==NULL){
			if(root->left->left!=NULL){
				if(root->left->left->color=='b' && root->left->right->color=='b'){
					rightRotate(rootPtr);
					(*rootPtr)->right->left->color='r';
				}
			}
		}
	}
  }
  
  return node;
}
*********************************************************************/
