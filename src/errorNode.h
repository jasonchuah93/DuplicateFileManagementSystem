#ifndef errorNode_H
#define errorNode_H

#define getNameInErr(err) ((FileInfo*)((LinkedList*)((Node*)(err->data))->data)->head->data)->fileName
#define getSizeInErr(err) ((FileInfo*)((LinkedList*)((Node*)(err->data))->data)->head->data)->fileSize
#define getCRCInErr(err) ((FileInfo*)((LinkedList*)((Node*)(err->data))->data)->head->data)->fileCRC32Value

typedef enum{
	ERR_NO_ERROR,
	ERR_EQUIVALENT_NODE,
	ERR_JSON_UNAVAILABLE,
	ERR_NOT_JSON_ARRAY,
	ERR_NOT_JSON_OBJECT,
	ERR_NOT_STRING_OBJECT,
	ERR_NOT_INTEGER_OBJECT
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
