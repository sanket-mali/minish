#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "find_command_path.h"
#define clear() printf("\033[H\033[J") 

char *get_username()
{
    char *uname=getlogin();
    if(uname==NULL)
    {
        uname = "";
    }
    return uname;
}

char ** read_input()
{
    char *command = (char*)malloc(sizeof(char)*100);
	char **command_input = (char**)malloc(sizeof(char*)*50);
	fgets(command,100,stdin);
	//puts(command);
	char *token;
	int i=0;
	for(token=strtok(command," ");token;token=strtok(NULL," "))
	{
		//puts(token);
		command_input[i] = (char *)malloc(sizeof(token));
		strcpy((command_input[i]), token);
        //puts(command_input[i]);
		i++;
	}
	command_input[i] = NULL;
	//puts(command_input[1]);
    //printf("i: %d\n",i);
	command_input[i-1][strlen(command_input[i-1])-1]='\0';
	/*if(command_input[0][2]=='\n')
		puts("ok");
	/*printf("%c",command_input[0][1]);
	printf("%ld\n",strlen(command_input[0]));*/
	//strcpy((*command_input) , NULL);
	//(*command)[1] = NULL;
    return command_input;
}

void init_shell()
{
    clear();
    printf("===============================================\n");
    printf("===============================================\n");
    printf("===============================================\n");
    printf("      _       _  ______  _         ______\n");
    printf("     | \\    / | |_   _| | \\    |  |_   _|\n");
    printf("     |  \\  /  |   | |   |  \\   |    | |\n");
    printf("     |   \\/   |   | |   |   \\  |    | |\n");
    printf("     |        |  _| |_  |    \\ |   _| |_\n");
    printf("     |        | |____|  |     _|  |____|\n");
    printf("===============================================\n");
    printf("==================== SHELL ====================\n");
    printf("===============================================\n");    
    char *uname = get_username();
    printf("%s",uname);
    printf(">");
}

void execute_shell(char **command)
{
	pid_t pid;
	int es;
	pid = fork();
	
	if(pid==-1)
	{
		printf("Something went wrong\n");
		exit(0);
	}
	else if(pid)
	{
		//sleep(1);
		//printf("This is the parent process with PID: %u\n",getpid());
		//printf("My child's PID: %u\n",pid);
		//printf("Waiting for child to exit..\n");
		wait(&es);
		//printf("Child exit status: %u\n",WEXITSTATUS(es));
	}
	else
	{
		//printf("This is the child process with PID: %u\n",getpid());
		//printf("My parent's PID: %u\n",getppid());
		//printf("Waiting for child to exit..\n");
		//char *res = getenv("PATH");
		//char *arg[]={"pwd",NULL};
		char *path = find_command_path(command[0]);
        //puts(">");
		execv(path,command);
		exit(es);
	}
}