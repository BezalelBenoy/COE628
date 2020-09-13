/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Bezalel Benoy
 * 500817911
 *
 * Created on February 13, 2020, 1:17 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<string.h>

#define GIVEN_COMMAND 1024
#define READ_IN 64
#define FILE_PATH 20

int main(int argc,char* argv[GIVEN_COMMAND] ){ 
    char commandline[READ_IN];  
    char progpath[FILE_PATH];      
    char* path= "/bin/";    
   

while(1){

    printf("Your command>");                    

      if(!fgets(commandline, READ_IN, stdin)) 
     
        break;
    
    size_t stringlength = strlen(commandline); 
    
    
    
    if(strcmp(commandline, "exit\n")==0){          
        break;
    }
    if (commandline[stringlength - 1] == '\n'){ 
    commandline[stringlength - 1] = '\0'; 
    }

    char *split;                
    split= strtok(commandline," ");
    int index=0;
    while(split!= NULL){
        argv[index]=split;      
        split = strtok(NULL," ");
        index++;
    }
    argv[index]=NULL;                     

    argc=index;                           
    for(index=0; index<argc; index++){
        printf("%s\n", argv[index]);    
    }
    strcpy(progpath, path);           
    strcat(progpath, argv[0]);           

    for(index=0; index<strlen(progpath); index++){    
        if(progpath[index]=='\n'){      
            progpath[index]='\0';
        }
    }
    int pid= fork();            
    if (pid ==-1)
    {
        printf("Cannot fork process\n"); 
        return 0;
    }
    else if(pid==0){         //Child Process      
        execvp(progpath,argv);
        printf("Child process: PID is %d and parent ID is %d.\n", getpid(), getppid());
        fprintf(stderr, "Child process could not execute\n");
    }else{                  //Parent Process  
        wait(NULL);
        printf("Parent process: PID is %d and parent ID is %d.\n", getpid(), pid);
        printf("Child exit\n");
    }

}
} 

