#ifndef fileHandling_H
#define fileHandling_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include "Node.h"

#define TRUE 1
#define FALSE 0
#define MaxFile 10000

void scanFolder(Node *root, Node *duplicatedRoot,const char *folderName);
void traverseFolder(Node *duplicatedFileRoot,char *folderPath);
void _traverseFolder(Node *root,Node *duplicatedRoot,char *folderPath);
char *createJSONFilePath(const char *folderPath);
char *addFolderPathToFilePath(const char *folderName,const char *fileName);
int checkFile(const char *path);
int checkFolder(const char *path);
FILE *getFilePtr(const char *path);
DIR *getFolderPtr(const char *path);
int getFileSize(const char *path);
int listFileNumber(const char *path);
int listSubFolderNumber(const char *path);
char *subFolder(const char *path);
int compareDateTime(char *dateTime,const char *path);
int getFileDateTime(char *dateTime,const char *path);
int convertEpoch(char *fileDateTime);

#endif // fileHandling_H
