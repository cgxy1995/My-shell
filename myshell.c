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
	int status=0;
	//int stdin_cp = dup(0);
	//int stdout_cp = dup(1);
	/* EXERCISE: Complete this function!
	 * We've written some of the skeleton for you, but feel free to
	 * change it.
	 */
	// Create a pipe, if this command is the left-hand side of a pipe.
	// Return -1 if the pipe fails.
	if (cmd->controlop == CMD_PIPE) {
		int i = pipe(pipefd);
		
		//int i=0;
		//printf("%d %d\n",pipefd[0],pipefd[1]);
		
		//if(i)
		//	return -1;

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
	char empty = '\0';
	pid = fork();
	if(pid==0){ //child branch
		//simple echo first
		int stdout = dup(1);
		int cmd_ct=0;
		dup2(*pass_pipefd,0);
		if(cmd->controlop == CMD_PIPE || cmd->controlop == CMD_BACKGROUND)
			setsid();
		if(!strcmp(cmd->argv[0],"true")){
			//if(cmd->controlop == CMD_END)
			//	printf("%c",empty);
			exit(0);
		}else if(!strcmp(cmd->argv[0],"false")){
			//if(cmd->controlop == CMD_END)
			//	printf("%c",empty);
			exit(1);
		}else if(!strcmp(cmd->argv[0],"(")){
			char out[2048];
			int dfd[2];
			int fd_read,fd_write,fd_2write;
			pipe(dfd);
			if(cmd->redirect_filename[0]){
					fd_read = open(cmd->redirect_filename[0],O_RDONLY , 0777);
					dup2(fd_read,0);
			}
			if(cmd->controlop == CMD_PIPE){
				dup2(pipefd[1],1);
				status = command_line_exec(cmd->subshell);
			}
			else if(cmd->redirect_filename[1] || cmd->redirect_filename[2]){
				dup2(dfd[1],1);
				status = command_line_exec(cmd->subshell);
				read(dfd[0],out,2048);
				close(dfd[0]);
				dup2(stdout,1);
				if(cmd->redirect_filename[1]){
					fd_write = open(cmd->redirect_filename[1],O_WRONLY | O_CREAT | O_TRUNC, 0777);
					write(fd_write,out,strlen(out));
					close(fd_write);
				}
				if(cmd->redirect_filename[2]){
					fd_2write = open(cmd->redirect_filename[2],O_WRONLY | O_CREAT | O_TRUNC , 0777);
					write(fd_2write,out,strlen(out));
					close(fd_2write);
				}
				if(!cmd->redirect_filename[2] && !cmd->redirect_filename[1]){
					printf("%s",out);
				}
			}else{
				//printf("in\n");
				//dup2(dfd[1],1);
				status = command_line_exec(cmd->subshell);
				//if(cmd->controlop == CMD_END || cmd->controlop == CMD_BACKGROUND){
					//close(dfd[1]);
					/*dup2(stdout,1);
					write(dfd[1],"\0",1);
					read(dfd[0],out,2048);
					dup2(stdout,1);
					close(dfd[1]);
					printf("%s",out);*/
				
			}
		}
		else if(strcmp(cmd->argv[0],"cd") || strcmp(cmd->argv[0],"exit")){ //if not cd
			char *arg[1024];
			arg[0] = cmd->argv[0];
			int i = 1;
			int fd_read,fd_write,fd_2write;
			if(cmd->controlop == CMD_PIPE){
				dup2(pipefd[1],1);
			}
			if(cmd->redirect_filename[1]){
				fd_write = open(cmd->redirect_filename[1],O_WRONLY | O_CREAT | O_TRUNC, 0777);
				dup2(fd_write,1);
			}
			if(cmd->redirect_filename[0]){
				fd_read = open(cmd->redirect_filename[0],O_RDONLY , 0777);
				dup2(fd_read,0);
			}
			if(cmd->redirect_filename[2]){
				fd_2write = open(cmd->redirect_filename[2],O_WRONLY | O_CREAT | O_TRUNC , 0777);
				dup2(fd_2write,2);
			}
			if(execvp(cmd->argv[0],cmd->argv)<0)
				exit(0);
				//printf("%s fails\n",arg[0]);
		}
		exit(WEXITSTATUS(status));
	}else{ //parent branch
		int cmd_ct=0;
		//wait(NULL);
		if(cmd->controlop == CMD_PIPE){
			*pass_pipefd = pipefd[0];
			return pid;
		}
		//printf("zhihou\n");
		if(!strcmp(cmd->argv[cmd_ct],"cd")){ //cd must be in parent
			char *dir;
			dir = getenv("PWD");
			//printf("%s\n",dir);
			if(!strcmp(cmd->argv[cmd_ct+1],"..")){
				unsigned i; int pos=0;
				for(i=0;i<strlen(dir);i++){
					if(dir[i]=='/')
						pos=i;
				}
				dir[pos] = '\0';
				if(chdir(dir)){
					pid=fork();
					if(!pid)
						exit(1);
				}
					//printf("Directory %s does not exist\n",dir);
			}else if(!strcmp(cmd->argv[cmd_ct+1],"/")){
				dir = "/";
				if(chdir(dir)<0){
					pid=fork();
					if(!pid)
						exit(1);
				}
					//printf("Directory %s does not exist\n",dir);
			}else if(cmd->argv[cmd_ct+1][0] == '/'){
				if(chdir(cmd->argv[cmd_ct+1])<0){
					pid=fork();
					if(!pid)
						exit(1);
				}
					//printf("Directory %s does not exist\n",cmd->argv[cmd_ct+1]);
			}
			else{
				strcat(dir,"/");
				strcat(dir,cmd->argv[cmd_ct+1]);
				if(chdir(dir)<0){
					pid=fork();
					if(!pid)
						exit(1);
				}
					//printf("Directory %s does not exist\n",dir);
		    }
		}else if(!strcmp(cmd->argv[0],"exit")){
			exit(0);
		}
		return pid;
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
	int wp_status;
	int to_wait[1024];
	int i;
	char empty = '\0';
	for(i=0;i<1024;i++)
		to_wait[i] = 0;
	i=0;
	while (cmdlist) {
		//int wp_status;	    // Hint: use for waitpid's status argument!
				    // Read the manual page for waitpid() to
				    // see how to get the command's exit
				    // status (cmd_status) from this value.
		// TODO: Fill out this function!
		// If an error occurs in command_exec, feel free to abort().
		
		/* Your code here. */
		if(cmdlist->argv[0] == NULL)
			goto skip;
		cmd_status = command_exec(cmdlist,&pipefd);
		//to_wait[i++] = cmd_status;
		if(cmdlist->controlop == CMD_BACKGROUND){
			//to_wait[i++] = cmd_status;
		}else if(cmdlist->controlop == CMD_PIPE)
			close(pipefd+1); //close write end if pipe
		else{
			int j=0;
			//while(to_wait[j]){
				//printf("waiting\n");
				//waitpid(to_wait[j], &wp_status, 0);
			waitpid(cmd_status, &wp_status, 0);
				//to_wait[j++] = 0;
			//}
			i=0;
		}
		skip:
		//if(cmdlist->controlop == CMD_END)
				//printf("%c",NULL);
		//printf("%s %d %d\n",cmdlist->argv[0],WEXITSTATUS(wp_status),cmd_status);
		if(cmdlist->controlop == CMD_AND){
			if(WEXITSTATUS(wp_status) != 0){
				return wp_status;
			}
		}else if(cmdlist->controlop == CMD_OR){
			if(WEXITSTATUS(wp_status) == 0){
				return wp_status;
			}
		}
		//printf("pid %d status: %d %d\n",cmd_status,WEXITSTATUS(wp_status),WIFEXITED(wp_status));
		cmdlist = cmdlist->next;
		fflush(stdout);
	}

done:
	//return cmd_status; //cmd_status
	return wp_status;
}

void report_background_job(int job_id, int process_id) {
    fprintf(stderr, "[%d] %d\n", job_id, process_id);
}
void delete_file(char *file){
	char *unlink[24];
	unlink[0] = "unlink";
	unlink[1] = file;
	execvp(unlink[0],unlink);
}
