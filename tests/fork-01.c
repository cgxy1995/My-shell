#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define   MAX_COUNT  1

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */
int fd[2];
void  main(void)
{
     pid_t  pid;
     
     pipe(fd);
     pid = fork();
     if (pid == 0) 
          ChildProcess();
     else 
          ParentProcess();
}

void  ChildProcess(void)
{
     /*int   i;

     for (i = 1; i <= MAX_COUNT; i++)
          printf("   This line is from child, value = %d\n", i);
     printf("   *** Child process is done ***\n");*/
     write(fd[1],"hello",strlen("hello"));
     exit(0);
}

void  ParentProcess(void)
{
     char str[10];
     int i;
     /*int   i;
     
     for (i = 1; i <= MAX_COUNT; i++)
          printf("This line is from parent, value = %d\n", i);
     printf("*** Parent is done ***\n");*/
     wait(NULL);
     read(fd[0],str,10);
     //printf("%s.\n",str);
     for(i=0;i<strlen(str);i++){
          printf("%d ",str[i]);
     }
     printf("\n");
     str[i]='\0';
     printf("%s\n",str);
}
