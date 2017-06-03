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

//This function on hold 
bool checkFileFolder(const char* path){
	DIR *d;
	if(checkFolder(path) == TRUE){
		d = opendir(path);
		if(d){
			while ((dir = readdir(d)) != NULL){
				
				//printf("%s\n", dir->d_name);
			}
			
			closedir(d);
		}
		
		return 1;		
	}else if(checkFile(path)==TRUE){
		return 1;
	}
}

int checkFileSize(const char* path){
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
