#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main (int argc, char ** argv) {
    int i;
    printf("%d\n",argc);
    for( i=1; i<argc-1; i++)
    {
    	printf("%s\n",argv[i]);
    	abort();
    }
    for( i=1; i<argc-1; i++)
    {
        int pd[2];
        pipe(pd);
        printf("%s\n",argv[i]);
        if (!fork()) {
            dup2(pd[1], 1); // remap output back to paren
            execlp(argv[i], argv[i], NULL);
            perror("exec");
            abort();
        }

        // remap output from previous child to input
        dup2(pd[0], 0);
        close(pd[1]);
    }

    execlp(argv[i], argv[i], NULL);
    perror("exec");
    abort();
}
