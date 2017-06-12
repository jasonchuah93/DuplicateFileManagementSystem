#include "fileHandling.h"
#include "Error.h"

struct stat buf;
struct dirent *dir;
/*************************************************************
* 	Check if the parameter is any type of file 
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: 1			indicate is file
*			0			indicate is not a file
*	
*	Destroy: none
**************************************************************/
int checkFile(const char* path) {
    FILE *f;
	f = fopen(path,"r");
	if(f!=NULL)
		return 1;
	else
		return 0;
}

/*************************************************************
* 	Get file pointer  
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: f					pointer of the file
*			Throw error			indicate is not a file
*	
*	Destroy: none
**************************************************************/
FILE *getFile(const char* path){
	FILE *f;
	int c = 0;
	c = checkFile(path);
	if(c == 1){
		f = fopen(path,"r");
		return f;
	}else if(c == 0){
		Throw(INVALID_FILE);
	}
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
int checkFolder(const char* path) {
    DIR *d;
	d = opendir(path);
	if(d!=NULL)
		return 1;
	else 
		return 0;
}

/*************************************************************
* Check the size of a given file
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: size		size of the file 
*			
*	Destroy: none
**************************************************************/
int getFileSize(const char* path){
	FILE *f;
    int size = 0;
	
    f = getFile(path);
	fseek(f,0,SEEK_END);    
	size = ftell(f);   
    return size;
}

/*************************************************************
* Check the last modified date & time of the file 
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: times		date and time of the file 
*			
*	Destroy: none
**************************************************************/
char *checkLatestModifiedTime(const char* path){
	static char times[100];
	time_t t = time(NULL);
	struct stat attr;
	stat(path, &attr);
	strftime(times,20,"%x - %I:%M%p",localtime(&(attr.st_mtime)));
	return times;
}

/*************************************************************
*   Scan the folder, traverse all content inside
*
*	Input: 	path		the path of the folder we want to scan  
*			
*	Output: size		size of the file 
*			
*	Destroy: none
**************************************************************/
char *traverseFolder(const char* path){
	DIR *d;
	char newPath[255];
	int fileSize=0;
	d = opendir(path);
	if(d!=NULL){
		while((dir = readdir(d))!= NULL){
			if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
				//printf("sub folder: %s\n",dir->d_name);
				strcpy(newPath,path);//Copy the path to a new path 
				strcat(newPath,"/");//Add / right after the path name
				strcat(newPath,dir->d_name);//Add the sub folder path name right after the main folder path name
				traverseFolder(newPath);//Recursive call the function to traverse file in sub folder
			}else if(dir->d_type == DT_REG){
				//printf("file name: %s\n",dir->d_name);
				fileSize = getFileSize(dir->d_name);
				printf("The size of given file is : %d bytes\n",fileSize);
			}
		}
	}else{
		errorMessage.message = "Invalid path!";
		Throw(INVALID_PATH);
	}
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

