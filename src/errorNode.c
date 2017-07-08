#include <stdio.h>
#include <stdlib.h>
#include "errorNode.h"

Error *createErrNode(Node *duplicatedNode){
	Error *errNode = malloc(sizeof(Error));
	errNode->data = duplicatedNode;
	errNode->errCode = ERR_EQUIVALENT_NODE;
	return errNode;
}