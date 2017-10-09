#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void mysh_parse_command(const char* command,
                        int *argc, char*** argv)
{
	int cnt = 0;
	int i, j;
	char **temp_argv;

	temp_argv = (char**)malloc(sizeof(char*)*20);
	for( i = 0; i < 20; i++)
		temp_argv[i] = (char*)malloc(512);

	temp_argv[cnt] = strtok((char*)command, " ");
	cnt++;
	while(temp_argv[cnt] = strtok(NULL, " "))
		cnt++;
	temp_argv[cnt-1][strlen(temp_argv[cnt-1])-1] = '\0';

	*argc = cnt;
	*argv = temp_argv;
	
	return;
}


