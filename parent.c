
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <signal.h>
#include <stdio.h>
#include "strace.h"

static int	get_syscall(int pid, char **strtab)
{
  struct user	infos;
  long		word;
  int		status;

  if (ptrace(PTRACE_GETREGS, pid, NULL, &infos) == -1)
    {      printf("getregs fail\n");      return 1;    }
  word = ptrace(PTRACE_PEEKTEXT, pid, infos.regs.rip, NULL);
  if ((word & 0xFFFF) != 0x050F)
    return 0;
  printf("%s(...)", strtab[(int)infos.regs.rax]);
  ptrace(PTRACE_SINGLESTEP, pid, NULL, 0);
  wait4(pid, &status, WUNTRACED, NULL);
  if (ptrace(PTRACE_GETREGS, pid, NULL, &infos) == -1)
    {      printf("\n");      return 1;    }
  printf(" ret : %ld\n", infos.regs.rax);
  return 0;
}

static void	trace_process(int pid, char **strtab)
{
  int		status;

  while (1)
    {
      wait4(pid, &status, WUNTRACED, NULL);
      if (status == 0)
	break;
      if (get_syscall(pid, strtab))
	break ;
      ptrace(PTRACE_SINGLESTEP, pid, NULL, 0);
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
