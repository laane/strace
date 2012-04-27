
#include <string.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <signal.h>
#include <stdio.h>
#include "strace.h"

extern struct syscalls g_syscalls[];

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

  printf("\"");
  while ((c = ptrace(PTRACE_PEEKTEXT, pid, get_reg(infos, i) + j++, NULL)))
    printf("%c", c);
  printf("\"");
}

static void	print_int(struct user infos, int i, int pid)
{
  int		r;

  r = ptrace(PTRACE_PEEKTEXT, pid, get_reg(infos, i), NULL);
  printf("%d", r);
}

# define MATCH(x) (!strcmp(args[i], x))

void	print_args(char **args, struct user infos, int pid)
{
  for (int i = 0; args[i]; ++i) {
    if (!strcmp(args[i], "char*") || !strcmp(args[i], "const char*"))
      print_string(infos, i, pid);
    else if (!strcmp(args[i], "int") || MATCH("size_t"))
      print_int(infos, i, pid);
    /* else if (!strcmp(args[i], "off_t")) */
    /*   printf("%#lx", ptrace(PTRACE_PEEKTEXT, pid, */
    /* 				 get_reg(infos, i, 0), NULL)); */
    else
      printf("%s", args[i]);
    if (args[i+1])
      printf(", ");
  }
}
