
#include <unistd.h>
#include <stdio.h>
#include "strace.h"

static int	usage(void)
{
  fprintf(stderr, "Usage: ./strace file_to_trace\n");
  return 1;
}

int		main(int ac, char **av)
{
  pid_t		pid;

  if (ac != 2)
    return usage();
  if (access(av[1], X_OK))
    {
      fprintf(stderr, "File %s doesnt exist or has not execute permissions\n", av[1]);
      return 1;
    }
  if ((pid = fork()) == -1)
    exit_error("fork fail");
  if (!pid) // child
    exec_child(av[1]);
  else // parent
    exec_parent(pid);
  return 0;
}
