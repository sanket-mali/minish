#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

//#include "find_command_path.h"
#include "execute_shell.h"


int main()
{
	//char *arg[]={"ls"};
	init_shell();
	do{
		//printf(">");
		char**command_input = read_input();
		if(strcmp(command_input[0],"exit")==0)
			break;
		execute_shell(command_input);
		printf("%s",get_username());
		printf(">");
	}while(1);
	return 0;
}

