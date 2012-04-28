
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include "strace.h"

static char **	get_syscalls(void)
{
  char		**ret;
  size_t	i, j, len, size;
  FILE*		fd;

  if ((fd = fopen("syscall_db", "r")) == NULL)
    return NULL;
  size = 50;
  ret = malloc(size * sizeof(*ret));
  i = 0;
  ret[i] = NULL;
  while (getline(&ret[i], &len, fd) != -1)
    {
      for (j = 0; ret[i][j] && ret[i][j] != '\n'; ++j);
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

static void	free_strtab(char **tab)
{
  size_t	i;

  for (i = 0; tab[i]; ++i)
    free(tab[i]);
}

extern char	**environ;

static char	*getbinary(char *arg)
{
  char		*path = getenv("PATH");
  char		*p;
  char		*bin;

  if (0 == access(arg, X_OK))
    return arg;
  if (!path)
    {
      if (0 != access(arg, X_OK))
	return NULL;
      return arg;
    }
  while ((p = strtok(path, ":")))
    {
      bin = strdup(p);
      bin = realloc(bin, strlen(bin) + strlen(arg) + 10);
      bin = strcat(bin, "/");
      bin = strcat(bin, arg);
      if (0 == access(bin, X_OK))
	return bin;
      free(bin);
      path = NULL;
      p = NULL;
    }
  return NULL;
}

int		main(int ac, char **av)
{
  char		**syscall_strtab;
  char		*bin;
  pid_t		pid;

  if (ac != 2)
    return usage();
  /* if (access(av[1], X_OK)) */
  if (NULL == (bin = getbinary(av[1])))
    {
      fprintf(stderr, "File %s doesnt exist or has not execute permissions\n",
  	      av[1]);
      return 1;
    }
  syscall_strtab = get_syscalls();
  if (syscall_strtab == NULL)
    exit_error("file syscall_db unreachable");
  if ((pid = fork()) == -1)
    exit_error("fork fail");
  if (!pid) /* child */
    exec_child(bin);
  else /* parent */
    exec_parent(pid, syscall_strtab);
  free_strtab(syscall_strtab);
  return 0;
}
