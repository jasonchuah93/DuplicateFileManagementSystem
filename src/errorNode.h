#ifndef errorNode_H
#define errorNode_H

#include "Node.h"

typedef enum{
	ERR_NO_ERROR,
	ERR_EQUIVALENT_NODE,
	ERR_NODE_UNAVAILABLE
}ErrorCode;

typedef struct Error Error;

struct Error{
	void *data;
	ErrorCode errCode;
	char *errorMsg;
};

Error *createErrNode(Node *duplicateNode);

#endif // errorNode_H
