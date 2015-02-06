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

int main(){
	char *echo[3];
	echo[0] = "echo";
	echo[1] = "haha";
	echo[2] = NULL;
	int stdout = dup(1);
	int fd[2];
	pipe(fd);
	dup2(5,1);
	//dup2(stdout,1);
	if(!fork())
		execvp(echo[0],echo);
}