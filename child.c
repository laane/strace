
#include <unistd.h>
#include <sys/ptrace.h>
#include "strace.h"

void		exec_child(char* filename)
{
  char*		args[2];

  args[0] = filename;
  args[1] = NULL;
  ptrace(PTRACE_TRACEME, 0, NULL, NULL);
  execvp(filename, args);
}
