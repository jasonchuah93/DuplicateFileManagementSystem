#ifndef __ERROR_H__
#define __ERROR_H__


typedef enum {INVALID_PATH} Error;

typedef struct{
	char *message;
}ErrorMessage;

extern ErrorMessage errorMessage;
#endif //__ERROR_H__