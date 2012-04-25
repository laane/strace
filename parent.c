
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <signal.h>
#include <stdio.h>
#include "strace.h"

static void	get_syscall(int pid, char **strtab)
{
  static char	flag = 1;
  struct user	infos;

  if (ptrace(PTRACE_GETREGS, pid, NULL, &infos) == -1)
    {      printf("getregs fail\n");      return ;    }
  if (flag)
    printf("syscall: %s ...", strtab[(int)infos.regs.orig_rax]);
  else
    printf(" ret 0x%x\n", (int)infos.regs.rax);
  flag = !flag;
}

static void	trace_process(int pid, char **strtab)
{
  int		status;

  while (1)
    {
      wait4(pid, &status, WUNTRACED, NULL);
      if (status == 0)
	break;
      /* if (is_a_syscall(pid)) */
      get_syscall(pid, strtab);
      ptrace(PTRACE_SYSCALL, pid, NULL, 0);
    }
}

void		exec_parent(int pid, char **strtab)
{
  if (ptrace(PTRACE_ATTACH, pid, NULL, 0) == -1)
    {
      kill(pid, SIGKILL);
      exit_error("Cannot attach parent process");
    }
  trace_process(pid, strtab);
}
