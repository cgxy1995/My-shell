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
	int pipefd[2];
	int pd[2];
	pipe(pd);
	if(!fork()){
		dup2(pd[1],1);
		char *echo[10] = {"echo","haha"};
		execvp(echo[0],echo);
		abort();
	}
	dup2(pd[0],0);
	close(pd[1]);
/*
	pipe(pd);
	if(!fork()){
		dup2(pd[1],1);
		execlp("grep","grep",NULL);
		abort();
	}
	dup2(pd[0],0);
	close(pd[1]);*/

if(!fork()){
	char *ls[10];
	ls[0] = "rev";
	ls[1] = NULL;
	execvp(ls[0],ls);
	abort();
}else
    wait(NULL);
	return 0;
}