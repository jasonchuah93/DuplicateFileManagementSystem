#ifndef fileInfo_H
#define fileInfo_H

typedef struct FileInfo FileInfo;
struct FileInfo{
	const char *fileName;
	unsigned long long int fileSize;
	unsigned long int fileCRC32Value; 
};

FileInfo *initInfo();

#endif // fileInfo_H
