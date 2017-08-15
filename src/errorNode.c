#include <string.h>
#include <malloc.h>
#include "errorNode.h"

Error *createErr(char *stringMsg,void *duplicatedNode){
	Error *errNode = malloc(sizeof(Error));
	errNode->data = duplicatedNode;
	errNode->errCode = ERR_EQUIVALENT_NODE;
	errNode->errorMsg = stringMsg;
	return errNode;
}
