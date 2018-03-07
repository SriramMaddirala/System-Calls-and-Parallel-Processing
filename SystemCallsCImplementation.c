/* 
Your last C# code is saved below:
/***********************************************************************************************

 CSci 4061 Fall 2017
 Assignment# 2:   I/O Programming on UNIX/LINUX

 Student name: Sriram Pohar Maddirala
 Student ID:   5014900
 X500 id:      maddi011@umn.edu

 Operating system on which you tested your code: Linux, Unix, MacOS
 CSELABS machine: <machine you tested on eg: xyz.cselabs.umn.edu>

***********************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/time.h>
#define NAMESIZE 256
#define TOKENSIZE 100
#define BUFSIZE 256


//Create global variables and arrays to facilitate calculations.
int largestFile; 
int secondLarge;
int thirdLarge;
char *largestName = (char*) malloc(NAMESIZE);
char *secondName = (char*) malloc(NAMESIZE);
char *thirdName = (char*) malloc(NAMESIZE);
void checkAndSort(const char *name, int sizefil ){
    printf("\n %s", name);
    if(sizefil>thirdLarge){
        if(sizefil>secondLarge){
            if(sizefil>largestFile){
                largestFile=sizefil;
                strcpy(largestName, name);
            }
            else{
                secondLarge=sizefil;
                strcpy(secondName, name);
            }
        }
        else{
            thirdLarge= sizefil;
            strcpy(thirdName, name);
        }
    }    
}
//create function to append strings
char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void traverseDirectory1( const char *currentDirectory){
    struct stat statbuf;
    struct dirent *direntry;
    DIR *opdirstrm;
    chdir(currentDirectory);
    stat(currentDirectory, &statbuf);
    printf("\n %s", currentDirectory);
    printf("cunt");
    if(!S_ISDIR(statbuf.st_mode)){
	printf("%s", currentDirectory);
        printf("%s\n", "Invalid directory, directory doesn't exist");
        exit(0);
    }
    if((opdirstrm = opendir(currentDirectory)) == NULL){
          perror("Error when opening directory");
          exit(0);
    }
    //iterate through directory unless a subdirectory is found
    //pass subdirectory to function'
    while((direntry = readdir(opdirstrm))!= NULL){
        stat(direntry->d_name,&statbuf);
    	if(strcmp(direntry->d_name,".")==0){
    		continue;    
    	}
    	if(strcmp(direntry->d_name,"..")==0){
    		continue;    
    	}
        if(S_ISDIR(statbuf.st_mode)){
	    char filepath[4096];
	    strcpy(filepath, currentDirectory);
	    strcat(filepath,"/");
	    strcat(filepath, direntry->d_name);
            traverseDirectory1(filepath);
        }
	printf("asf");
        if(S_ISREG(statbuf.st_mode)){
            int sizefile = statbuf.st_size;
            checkAndSort(direntry->d_name, sizefile);
        }
    }
}
void traverseDirectory2(const char *currentDirectory){
    struct stat statbuf;
    struct dirent *direntry;
    DIR *opdirstrm;
    chdir(currentDirectory);
    stat(currentDirectory, &statbuf);
    if(!((S_ISDIR(statbuf.st_mode)))){
        printf("%s\n", "Invalid directory, directory doesn't exist");
        exit(0);
    }
    if((opdirstrm = opendir(currentDirectory)) == NULL){
          perror("Error when opening directory");
          exit(0);
    }
    while((direntry = readdir(opdirstrm))!=NULL){
        lstat(direntry->d_name,&statbuf);
    if(strcmp(direntry->d_name,".")==0){
    continue;    
    }
    if(strcmp(direntry->d_name,"..")==0){
    continue;    
    }
        if(S_ISDIR(statbuf.st_mode)){
	    char filepath[4096];
	    strcpy(filepath, currentDirectory);
	    strcat(filepath,"/");
	    strcat(filepath, direntry->d_name);
            traverseDirectory2(filepath);
        }
        if((S_ISREG(statbuf.st_mode)) || (S_ISLNK(statbuf.st_mode))){
            if(statbuf.st_size==0){
                printf("%s\n", direntry->d_name);
            }
        }
    }
}
void traverseDirectory3(const char *currentDirectory){
    struct stat statbuf;
    struct dirent *direntry;
    DIR *opdirstrm;
    chdir(currentDirectory);
    stat(currentDirectory, &statbuf);
    if(!((S_ISDIR(statbuf.st_mode)))){
        printf("%s\n", "Invalid directory, directory doesn't exist");
        exit(0);
    }
    if((opdirstrm = opendir(currentDirectory)) == NULL){
          perror("Error when opening directory");
          exit(0);
    }
}
void traverseDirectory4(const char *currentDirectory){
    struct stat statbuf;
    struct dirent *direntry;
    DIR *opdirstrm;
    chdir(currentDirectory);
    stat(currentDirectory, &statbuf);
    if(!((S_ISDIR(statbuf.st_mode)))){
        printf("%s\n", "Invalid directory, directory doesn't exist");
        exit(0);
    }
    if((opdirstrm = opendir(currentDirectory)) == NULL){
          perror("Error when opening directory");
          exit(0);
    }
    //if backup exists, append time and create new backup
    char  buffer[BUFSIZE];
    time_t  clocktime;
    struct tm  *timeinfo;
    time (&clocktime);
    timeinfo = localtime( &clocktime );
    strftime(buffer, 64, "%b-%d-%Y-%H-%M-%S", timeinfo);
    char backup[NAMESIZE];
   // char newBackup[NAMESIZE] = concat(backup, buffer);
    //rename(backup, newBackup);

    
    //printf("Current date and time is: %s\n", buffer);
}

//Set up main function
int main(int argc, char *argv[])
{
    int choice = -1;
    char *input_dir_name, *dirpath, *chptr;
    largestFile=0; 
    secondLarge=0;
    thirdLarge=0;
    /* IF ARRAY DOESN"T WORK
    largestFiles[0] = *largestName;
    largestFiles[1] = *secondName;
    largestFiles[2] = *thirdName;
    largestName = NULL;
    secondName = NULL;
    thirdName = NULL;
    */
    //   Set up for user input and program execution
    //   allocate space for directory input from user
    input_dir_name = (char *) malloc(NAMESIZE * sizeof(char));
    printf("HELLO Beautiful!!!!!\nSELECT THE FUNCTION YOU WANT TO EXECUTE:\n");
    printf("1. Find the 3 largest files in a directory\n");
    printf("2. List all zero length files in a directory\n");
    printf("3. Find all files with permission 777 in a directory\n");
    printf("4. Create a backup of a directory\n");
    printf("5. Exit\n");
    printf("\n");
    printf("PLEASE, ENTER YOUR CHOICE: ");
    scanf("%d", &choice);
    printf("Enter a directory name in the current directory: \n");
    /**********************************************************/
    /*Form a full path to the directory and check if it exists*/
    /**********************************************************/

    scanf("%s", input_dir_name);
    dirpath = (char *) malloc(NAMESIZE * sizeof(char));
    dirpath=getcwd(dirpath,NAMESIZE);
    strcat(dirpath,"/");
    strcat(dirpath,input_dir_name);
    
    if(choice == 1){
        printf("\nEXECUTING \"1. Find the 3 largest files in a directory\"\n");
	printf("\n %s", dirpath);
        traverseDirectory1(dirpath);
        /********************************************************/
        /**************Function to perform choice 1**************/
        /********************************************************/
        /* Step 1 iterates through directory */
        /* Step 2 if file then check size */
        /* Step 3 if size is bigger than smallest in array of files then insert into array */
        /* Step 4 if directory then go into directory and call function onto directory */
        /* Step 5 then print pathnames and sizes of files in array */
        printf("Largest File is: %d.\n", *largestName);
        printf("\nIts size is: ");
        printf("%i", largestFile);
        printf("Second Largest File is: %d.\n", *secondName);
        printf("\nIts size is: ");
        printf("%i", secondLarge);
        printf("Third Largest File is: %d.\n", *thirdName);
        printf("\nIts size is: ");
        printf("%i", thirdLarge);
    }
    else if(choice == 2){
        printf("\nEXECUTING \"2. List all zero length files in a directory\"\n");
        //call traverse directory with function parameter passed
        traverseDirectory2(dirpath);
        /********************************************************/
        /**************Function to perform choice 2**************/
        /********************************************************/
        /* Step 1 iterate through directory */
        /* Step 2 if file then check size */
        /* Step 3 if size is 0 then insert into array */
        /* Step 4 if directory then go into directory and call function onto directory */
        /* Step 5 then print pathnames in array */
    }

    else if(choice == 3){
        printf("\nEXECUTING \"3. Find all files with permission 777 in a directory\"\n");
        traverseDirectory3(dirpath);
        /********************************************************/
        /**************Function to perform choice 3**************/
        /********************************************************/
        /* Step 1 Ask for a permission number */
        /* Step 2 iterate through directory */
        /* Step 3 if file then check if has specified permission */
        /* Step 4 if yes array then insert into array */
        /* Step 5 if directory then go into directory and call function onto directory */
        /* Step 6 then print pathnames of files in array */
    }

    else if(choice == 4){
        printf("\nEXECUTING \"4. Create a backup of a directory\"\n");
        traverseDirectory4(dirpath);
        /********************************************************/
        /**************Function to perform choice 4**************/
        /********************************************************/
        /* Step 1 check if directory exists */
        /* Step 2 check if backup exists */
        /* Step 3 if backup exists  then move it to date/time appended location*/
        /* Step 4 then create new directory backup and then iterate through original directory and abstract iteration process in function*/
        /* Step 5 while iterating if file then copy into backup if directory then call function on that if symbolic link copy*/
    }
    //exit chosen
    else if(choice == 5){
        printf("\nWe hate to see you go, but love to see you leave!\n");
        exit(1);
    }

    else{
        printf("You were somehow unable to enter a number 1-5. You should feel bad.\n Program over and out.\n");
        exit(1);
    }
    free(input_dir_name);
    free(dirpath);
    return 0;
}
