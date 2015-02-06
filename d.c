#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "cmdline.h"
#include "myshell.h"

int main(){
  char *unlink[24];
	unlink[0] = "unlink";
	unlink[1] = "dummy_d";
	if(remove("dummy_d")<0)
	    printf("delete fails\n");
return 0;
}
