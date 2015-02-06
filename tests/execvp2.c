#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
int main(){
	char *echo[64];
	char str[10];
	//int saved_stdout = dup(1);
	echo[0] = "echo";
	echo[1] = "nihao";
	echo[2] = NULL;
	if(execvp(echo[0],echo)<0)
		printf("failed 1\n");
	//int fd = 3;
	//dup2(fd,1);
	/*echo[1] = "nihaoma";
	if(execvp(echo[0],echo)<0)
		printf("failed 2\n");*/
	//read(fd,str,strlen("nihao"));
	//dup2(saved_stdout,1);
	//write(1,str,strlen("nihao"));
	printf("aa.\n");
}