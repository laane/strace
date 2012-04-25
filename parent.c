
#include <string.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <signal.h>
#include <stdio.h>
#include "strace.h"

static int	get_stopsig(int pid, char **strtab)
{
  siginfo_t	sig;

  (void)strtab;
  sig.si_signo = 0;
  if (-1 == ptrace(PTRACE_GETSIGINFO, pid, NULL, &sig))
    return printf("getsiginfo fail\n");
  if (sig.si_signo == 0 || sig.si_signo == 5)
    return 0;
  printf("Stopped by signal %d : %s\n", sig.si_signo, strerror(sig.si_errno));
  return 1;
}

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
      if (get_stopsig(pid, strtab))
	break;
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
