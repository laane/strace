
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include "strace.h"

static void	trace_process(int pid)
{

}

void		exec_parent(int pid)
{
  int		status;

  ptrace(PTRACE_ATTACH, pid, NULL, 0);
  wait4(pid, &status, WUNTRACED, NULL);
  trace_process(pid);
}
