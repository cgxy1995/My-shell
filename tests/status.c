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
	int pid;
	int status;
	if(!(pid=fork()))
	{
	    exit(2);
	}
	waitpid(pid,&status,0);
	if (WIFEXITED(status)) 
	    printf("%d %d\n", WEXITSTATUS(status),pid);
	if(!(pid=fork()))
	{
	    exit(2);
	}
	waitpid(pid,&status,0);
	if (WIFEXITED(status)) 
	    printf("%d %d\n", WEXITSTATUS(status),pid);
}