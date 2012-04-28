
#include <string.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include "strace.h"

/* extern struct syscalls g_syscalls[]; */

static unsigned long	get_reg(struct user info, int i)
{
  if (i == 0)
    return (info.regs.rdi);
  if (i == 1)
    return (info.regs.rsi);
  if (i == 2)
    return (info.regs.rdx);
  if (i == 3)
    return (info.regs.rcx);
  if (i == 4)
    return (info.regs.r8);
  if (i == 5)
    return (info.regs.r9);
  return 0;
}

static void	print_string(struct user infos, int i, int pid)
{
  char		c;
  int		j = 0;

  fprintf(stderr, "\"");
  while ((c = ptrace(PTRACE_PEEKTEXT, pid, get_reg(infos, i) + j++, NULL))
	 && j < 60)
    fprintf(stderr, (c == '\n') ? "\\n" : "%c", c);
  fprintf(stderr, "\"");
  if (j == 60)
    fprintf(stderr, "...");
}

static int	count_args(struct user infos, int i, int pid)
{
  int		j = 0;

  while (ptrace(PTRACE_PEEKTEXT, pid, get_reg(infos, i) + j, NULL))
    j += sizeof(long);
  return j / sizeof(long);
}

static void	print_strtab(struct user infos, int i, int pid)
{
  char		c;
  int		nb;
  long		addr;
  int		j = 0;

  if ((nb = count_args(infos, i, pid)) > 3)
    {    fprintf(stderr, "[/* %d vars */]", nb);      return ;    }
  fprintf(stderr, "[");
  while ((addr = ptrace(PTRACE_PEEKTEXT, pid, get_reg(infos, i) + j, NULL)))
    {
      int	k = 0;
      fprintf(stderr, "\"");
      while ((c = ptrace(PTRACE_PEEKTEXT, pid, addr + k++, NULL)) && k < 60)
  	fprintf(stderr, (c == '\n') ? "\\n" : "%c", c);
      fprintf(stderr, "\"");
      if (k == 60)
	fprintf(stderr, "...");
      j += sizeof(long);
      if (ptrace(PTRACE_PEEKTEXT, pid, get_reg(infos, i) + j, NULL))
	fprintf(stderr, ", ");
    }
  fprintf(stderr, "]");
}

# define MATCH(x) (!strcmp(args[i], x))

void	print_args(const char *call, char **args, struct user infos, int pid)
{
  for (int i = 0; args[i]; ++i) {
    if (MATCH("char*")
	|| (!strcmp(call, "write")
	    && (MATCH("void*") || MATCH("void*"))))
      print_string(infos, i, pid);
    else if (MATCH("int") || MATCH("size_t"))
      fprintf(stderr, "%d", (int)get_reg(infos, i));
    else if (MATCH("off_t"))
      fprintf(stderr, "%lu", get_reg(infos, i));
    else if (MATCH("void*") || MATCH("unsigned long"))
      fprintf(stderr, !get_reg(infos, i) && !strcmp(call, "mmap") ?
	      "NULL" : "%#lx", get_reg(infos, i));
    else if (MATCH("char**") &&
	     (!strcmp(call, "execve")))
      print_strtab(infos, i, pid);
    else
      fprintf(stderr, "%s", args[i]);
    if (args[i+1])
      fprintf(stderr, ", ");
  }
}
