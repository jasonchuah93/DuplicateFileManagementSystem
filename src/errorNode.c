#include <stdlib.h>
#include <malloc.h>
#include "errorNode.h"
#include "CException.h"

Error *createErr(Node *duplicatedNode){
	Error *errNode = malloc(sizeof(Error));
	errNode->data = duplicatedNode;
	errNode->errCode = ERR_EQUIVALENT_NODE;
	return errNode;
}

void freeErr(Error *e){
  free(e);
}