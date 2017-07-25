#ifndef errorNode_H
#define errorNode_H

#define getNameInErr(err) ((FileInfo*)((Element*)((Node*)err->data)->data)->data)->fileName
#define getSizeInErr(err) ((FileInfo*)((Element*)((Node*)err->data)->data)->data)->fileSize
#define getCRCInErr(err) ((FileInfo*)((Element*)((Node*)err->data)->data)->data)->fileCRC32Value

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
