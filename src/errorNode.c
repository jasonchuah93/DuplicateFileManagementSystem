#include <stdlib.h>
#include <malloc.h>
#include "errorNode.h"
#include "CException.h"

void catchErr(Node **newRoot,Error *err){
	
}

Error *createErr(char *stringMsg,void *duplicatedNode){
	Error *errNode = malloc(sizeof(Error));
	errNode->data = duplicatedNode;
	errNode->errCode = ERR_EQUIVALENT_NODE;
	errNode->errorMsg = stringMsg;
	return errNode;
}

void freeErr(Error *e){
  free(e);
}