#include "jansson.h"
#include "fileHandling.h"

struct stat attr;
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
int checkFile(const char *path) {
    FILE *f = fopen(path,"r");
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
FILE *getFilePtr(const char *path){
	int c = 0;
	c = checkFile(path);
	if(c == 1){
		FILE *f = fopen(path,"r");
		return f;
	}else if(c == 0){
		
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
int checkFolder(const char *path) {
    DIR *d = opendir(path);
	if(d!=NULL)
		return 1;
	else 
		return 0;
}

/*************************************************************
* 	Get folder pointer  
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: d					pointer of the folder
*			Throw error			indicate is not a folder
*	
*	Destroy: none
**************************************************************/
DIR *getFolderPtr(const char *path){
	int c = 0;
	
	c = checkFolder(path);
	if(c == 1){
		DIR *d = opendir(path);
		return d;
	}else if(c == 0){
		
	}
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
int getFileSize(const char *path){
	json_object();
	int size = 0;
	FILE *f = getFilePtr(path);
	fseek(f,0,SEEK_END);    
	size = ftell(f);   
    return size;
}

/*************************************************************
* Check the total number of file in folder 
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: count		number of file inside a folder 
*			
*	Destroy: none
**************************************************************/
int listFileNumber(const char *path){
	int count = 0;
	DIR *folder = getFolderPtr(path);
	while((dir=readdir(folder))!=NULL){
		if(dir->d_type == DT_REG){
			count++;
		}
	}
	return count;
}

/*************************************************************
* Check the total number of sub folders in folder 
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: count		number of sub folders inside a folder 
*			
*	Destroy: none
**************************************************************/
int listSubFolderNumber(const char *path){
	int count = 0;
	DIR *folder = getFolderPtr(path);
	while((dir=readdir(folder))!=NULL){
		if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			count++;
		}
	}
	return count;
}

/****************************************************************************
*   This function add subfolder path name into existing folder path name
*
*	Input: 	path		the path of the folder
*			
*	Output: newPath		the path of subFolder 
*			
*	Destroy: none
****************************************************************************/
char *subFolder(const char *path){
	static char newPath[255];
	strcpy(newPath,path);//Copy the path to a new path 
	strcat(newPath,"/");//Add / right after the path name
	strcat(newPath,dir->d_name);//Add the sub folder path name right after the main folder path name		
	return newPath;
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
char *traverseFolder(const char *path){
	DIR *d = getFolderPtr(path);
	while((dir = readdir(d))!= NULL){
		if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			//printf("sub folder: %s\n",dir->d_name);
			char *sub = subFolder(path);
			traverseFolder(sub);//Recursivly call the function to traverse file in sub folder
		}else if(dir->d_type == DT_REG){
			//printf("file name: %s\n",dir->d_name);
		}
	}
	closedir(d);
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
char *checkLatestModifiedTime(const char *path){
	/*
	static char times[100];
	time_t t = time(NULL);
	stat(path, &attr);
	strftime(times,20,"%x - %I:%M%p",localtime(&(attr.st_mtime)));
	return times;
	*/
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

int getDateTime(char *dateTime,const char *path){
	int val,valArray[20];
	char buf[100];
	struct tm info;
	time_t t = time(NULL);
	stat(path,&attr);
	info = *(localtime(&(attr.st_mtime)));
	strftime(buf,sizeof(buf),"%y%m%d%H%M",&info);
	val = atoi(buf);
	info.tm_year = val; 
	printf("%d\n",info.tm_year);
	
}
/*
int compareDateTime(char *JSONDateTime, const char *path){
	int compare = 0;
	char *fileDateTime;
	fileDateTime = getDateTime(path);
	
	if(compare < 0)
		return -1;
	else if(compare > 0)
		return 1;
	else 
		return 0;
}
*/

