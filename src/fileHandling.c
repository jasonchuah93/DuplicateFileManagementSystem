#include "fileHandling.h"

struct stat buf;
struct dirent *dir;
/*************************************************************
* Check if the parameter is any type of file 
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: 1			indicate is file
*			0			indicate is not a file
*	
*	Destroy: none
**************************************************************/
bool checkFile(const char* path) {
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

/*************************************************************
* Check if the parameter is folder
*
*	Input: 	path		the path of the folder we want to check  
*			
*	Output: 1			indicate is folder
*			0			indicate is not a folder
*	
*	Destroy: none
**************************************************************/
bool checkFolder(const char* path) {
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

/*************************************************************
* Check the size of a given file
*
*	Input: 	path		the path of the folder we want to check  
*			
*	Output: size		size of the file 
*			
*	Destroy: none
**************************************************************/
int getFileSize(const char* path){
	FILE *fp;
    int size = 0;
 
    fp = fopen(path,"r");
    if (fp == NULL)
        printf("File unable to open\n");
    else{ 
        fseek(fp,0,2);    
		size = ftell(fp);   
		//printf("The size of given file is : %d bytes\n", size); //For test check    
    }
	fclose(fp);
	return size;
}

char checkLatestModifiedTime(const char* path){
	char times[60];
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	struct stat attr;
    stat(path, &attr);
    //printf("Last modified time: %s\n",ctime(&attr.st_mtime));
}
/*
char *getFileName(char* path){
	DIR *d;
	if(checkFolder(path) == TRUE){
		d = opendir(path);
		if(d){
			while ((dir = readdir(d)) != NULL){
				if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
					printf("sub folder: %s\n",dir->d_name);
					//return dir->d_name;
				}else if(dir->d_type == DT_REG){
					//printf("file name: %s\n",dir->d_name);
					//return dir->d_name;
				}
			}
			closedir(d);
		}
	}
}
*/

char *listAllFiles(const char* path){
	DIR *d,*sub_d,*sub_sub_d;
	char filePath[255],subFilePath[255];
	
	d = opendir(path);
	dir = readdir(d);
	dir = readdir(d);
	dir = readdir(d);
	dir = readdir(d);
	dir = readdir(d);
	strcpy(filePath,path);
	strcat(filePath, "/");
	strcat(filePath, dir->d_name);
	stat(filePath,&buf);
	if(S_ISDIR(buf.st_mode)){
		sub_d=opendir(filePath);
		dir = readdir(sub_d);
		dir = readdir(sub_d);
		dir = readdir(sub_d);
		strcpy(subFilePath,filePath);
		strcat(subFilePath, "/");
		strcat(subFilePath, dir->d_name);
		stat(subFilePath,&buf);
		if(S_ISDIR(buf.st_mode)){
			sub_sub_d = opendir(subFilePath);
			dir = readdir(sub_sub_d);
			dir = readdir(sub_sub_d);
			dir = readdir(sub_sub_d);
		}
	}
	return dir->d_name;
	closedir(d);
}

int listFileNumber(const char* path){
	int count = 0;
	DIR * folder;
	folder = opendir(path);
	while((dir=readdir(folder))!=NULL){
		if(dir->d_type == DT_REG){
			count++;
		}
	}
	closedir(folder);
	return count;
}

int listSubFolderNumber(const char* path){
	int count = 0;
	DIR * folder;
	folder = opendir(path);
	while((dir=readdir(folder))!=NULL){
		if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			count++;
		}
	}
	closedir(folder);
	return count;
}

