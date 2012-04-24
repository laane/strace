
#include <sys/wait.h>
#include "strace.h"

void		exec_parent(int pid)
{
  int		status;

  wait4(pid, &status, 0, NULL);
}
