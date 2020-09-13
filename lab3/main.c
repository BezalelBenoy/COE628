/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Bezalel Benoy
 *          500817911
 *
 * Created on February 4, 2020, 8:38 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


void  parse(char *line, char **argv)
{
     while (*line != '\0') {       
          while (*line == ' & ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     
          *argv++ = line;          
          while (*line != '\0' && *line != '& ' && *line != '\t' && *line != '\n')
               line++;             
    }
     *argv = '\0';              
}

     
void  execute(char **argv)
{
     pid_t  pid;
     int    status;
     
     if ((pid = fork()) < 0) {     
          printf(" forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          
          if (execvp(*argv, argv) < 0) {     
               printf("exec failed\n");
               exit(1);
          }
     }
     else {                                 
          while (wait(&status) != pid)      
               ;
     }
}


     
void  main(void)
{
     char  line[1024];             
     char  *argv[64];             
     
     while (1) {                   
          printf("Your Command> ");     
          gets(line);              
          printf("\n");
          parse(line, argv);       
          if (strcmp(argv[0], "exit") == 0)  
               exit(0);           
          execute(argv);         
     }
}

// not fully functional yet, going to try to finish by thursday