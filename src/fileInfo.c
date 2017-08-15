#include <string.h>
#include <malloc.h>
#include "fileInfo.h"

FileInfo *initInfo(){
	FileInfo *info = malloc(sizeof(FileInfo));
	info->fileName = NULL;
	info->fileSize = 0;
	info->fileCRC32Value = 0;
	return info;
}
