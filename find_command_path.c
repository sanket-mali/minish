/*
//find_command_path.c
//Author: Sanket Kumar Mali
//Determine if a program exist or not by searching in the
//system environment variable
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "find_command_path.h"

//check if a program exist or not
int is_program_exist(char *prog)
{
    if(access(prog,F_OK)!=-1)
        return 1;
    else
        return 0;
}
char * find_command_path(char *prog_name)
{
    char *dup = strdup(getenv("PATH"));
    char *dir;
    char *path;
    //prog_name = "ls";
    //puts("This is find");
    //puts(prog_name);
    for(dir=strtok(dup,":");dir;dir=strtok(NULL,":"))
    {
        path=(char *)malloc(sizeof(dir)+sizeof(prog_name+1));
        path = strcat(path,dir);
        path = strcat(path,"/");
        path = strcat(path,prog_name);
        //puts(path);
        //printf("exist: %d\n",is_program_exist(path));
        if(is_program_exist(path))
        {
            //printf("exist: %d\n",is_program_exist(path));
            break;
        }
        path = "";
    }
    return path;
    free(dup);
    free(path);
}

/*int main(int argc,char **argv)
{
    puts(find_command_path(argv[1]));
}*/