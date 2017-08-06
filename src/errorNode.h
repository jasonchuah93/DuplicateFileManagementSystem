#ifndef errorNode_H
#define errorNode_H

#define getNameInErr(err) ((FileInfo*)((Node*)err->data)->data)->fileName
#define getSizeInErr(err) ((FileInfo*)((Node*)err->data)->data)->fileSize
#define getCRCInErr(err) ((FileInfo*)((Node*)err->data)->data)->fileCRC32Value

typedef enum{
	ERR_NO_ERROR,
	ERR_EQUIVALENT_NODE,
	ERR_JSON_UNAVAILABLE,
	ERR_NOT_JSON_ARRAY,
	ERR_NOT_JSON_OBJECT,
	ERR_NOT_STRING_OBJECT,
	ERR_NOT_INTEGER_OBJECT,
	ERR_FILE_NOT_OPEN,
	ERR_FILE_NO_EXIST,
	ERR_EMPTY_CONTENT,
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
