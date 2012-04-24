
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include "strace.h"

static void	get_syscall(int pid)
{
  static char	flag = 1;

  (void)pid;
  if (flag)
    printf("syscall ...");
  else
    printf(" ret\n");
  flag = !flag;
}

static void	trace_process(int pid)
{
  int		status;
  long		ret;

  while (1)
    {
      wait4(pid, &status, WUNTRACED, NULL);
      if (status == 0)
	break;
      /* if (is_a_syscall(pid)) */
      get_syscall(pid);
      ptrace(PTRACE_SYSCALL, pid, NULL, 0);
    }
}

void		exec_parent(int pid)
{
  if (ptrace(PTRACE_ATTACH, pid, NULL, 0) == -1)
    {
      kill(pid, SIGKILL);
      exit_error("Cannot attach parent process");
    }
  trace_process(pid);
}
