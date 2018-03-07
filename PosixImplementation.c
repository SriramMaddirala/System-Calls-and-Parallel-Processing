/* 
Your last C# code is saved below:
***********************************************************************************************

 CSci 4061 Fall 2017
 Assignment# 4

 Student name: Sriram Pohar Maddirala
 Student ID:  5014900
 X500 id:    maddi011

 Operating system on which you tested your code: MacOS
 CSELABS machine: <Keller 4-250 computer 12>

***********************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/time.h>
#define NAMESIZE 256
#define TOKENSIZE 100
#define BUFSIZE 256
//defined struct to help pass string argument into traverseDirectory
typedef struct path
{
    char name[NAMESIZE];
}path;

//thread function to traverse directory 
void *traverseDirectory(void *arg){
    //initialize variables and constructs
    path pathname;
    int n;
    //set currentDirectory equal to the parameter passed in
    const char *currentDirectory = (((path*)arg)->name);
    pthread_t tid;
    void *thread_return_value;
    int *dirsum=(int *)malloc(sizeof(int));
    struct stat statbuf;
    struct dirent *direntry;
    DIR *opdirstrm;
    chdir(currentDirectory);
    stat(currentDirectory, &statbuf);
    //check to make sure directory is valid
    if(!S_ISDIR(statbuf.st_mode)){
        printf("%s\n", "Invalid directory, directory doesn't exist");
        exit(1);
    }
    //make sure there is no error on opening directory
    if((opdirstrm = opendir(currentDirectory)) == NULL){
        if(errno==ENOENT){
            printf("%s\n"," No such file or directory" );
        }
        perror("Error when opening directory");
        exit(1);
    }
    //read directory stream to iterate through contents
    while((direntry = readdir(opdirstrm))!=NULL){
        stat(direntry->d_name,&statbuf);
        //handle for directory errors due to "." and ".."
        if(strcmp(direntry->d_name,".")==0){
            continue;    
        }
        if(strcmp(direntry->d_name,"..")==0){
            continue;    
        }
        // handle for ds Store file in mac
        if(strcmp(direntry->d_name,".DS_Store")==0){
            continue;    
        }
        //check if directory
        if(direntry->d_type == DT_DIR){
            //get filepath
            char filepath[4096];
            strcpy(filepath, currentDirectory);
            strcat(filepath,"/");
            strcat(filepath, direntry->d_name);
            strcpy(pathname.name,filepath);
            //create new thread with pthread_create using current function recursively
            if(pthread_create(&tid,NULL,traverseDirectory,(void *)&pathname)!=0){
                perror("pthread_create");
                exit(1);
            }
            //wait for thread completion and save the directory sum of files from the terminated child thread
            if ( (n = pthread_join(tid, &thread_return_value)) ) { 
                fprintf(stderr,"pthread_join:%s\n",strerror(n));
                exit(1);
            }
            //print intermediate sum
            printf("DEBUG: ");
            printf("%s", filepath);
            printf(" ");
            printf("%d,\n",*(int*)thread_return_value);
            //add intermediate sum to current directory sum
            *dirsum = *dirsum + *(int*)thread_return_value;
        }
        if(direntry->d_type == DT_REG){
            //add file size to current directory sum
            *dirsum = statbuf.st_size + *dirsum;
        }
    }
    closedir(opdirstrm);
    // return current directory sum
    return (void *) dirsum;
}
//Set up main function
int main(int argc, char *argv[])
{
    //initialize constructs and variables
    int n;
    path pathname; 
    pthread_t td;
    void *thread_return_value;
    //initialize variables
    char *input_dir_name, *dirpath, *chptr;
    //   Set up for user input and program execution
    //   allocate space for directory input from user
    input_dir_name = (char *) malloc(NAMESIZE * sizeof(char));
    printf("Enter a directory name in the current directory: \n");
    //read in user input as directory path
    scanf("%s", input_dir_name);
    dirpath = (char *) malloc(NAMESIZE * sizeof(char));
    dirpath=getcwd(dirpath,NAMESIZE);
    strcat(dirpath,"/");
    strcat(dirpath,input_dir_name);
    strcpy(pathname.name,dirpath);
    printf("\nEXECUTING \" List Sum of all files in a directory\"\n");
    //call traverse directory with function parameter passed
    if (pthread_create(&td, NULL, traverseDirectory, (void *)&pathname) != 0) 
    {
        perror("pthread_create");
        exit(1);
    }
    //get final sum
    if ( (n = pthread_join(td, &thread_return_value)) ) 
    { 
            fprintf(stderr,"pthread_join:%s\n",strerror(n));
            exit(1);
    }
    //print final sum
    printf("The sum of the sizes of all the files is: ");
    printf("%i", *(int*)thread_return_value);
    printf("\n");
    //free the previously allocated spaces in memory
    free(input_dir_name);
    free(dirpath);
    return 0; 
}