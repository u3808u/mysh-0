#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "utils.h"

static void release_argv(int argc, char*** argv);

int main()
{
  char buf[8096]="";
  int argc = 0;
  char** argv;

  while (1) {
    fgets(buf, 8096, stdin);

    mysh_parse_command(buf, &argc, &argv);

    if (strcmp(argv[0], "") == 0) {
      goto release_and_continue;
    } else if (strcmp(argv[0], "cd") == 0) {
      if (do_cd(argc, argv)) {
        fprintf(stderr, "cd: Invalid arguments\n");
      }
    } else if (strcmp(argv[0], "pwd") == 0) {
      if (do_pwd(argc, argv)) {
        fprintf(stderr, "pwd: Invalid arguments\n");
      }
    } else if (strcmp(argv[0], "exit") == 0) {
      goto release_and_exit;
    } else {
      fprintf(stderr, "%s: command not found\n", argv[0]);
    }
release_and_continue:
    release_argv(argc, &argv);
    continue;
release_and_exit:
    release_argv(argc, &argv);
    return 0;
  }

  return 0;
}

static void release_argv(int argc, char*** argv) {
  free(*argv);
  *argv = NULL;
}
