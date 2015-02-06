/* 
 * Skeleton code for Shell processing
 * This file contains skeleton code for executing commands parsed in main-x.c.
 * Acknowledgement: derived from UCLA CS111
 */

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
#include "cmdline.h"
#include "myshell.h"
 char curr_dir[512] = "/home/min/a/jiang85";
 int default_fd0 = 3;
 int default_fd1 = 4;
/** 
 * Reports the creation of a background job in the following format:
 *  [job_id] process_id
 * to stderr.
 */
void report_background_job(int job_id, int process_id);

/* command_exec(cmd, pass_pipefd)
 *
 *   Execute the single command specified in the 'cmd' command structure.
 *
 *   The 'pass_pipefd' argument is used for pipes.
 *   On input, '*pass_pipefd' is the file descriptor used to read the
 *   previous command's output.  That is, it's the read end of the previous
 *   pipe.  It equals STDIN_FILENO if there was no previous pipe.
 *   On output, command_exec should set '*pass_pipefd' to the file descriptor
 *   used for reading from THIS command's pipe.
 *   If this command didn't have a pipe -- that is, if cmd->commandop != PIPE
 *   -- then it should set '*pass_pipefd = STDIN_FILENO'.
 *
 *   Returns the process ID of the forked child, or < 0 if some system call
 *   fails.
 *
 *   You must also handle the internal commands "cd" and "exit".
 *   These are special because they must execute in the shell process, rather
 *   than a child.  (Why?)
 *
 *   However, these special commands still have a status!
 *   For example, "cd DIR" should return status 0 if we successfully change
 *   to the DIR directory, and status 1 otherwise.
 *   Thus, "cd /tmp && echo /tmp exists" should print "/tmp exists" to stdout
 *   iff the /tmp directory exists.
 *   Not only this, but redirections should work too!
 *   For example, "cd /tmp > foo" should create an empty file named 'foo';
 *   and "cd /tmp 2> foo" should print any error messages to 'foo'.
 *
 *   How can you return a status, and do redirections, for a command executed
 *   in the parent shell?
 *   Hint: It is easiest if you fork a child ANYWAY!
 *   You should divide functionality between the parent and the child.
 *   Some functions will be executed in each process.
 */
static pid_t
command_exec(command_t *cmd, int *pass_pipefd)
{
	pid_t pid = 0;		// process ID for child
	int pipefd[2];		// file descriptors for this process's pipe
	pipe(pipefd);
	//printf("%d.\n",pipefd[0]);
	/* EXERCISE: Complete this function!
	 * We've written some of the skeleton for you, but feel free to
	 * change it.
	 */
	// Create a pipe, if this command is the left-hand side of a pipe.
	// Return -1 if the pipe fails.
	if (cmd->controlop == CMD_PIPE) {
		//int i = pipe(pipefd);
		int i=0;
		//printf("%d %d\n",pipefd[0],pipefd[1]);
		//*pass_pipefd = pipefd[0];
		if(i)
			return -1;

		/* Your code here. */
	}
	/*if(pipefd[0]>30000 || pipefd[0]<-30000){
		pipefd[0]=2000;
		pipefd[1]=2000;
	}*/

	// Fork the child and execute the command in that child.
	// You will handle all redirections by manipulating file descriptors.
	//
	// This section is fairly long.  It is probably best to implement this
	// part in stages, checking it after each step.  For instance, first
	// implement just the fork and the execute in the child.  This should
	// allow you to execute simple commands like 'ls'.  Then add support
	// for redirections: commands like 'ls > foo' and 'cat < foo'.  Then
	// add parentheses, then pipes, and finally the internal commands
	// 'cd' and 'exit'.
	//
	// In the child, you should:
	//    1. Set up stdout to point to this command's pipe, if necessary.
	//    2. Set up stdin to point to the PREVIOUS command's pipe (that
	//       is, *pass_pipefd), if appropriate.
	//    3. Close some file descriptors.  Hint: Consider the read end
	//       of this process's pipe.
	//    4. Set up redirections.
	//       Hint: For output redirections (stdout and stderr), the 'mode'
	//       argument of open() should be set to 0666.
	//    5. Execute the command.
	//       There are some special cases:
	//       a. Parentheses.  Execute cmd->subshell.  (How?)
	//       b. A null command (no subshell, no arguments).
	//          Exit with status 0.
	//       c. "exit".
	//       d. "cd".
	//
	// In the parent, you should:
	//    1. Close some file descriptors.  Hint: Consider the write end
	//       of this command's pipe, and one other fd as well.
	//    2. Handle the special "exit" and "cd" commands.
	//    3. Set *pass_pipefd as appropriate.
	//
	// "cd" error note:
	// 	- Upon syntax errors: Display the message
	//	  "cd: Syntax error on bad number of arguments"
	// 	- Upon system call errors: Call perror("cd")
	//
	// "cd" Hints:
	//    For the "cd" command, you should change directories AFTER
	//    the fork(), not before it.  Why?
	//    Design some tests with 'bash' that will tell you the answer.
	//    For example, try "cd /tmp ; cd $HOME > foo".  In which directory
	//    does foo appear, /tmp or $HOME?  If you chdir() BEFORE the fork,
	//    in which directory would foo appear, /tmp or $HOME?
	//

	/* Your code here. */
	//if(cmd->controlop != CMD_PIPE)
	//if(*pass_pipefd==0)
	pid = fork();
	if(pid==0){ //child branch
		//simple echo first
		int cmd_ct=0;
		if(!strcmp(cmd->argv[cmd_ct],"echo")){
			char str[1024]="";
			while(cmd->argv[++cmd_ct]){
				/*if(cmd->controlop == CMD_PIPE){
					if(cmd_ct>1){
						write(pipefd[1], strcat(" ",cmd->argv[cmd_ct]), strlen(cmd->argv[cmd_ct])+1);
					}
					else{
						write(pipefd[1], cmd->argv[cmd_ct], strlen(cmd->argv[cmd_ct]));
					}
				}else{
					if(cmd_ct>1)
						printf(" %s",cmd->argv[cmd_ct]);
					else{
						printf("%s",cmd->argv[cmd_ct]);
						//printf("echoing\n");
					}
				}*/

				if(cmd_ct > 1){
					strcat(str," ");
					strcat(str,cmd->argv[cmd_ct]);
					//printf("%s?\n",str);
				}else{
					strcpy(str,cmd->argv[cmd_ct]);
					//printf("%s?\n",str);
				}
			}
			//printf("%d %s.\n",pipefd[0],str);
			write(pipefd[1], str, strlen(str));
			//printf(";%d %s.\n",pipefd[0],str);
			//read(pipefd[0], str, 10);
		//printf("lop:%d\n",cmd->controlop);
		//if(cmd->controlop != CMD_PIPE)
			//printf("\n");
		}else if(!strcmp(cmd->argv[cmd_ct],"cat")){
			char buf[65536];
			int file;
			if(*pass_pipefd > 0)
				file = *pass_pipefd;
			else 
				file = open(cmd->argv[++cmd_ct],O_RDONLY);
			read(file,buf,65536);//read file descriptor
			write(pipefd[1],buf,strlen(buf));
			//printf("%s %d.\n",buf,*pass_pipefd);
		}else if(!strcmp(cmd->argv[cmd_ct],"ls")){ // not required so use execvp
			char *ls[2];
			ls[0] = "ls";
			ls[1] = NULL;
			if(execvp(ls[0],ls)<0){
				printf("ls fails\n");
			}
		}else if(!strcmp(cmd->argv[cmd_ct],"pwd")){
			//if(cmd->controlop == CMD_PIPE)
			int i;
			if(write(pipefd[1], curr_dir, strlen(curr_dir))<0)
				printf("write %s into fd %d fails\n",curr_dir,pipefd[1]);
			//else
				//printf("%s\n",curr_dir);
		}else if(!strcmp(cmd->argv[cmd_ct],"ls")){

		}
		if(cmd->controlop == CMD_PIPE){
			//write(pipefd[1], cmd->argv[cmd_ct], strlen(cmd->argv[cmd_ct]));
			*pass_pipefd = pipefd[0];
			//printf("pass: %d %d\n",pipefd[0],pipefd[1]);
		}else{//to stdout
			char output[65536];
			read(pipefd[0],output,65536);
			printf("%s\n",output);
			//printf("%d %d %s.\n",pipefd[0],pipefd[1],output);
		}
		//close(pipefd[0]);
		//close(pipefd[1]);
		exit(0);
	}else{ //parent branch
		wait(NULL);
	}
	// return the child process ID
	return pid;
}


/* command_line_exec(cmdlist)
 *
 *   Execute the command list.
 *
 *   Execute each individual command with 'command_exec'.
 *   String commands together depending on the 'cmdlist->controlop' operators.
 *   Returns the exit status of the entire command list, which equals the
 *   exit status of the last completed command.
 *
 *   The operators have the following behavior:
 *
 *      CMD_END, CMD_SEMICOLON
 *                        Wait for command to exit.  Proceed to next command
 *                        regardless of status.
 *      CMD_AND           Wait for command to exit.  Proceed to next command
 *                        only if this command exited with status 0.  Otherwise
 *                        exit the whole command line.
 *      CMD_OR            Wait for command to exit.  Proceed to next command
 *                        only if this command exited with status != 0.
 *                        Otherwise exit the whole command line.
 *      CMD_BACKGROUND, CMD_PIPE
 *                        Do not wait for this command to exit.  Pretend it
 *                        had status 0, for the purpose of returning a value
 *                        from command_line_exec.
 */
int
command_line_exec(command_t *cmdlist)
{
	int cmd_status = 0;	    // status of last command executed
	int pipefd = STDIN_FILENO;  // read end of last pipe
	
	while (cmdlist) {
		int wp_status;	    // Hint: use for waitpid's status argument!
				    // Read the manual page for waitpid() to
				    // see how to get the command's exit
				    // status (cmd_status) from this value.

		// TODO: Fill out this function!
		// If an error occurs in command_exec, feel free to abort().
		
		/* Your code here. */
		//printf("executing %s %s\n",cmdlist->argv[0],cmdlist->argv[1]);
		//printf("cmd:%s\n",cmdlist->argv[0]);
		cmd_status = command_exec(cmdlist,&pipefd);
		cmdlist = cmdlist->next;
		fflush(stdout);
	}

done:
	return cmd_status;
}

void report_background_job(int job_id, int process_id) {
    fprintf(stderr, "[%d] %d\n", job_id, process_id);
}
