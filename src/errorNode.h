#ifndef errorNode_H
#define errorNode_H

#include "Node.h"

typedef enum{
	ERR_NO_ERROR,
	ERR_EQUIVALENT_NODE,
	ERR_JSON_UNAVAILABLE
}ErrorCode;

typedef struct Error Error;
typedef struct Error *ErrorPtr;
struct Error{
	void *data;
	ErrorCode errCode;
	char *errorMsg;
};

Error *createErr(char *stringMsg,void *duplicatedNode);
void freeErr(Error *e);

#endif // errorNode_H
