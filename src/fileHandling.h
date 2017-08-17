#ifndef fileHandling_H
#define fileHandling_H

#include "Node.h"

#define MaxFile 10000

void summariseFolder();
void deleteAllContentInFolder(char *folderPath);
void deleteFile(char *filePathToDelete);
char *duplicateFileForTesting(char *fileToDuplicate, char *newName);
char *createFileForTesting(char *folderName,char *fileName,int size);
void scanFolder(Node **root, Node **duplicatedRoot,const char *folderName);
void traverseFolder(Node **duplicatedFileRoot,const char *folderPath);
void _traverseFolder(Node **root,Node **duplicatedRoot,const char *folderPath);
int getFileSize(const char *path);
int checkFileNumberInFolder(const char *folderName);
int getFileEpoch(char *filePath);
int getFileDateTime(char *dateTime,char *path);
int convertEpoch(char *fileDateTime);

#endif // fileHandling_H
