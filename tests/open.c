#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
 
int main()
{
  int fd[2];
  char str[100];
  int a=3;
  pipe(fd);
  write(fd[1],"hello ",strlen("hello "));
  write(fd[1],"world\n",strlen("hello"));
  //dup2(a,fd[0]);
  //lseek(a,0,SEEK_SET);
  //if(lseek(a,0,SEEK_END)==-1)
  	//printf("cant seek\n");
  read(fd[0],str,100);
  printf("done %s\n",str);
}

