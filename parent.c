
#include <string.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <signal.h>
#include <stdio.h>
#include "strace.h"

/* _NAME	_RTYPE		_PARAMS */
struct syscalls	g_syscalls[] =
  {
    { "read",	"ssize_t",	{ "int",
				  "void*",
				  "size_t",
				  NULL }},
    { "write",	"ssize_t",	{ "int",
				  "const void*",
				  "size_t",
				  NULL }},
    { "open",	"int",		{ "const char*",
				  "int",
				  NULL }},
    { "close",	"int",		{ "int",
				  NULL }},
    { "stat",	"int",		{ "const char*",
				  "struct stat*",
				  NULL }},
    { "fstat",	"int",		{"int",
				 "struct stat*",
				 NULL }},
    { "lstat",	"int",		{"const char*",
				 "struct stat*",
				 NULL }},
    { "poll",	"int",		{ "struct pollfd*",
				  "nfds_t",
				  "int",
				  NULL }},
    { "lseek",	"off_t",	{ "int",
				  "off_t",
				  "int",
				  NULL }},
    { "mmap",	"void*",	{ "void*",
				  "size_t",
				  "int",
				  "int",
				  "int",
				  "off_t",
				  NULL }},
    { "munmap",	"int",		{ "void*",
				  "size_t",
				  NULL }},
    { "brk",	"int",		{ "void*",
				  NULL }},
    { "rt_sigaction",	"int",	{ "int",
				  "const struct sigaction*",
				  "struct sigaction*",
				  NULL }},
    { "rt_sigprocmask",	"int",	{ "int",
				  "const sigset_t*",
				  "sigset_t*",
				  NULL }},
    { "rt_sigreturn",	"int",	{ "unsigned long",
				  NULL }},
    { "ioctl",	"int",		{ "int",
				  "int",
				  "...",
				  NULL }},
    { "pread64",	"ssize_t",	{ "int",
					  "void*",
					  "size_t",
					  "off_t",
					  NULL }},
    { "pwrite64",	"ssize_t",	{ "int",
					  "const void*",
					  "size_t",
					  "off_t",
					  NULL }},
    { "readv",	"ssize_t",	{ "int",
				  "const struct iovec*",
				  "int",
				  NULL }},
    { "writev",	"ssize_t",	{ "int",
				  "const struct iovec*",
				  "int",
				  NULL }},
    { "access",	"int",		{ "const char*",
				  "int",
				  NULL }},
    { "pipe",	"int",		{ "int[2]",
				  NULL }},
    { "select",	"int",		{ "int",
				  "fd_set*",
				  "fd_set*",
				  "fd_set*",
				  "struct timeval*",
				  NULL }},
    { "sched_yield",	"int",	{ "void",
				  NULL }},
    { "mremap",	"void*",	{ "void*",
				  "size_t",
				  "size_t",
				  "int",
				  "...",
				  NULL }},
    { "msync", "int",		{ "void*",
				  "size_t",
				  "int",
				  NULL}},
    { "mincore",	"int",	{ "void*",
				  "size_t",
				  "unsigned char*",
				  NULL }},
    { "madvise",	"int",	{ "void*",
				  "size_t",
				  "int",
				  NULL }},
    { "shmget",	"int",		{ "key_t",
				  "size_t",
				  "int",
				  NULL }},
    { "shmat",	"void*",	{ "int",
				  "const void*",
				  "int",
				  NULL }},
    { "shmctl",	"int",		{ "int",
				  "int",
				  "struct shmid_ds*",
				  NULL }},
    { "dup",	"int",		{ "int",
				  NULL }},
    { "dup2",	"int",		{ "int",
				  "int",
				  NULL }},
    { "pause",	"int",		{ "void",
				  NULL }},
    { "nanosleep",	"int",	{ "const struct timespec*",
				  "struct timespec*",
				  NULL }},
    { "getitimer",	"int",	{ "int",
				  "struct itimerval*",
				  NULL }},
    { "alarm",	"unsigned int",	{ "unsigned int",
				  NULL }},
    { "setitimer",	"int",	{ "int",
				  "const struct itimerval*",
				  "struct itimerval*",
				  NULL }},
    { "getpid",	"pid_t",	{ "void",
				  NULL }},
    { "sendfile",	"ssize_t",	{ "int",
					  "int",
					  "off_t*",
					  "size_t",
					  NULL }},
    { "socket",	"int",		{ "int",
				  "int",
				  "int",
				  NULL }},
    { "connect", "int",		{ "int",
				  "const struct sockaddr*",
				  "socklen_t",
				  NULL }},
    { "accept",	"int",		{ "int",
				  "struct sockaddr*",
				  "socklen_t*",
				  NULL }},
    { "sendto", "ssize_t",	{ "int",
				  "const void*",
				  "size_t",
				  "int",
				  NULL }},
    { "recvfrom",	"ssize_t",	{ "int",
					  "void*",
					  "size_t",
					  "int",
					  "struct sockaddr*",
					  "socklen_t*",
					  NULL }},
    { "sendmsg",	"ssize_t",	{ "int",
					  "const struct msghdr*",
					  "int",
					  NULL }},
    { NULL,	NULL,		{ NULL }}
  };

static int	get_stopsig(int pid, char **strtab)
{
  siginfo_t	sig;

  (void)strtab;
  sig.si_signo = 0;
  if (-1 == ptrace(PTRACE_GETSIGINFO, pid, NULL, &sig))
    return printf("getsiginfo fail\n");
  if (sig.si_signo == 0 || sig.si_signo == 18 /* SIGCONT 18 19 25 ... */
      || sig.si_signo == 19 || sig.si_signo == 25
      || sig.si_signo == SIGTRAP)
    return 0;
  printf("Killed by signal %d : %s\n", sig.si_signo, strerror(sig.si_errno));
  return 1;
}

static int	get_syscall(int pid, char **strtab)
{
  struct user	infos;
  long		word;
  int		status;

  /* Return call informations */
  if (ptrace(PTRACE_GETREGS, pid, NULL, &infos) == -1)
    {      printf("getregs fail\n");      return 1;    }
  word = ptrace(PTRACE_PEEKTEXT, pid, infos.regs.rip, NULL);
  if ((word & 0xFFFF) != 0x050F)
    return 0;
  printf("%s(...)", strtab[(int)infos.regs.rax]);

  /* Go to return value */
  ptrace(PTRACE_SINGLESTEP, pid, NULL, 0);
  wait4(pid, &status, WUNTRACED, NULL);
  if (ptrace(PTRACE_GETREGS, pid, NULL, &infos) == -1)
    {      printf("\n");      return 1;    }
  printf(" ret : %ld\n", infos.regs.rax);

  if (infos.regs.rdi)
    printf(">>>>>>> %s\n", infos.regs.rdi);
  return 0;
}

static void	trace_process(int pid, char **strtab)
{
  int		status;

  while (1)
    {
      wait4(pid, &status, WUNTRACED, NULL);
      if (get_stopsig(pid, strtab))
      	break;
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
