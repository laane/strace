
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include "strace.h"

static char **	get_syscalls(void)
{
  char		**ret;
  size_t	len;
  size_t	size;
  size_t	i, j;
  FILE*		fd;

  if ((fd = fopen("syscall_db", "r")) == NULL)
    return NULL;
  size = 50;
  ret = malloc(size * sizeof(*ret));
  i = 0;
  ret[i] = NULL;
  len = 0;
  while (getline(&ret[i], &len, fd) != -1)
    {
      len = 0;
      for (j = 0; ret[i][j] && ret[i][j] != ' ' && ret[i][j] != '\t'; ++j);
      ret[i][j] = 0;
      if (++i == size)
	{
	  size += 50;
	  if ((ret = realloc(ret, size * sizeof(*ret))) == NULL)
	    perror("realloc fail");
	}
      ret[i] = NULL;
    }
  return ret;
}

static int	usage(void)
{
  fprintf(stderr, "Usage: ./strace file_to_trace\n");
  return 1;
}

int		main(int ac, char **av)
{
  char		**syscall_strtab;
  pid_t		pid;

  if (ac != 2)
    return usage();
  if (access(av[1], X_OK))
    {
      fprintf(stderr, "File %s doesnt exist or has not execute permissions\n",
  	      av[1]);
      return 1;
    }
  syscall_strtab = get_syscalls();
  if (syscall_strtab == NULL)
    perror("pas de fichier");
  if ((pid = fork()) == -1)
    exit_error("fork fail");
  if (!pid) /* child */
    exec_child(av[1]);
  else /* parent */
    exec_parent(pid, syscall_strtab);
  return 0;
}
