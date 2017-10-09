#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"
#include <string.h>
int do_cd(int argc, char** argv) {
	int wherecd = 0;
	int cdwant = 0;
	wherecd = validate_cd_argv(argc,argv);
	char* directory;
	directory = (char*)malloc(1024);
	char** token;
	token = (char**)malloc(128);
	for(int j = 0; j<128;j++){
		token[j] = (char*)malloc(256);
	}
	getcwd(directory,1024);
	char* tmp = (char*)malloc(1024);
	getcwd(tmp,1024);
	token[0] = strtok(directory, "/");
	for(int x =1;token[x]!=NULL;x++){
		token[x]=token[x-1];
		token[x] = strtok(NULL, "/");
	}
	tmp = strtok(directory, "/");
	int i = 0;
	char** count = (char**)malloc(128);
	for(int j = 0;j<128;j++){
		count[j] = (char*)malloc(256);
		count[j] = token[j];
	}
	for(cdwant=0;count[cdwant]!=NULL;cdwant++)
	{count[cdwant] = strtok(NULL,"/");}
	char** temp = (char**)malloc(3);
	for(int j = 0;j<3;j++){
		temp[j] = (char*)malloc(256);
	}

	if (!wherecd)
		return -1;
	else
	{
		if(!strcmp(*(argv+wherecd),".."))
	{
			getcwd(temp[0],256);
			temp[1] = token[cdwant-2];
			if(!strcmp(temp[0],"/home")){
				chdir("/");
			}
			else if(!strcmp(temp[0],"/")){
				printf("You are in root.\n");
				return 0;
			}
			else{
				char* loc1 = strstr(temp[0],temp[1]);
				char* loc2 = loc1 + strlen(temp[1]);
				for(int y = 0;*(loc2+y)!='\0';y++)
					*(loc2+y) = '\0';
				chdir(temp[0]);
			}
			getcwd(directory,1024);
			printf("%s\n", directory);
		}
		else if(!strcmp(*(argv+wherecd),"~"))
		{
			chdir("/home");
			getcwd(directory,1024);
			printf("%s\n", directory);
		}
		else if(!strcmp(*(argv+wherecd),"."))
		{
			getcwd(directory,1024);
			printf("%s\n",directory);
		}
		else if(!strcmp(*(argv+wherecd),"/"))
		{
			chdir("/");
			getcwd(directory,1024);
			printf("%s\n",directory);
		}
		else
		{
			/*getcwd(directory,1024);
			printf("directory:%s\n",directory);
			char* loc3 = (char*)malloc(512);
			printf("loc3:%s\n",loc3);
			loc3 = strstr(directory,*(argv+wherecd));
			printf("%s\n",loc3);
			if(loc3!=NULL){
				char* temporary = (char*)malloc(512);
				temporary = loc3 + strlen(*(argv+wherecd));
				printf("%s\n",temporary);
				for(int x = 0;x<strlen(*(argv+wherecd));x++){
					temporary[x] = '\0';
				}					
				chdir(directory);
				getcwd(directory,1024);
				printf("%s\n",directory);
			}
			else{
				char* temporary1 = (char*)malloc(512);
				for(int x = 0;x<strlen(*(argv+wherecd));x++){
					temporary[x+2] = argv[wherecd+x];
				}
				temporary[0] = '/';
				y = chdir();
				if(y != 0)*/
					printf("There is no file or directory : %s\n", *(argv+wherecd));
			//}
		}
	}
  return 0;
}

int do_pwd(int argc, char** argv) {
	if (!validate_pwd_argv(argc, argv))
		return -1;
        char* directory = "";
        directory = (char*)malloc(512);
	getcwd(directory,512);
	printf("%s\n",directory);
	
	return 0;
}

int validate_cd_argv(int argc, char** argv) {
	int i = 1;
	for(i = 1;i<=argc;i++)
	{
		if(!strcmp(*(argv+i-1),"cd"))
		{
			return i;
		}
		else
			continue;
	}
	if(i==argc)
		return 0;
}

int validate_pwd_argv(int argc, char** argv) {
	int i = 1;
	for(i = 1;i<=argc;i++)
	{
		if(!strcmp(*(argv+i-1),"pwd"))
		{
			return i;
		}
		else
			continue;
	}
	if(i==argc)
		return 0;
}
