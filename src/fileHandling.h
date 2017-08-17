#ifndef fileHandling_H
#define fileHandling_H

#include <unistd.h>
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

void summariseFolder();
void deleteAllContentInFolder(char *folderPath);
void deleteFile(char *filePathToDelete);
char *duplicateFileForTesting(char *fileToDuplicate, char *newName);
char *createFileForTesting(char *filePath,int size);
void scanFolder(Node **root, Node **duplicatedRoot,const char *folderName);
char *changeDir(char *curFolder, char *nextFolder);
void traverseFolder(Node **duplicatedFileRoot,const char *folderPath);
void _traverseFolder(Node **root,Node **duplicatedRoot,const char *folderPath);
char *createJSONFilePath(const char *folderPath);
char *addFolderPathToFilePath(const char *folderName,const char *fileName);
int checkFile(const char *path);
int checkFolder(const char *path);
FILE *getFilePtr(const char *path);
DIR *getFolderPtr(const char *path);
int getFileSize(const char *path);
int checkFileNumberInFolder(const char *folderName);
int listSubFolderNumber(const char *path);
char *getSubFolderPath(const char *path);
int compareDateTime(char *dateTime,const char *path);
int getFileEpoch(char *filePath);
int getFileDateTime(char *dateTime,char *path);
int convertEpoch(char *fileDateTime);

#endif // fileHandling_H
