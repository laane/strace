
#include "strace.h"

/* _NAME	_RTYPE		_PARAMS */
struct syscalls	g_syscalls[] =
  {
    { "read",	"ssize_t",	{ "int",
				  "void*",
				  "size_t",
				  NULL }},
    { "write",	"ssize_t",	{ "int",
				  "void*",
				  "size_t",
				  NULL }},
    { "open",	"int",		{ "char*",
				  "int",
				  NULL }},
    { "close",	"int",		{ "int",
				  NULL }},
    { "stat",	"int",		{ "char*",
				  "struct stat*",
				  NULL }},
    { "fstat",	"int",		{"int",
				 "struct stat*",
				 NULL }},
    { "lstat",	"int",		{"char*",
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
					  "void*",
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
    { "access",	"int",		{ "char*",
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
				  "void*",
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
				  "void*",
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
    { "recvmsg",	"ssize_t",	{ "int",
					  "struct msghdr*",
					  "int",
					  NULL }},
    { "shutdown",	"int",	{ "int",
				  "int",
				  NULL }},
    { "bind",		"int",	{ "int",
				  "const struct sockaddr*",
				  "socklen_t",
				  NULL }},
    { "listen",		"int",	{ "int",
				  "int",
				  NULL }},
    { "getsockname",	"int",	{ "int",
				  "struct sockaddr*",
				  "socklen_t*",
				  NULL }},
    { "getpeername",	"int",	{ "int",
				  "struct sockaddr*",
				  "socklen_t*",
				  NULL }},
    { "socketpair",	"int",	{ "int",
				  "int",
				  "int",
				  "int*",
				  NULL }},
    { "setsockopt",	"int",	{ "int",
				  "int",
				  "int",
				  "void*",
				  "socklen_t",
				  NULL }},
    { "getsockopt",	"int",	{ "int",
				  "int",
				  "int",
				  "void*",
				  "socklen_t*",
				  NULL }},
    { "clone",		"int",	{ "int (*)(void*)",
				  "void*",
				  "int",
				  "void*",
				  "...",
				  NULL }},
    { "fork",	"pid_t",	{ "void",
				  NULL }},
    { "vfork",	"pid_t",	{ "void",
				  NULL }},
    { "execve",		"int",	{ "char*",
				  "char**",
				  "char**",
				  NULL }},    
    { "exit",		"void",	{ "int",
				  NULL }},
    { "wait4",	"pid_t",	{ "pid_t",
				  "int*",
				  "int",
				  "struct rusage*",
				  NULL }},
    { "kill",		"int",	{ "pid_t",
				  "int",
				  NULL }},
    { "uname",		"int",	{ "struct utsname*",
				  NULL }},
    { "semget",		"int",	{ "key_t",
				  "int",
				  "int",
				  NULL }},
    { "semop",		"int",	{ "int",
				  "struct sembuf*",
				  "unsigned",
				  NULL }},
    { "semctl",		"int",	{ "int",
				  "int",
				  "int",
				  NULL }},
    { "shmdt",		"int",	{ "void*",
				  NULL }},
    { "msgget",		"int",	{ "key_t",
				  "int",
				  NULL }},
    { "msgsnd",		"int",	{ "int",
				  "void*",
				  "size_t",
				  "int",
				  NULL }},
    { "msgrcv",	"ssize_t",	{ "int",
				  "void*",
				  "size_t",
				  "long",
				  "int",
				  NULL }},
    { "msgctl",		"int",	{ "int",
				  "int",
				  "struct msqid_ds*",
				  NULL }},
    { "fcntl",		"int",	{ "int",
				  "int",
				  "...",
				  NULL }},
    { "flock",		"int",	{ "int",
				  "int",
				  NULL }},
    { "fsync",		"int",	{ "int",
				  NULL }},
    { "fdatasync",	"int",	{ "int",
				  NULL }},
    { "truncate",	"int",	{ "char*",
				  "off_t",
				  NULL }},
    { "ftruncate",	"int",	{ "int",
				  "off_t",
				  NULL }},
    { "getdents",	"int",	{ "unsigned int",
				  "struct linux_dirent*",
				  "unsigned int",
				  NULL }},
    { "getcwd",	"char*",	{ "char*",
				  "size_t",
				  NULL }},
    { "chdir",		"int",	{ "char*",
				  NULL }},
    { "fchdir",		"int",	{ "int",
				  NULL }},
    { "rename",		"int",	{ "char*",
				  "char*",
				  NULL }},
    { "mkdir",		"int",	{ "char*",
				  "mode_t",
				  NULL }},
    { "rmdir",		"int",	{ "char*",
				  NULL }},
    { "creat",		"int",	{ "char*",
				  "mode_t",
				  NULL }},
    { "link",		"int",	{ "char*",
				  "char*",
				  NULL }},
    { "unlink",		"int",	{ "char*",
				  NULL }},
    { "symlink",	"int",	{ "char*",
				  "char*",
				  NULL }},
    { "readlink", "ssize_t",	{ "char*",
				  "char*",
				  "size_t",
				  NULL }},
    { "chmod",		"int",	{ "char*",
				  "mode_t",
				  NULL }},
    { "fchmod",		"int",	{ "int",
				  "mode_t",
				  NULL }},
    { "chown",		"int",	{ "char*",
				  "uid_t",
				  "gid_t",
				  NULL }},
    { "fchown",		"int",	{ "int",
				  "uid_t",
				  "gid_t",
				  NULL }},
    { "lchown",		"int",	{ "char*",
				  "uid_t",
				  "gid_t",
				  NULL }},
    { "umask",	"mode_t",	{ "mode_t",
				  NULL }},
    { "gettimeofday",	"int",	{ "struct timeval*",
				  "struct timezone*",
				  NULL }},
    { "getrlimit",	"int",	{ "int",
				  "struct rlimit*",
				  NULL }},
    { "getrusage",	"int",	{ "int",
				  "struct rusage*",
				  NULL }},
    { "sysinfo",	"int",	{ "struct sysinfo*",
				  NULL }},
    { "times",	"clock_t",	{ "struct tms*",
				  NULL }},
    { "ptrace",	"long",		{ "enum __ptrace_request",
				  "pid_t",
				  "void*",
				  "void*",
				  NULL }},
    { "getuid",	"uid_t",	{ "void",
				  NULL }},
    { "syslog",	"int",		{ "int",
				  "char*",
				  "int",
				  NULL }},
    { "getgid",	"uid_t",	{ "void",
				  NULL }},
    { "setuid",	"int",		{ "uid_t",
				  NULL }},
    { "setgid",	"int",		{ "gid_t",
				  NULL }},
    { "geteuid",	"uid_t",	{ "void",
					  NULL }},
    { "getegid",	"gid_t",	{ "void",
					  NULL }},
    { "setpgid",	"int",	{ "pid_t",
				  NULL }},
    { "getppid",	"pid_t",	{ "void",
					  NULL }},
    { "getpgrp",	"pid_t",	{ "void",
					  NULL }},
    { "setsid",	"pid_t",	{ "void",
				  NULL }},
    { "setreuid",	"int",	{ "uid_t",
				  "uid_t",
				  NULL }},
    { "setregid",	"int",	{ "gid_t",
				  "gid_t",
				  NULL }},
    { "getgroups",	"int",	{ "int",
				  "gid_t[]",
				  NULL }},
    { "setgroups",	"int",	{ "size_t",
				  "const gid_t*",
				  NULL }},
    { "setresuid",	"int",	{ "uid_t",
				  "uid_t",
				  "uid_t",
				  NULL }},
    { "getresuid",	"int",	{ "uid_t*",
				  "uid_t*",
				  "uid_t*",
				  NULL }},
    { "setresgid",	"int",	{ "gid_t",
				  "gid_t",
				  "gid_t",
				  NULL }},
    { "getresgid",	"int",	{ "gid_t*",
				  "gid_t*",
				  "gid_t*",
				  NULL }},
    { "getpgid",	"pid_t",	{ "pid_t",
					  NULL }},
    { "setfsuid",	"int",	{ "uid_t",
				  NULL }},
    { "setfsgid",	"int",	{ "uid_t",
				  NULL }},
    { "getsid",	"pid_t",	{ "pid_t",
				  NULL }},
    { "capget",	"int",		{ "cap_user_header_t",
				  "cap_user_data_t",
				  NULL }},
    { "capset",	"int",		{ "cap_user_header_t",
				  "cap_user_data_t",
				  NULL }},
    { "rt_sigpending",	"int",	{ "sigset_t*",
				  NULL }},
    { "rt_sigtimedwait",	"int",	{ "const sigset_t*",
					  "siginfo_t*",
					  "const struct timespec*",
					  NULL }},
    { "rt_sigqueueinfo",	"int",	{ "pid_t",
					  "int",
					  "const union sigval",
					  NULL }},
    { "rt_sigsuspend",	"int",	{ "const sigset_t*",
				  NULL }},
    { "sigaltstack",	"int",	{ "const stack_t*",
				  "stack_t*",
				  NULL }},
    { "utime",	"int",		{ "char*",
				  "const struct utimbuf*",
				  NULL }},
    { "mknod",	"int",		{ "char*",
				  "mode_t",
				  "dev_t",
				  NULL }},
    { "uselib",	"int",		{ "char*",
				  NULL }},
    { "personality",	"int",	{ "unsigned long",
				  NULL }},
    { "ustat",	"int",		{ "dev_t",
				  "struct ustat*",
				  NULL }},
    { "statfs",	"int",		{ "char*",
				  "struct statfs*",
				  NULL }},
    { "fstatfs",	"int",	{ "int",
				  "struct statfs*",
				  NULL }},
    { "sysfs",	"int",		{ "int",
				  NULL }},
    { "getpriority",	"int",	{ "int",
				  "int",
				  NULL }},
    { "setpriority",	"int",	{ "int",
				  "int",
				  "int",
				  "int",
				  NULL }},
    { "sched_setparam",	"int",	{ "pid_t",
				  "const struct sched_param*",
				  NULL }},
    { "sched_getparam",	"int",	{ "pid_t",
				  "struct sched_param*",
				  NULL }},
    { "sched_setscheduler",	"int",	{ "pid_t",
					  "int",
					  "const struct sched_param*",
					  NULL }},
    { "sched_getscheduler",	"int",	{ "pid_t",
					  NULL }},
    { "sched_get_priority_max",	"int",	{ "int",
					  NULL }},
    { "sched_get_priority_min",	"int",	{ "int",
					  NULL }},
    { "sched_rr_get_interval",	"int",	{ "pid_t",
					  "struct timespec*",
					  NULL }},
    { "mlock",	"int",		{ "cont void*",
				  "size_t",
				  NULL }},
    { "munlock",	"int",	{ "void*",
				  "size_t",
				  NULL }},
    { "mlockall",	"int",	{ "int",
				  NULL }},
    { "munlockall",	"int",	{ "void",
				  NULL }},
    { "vhangup",	"int",	{ "void",
				  NULL }},
    { "modify_ldt",	"int",	{ "int",
				  "void*",
				  "unsigned long",
				  NULL }},
    { "pivot_root",	"int",	{ "char*",
				  "char*",
				  NULL}},
    { "_sysctl",	"int",	{ "struct __sysctl_args*",
				  NULL }},
    { "prctl",	"int",		{ "int",
				  "unsigned long",
				  "unsigned long",
				  "unsigned long",
				  "unsigned long",
				  NULL }},
    { "arch_prctl",	"int",	{ "int",
				  "unsigned long",
				  NULL }},
    { "adjtimex",	"int",	{ "struct timex*",
				  NULL }},
    { "setrlimit",	"int",	{ "int",
				  "const struct rlimit*",
				  NULL }},
    { "chroot",	"int",		{ "char*",
				  NULL }},
    { "sync",	"void",		{ "void",
				  NULL }},
    { "acct",	"int",		{ "char*",
				  NULL }},
    { "settimeofday",	"int",	{ "const struct timeval*",
				  "const struct simezone*",
				  NULL }},
    { "mount",	"int",		{ "char*",
				  "char*",
				  "char*",
				  "unsigned long",
				  "void*",
				  NULL }},
    { "umount2",	"int",	{ "char*",
				  "int",
				  NULL }},
    { "swapon",	"int",		{ "char*",
				  "int",
				  NULL }},
    { "swapoff",	"int",	{ "char*",
				  NULL }},
    { "reboot",	"int",		{ "int",
				  NULL }},
    { "sethostname",	"int",	{ "char*",
				  "size_t",
				  NULL }},
    { "setdomainname",	"int",	{ "char*",
				  "size_t",
				  NULL }},
    { "iopl",	"int",		{ "int",
				  NULL }},
    { "ioperm",	"int",		{ "unsigned long",
				  "unsigned long",
				  "int",
				  NULL }},
    { "create_module",	"caddr_t",	{ "char*",
					  "size_t",
					  NULL }},
    { "init_module",	"int",	{ "char*",
				  "struct module*",
				  NULL }},
    { "delete_module",	"int",	{ "char*",
				  NULL }},
    { "get_kernel_syms",	"int",	{ "struct kernel_sym*",
					  NULL }},
    { "query_module",	"int",	{ "char*",
				  "int",
				  "void*",
				  "size_t",
				  "size_t",
				  NULL }},
    { "quotactl",	"int",	{ "int",
				  "char*",
				  "int",
				  "caddr_t",
				  NULL }},
    { "nfsservctl",	"long",	{ "int",
				  "struct nfsctl_arg*",
				  "union nfsctl_res*",
				  NULL }},
    { "gettid",	"pid_t",	{ "void",
				  NULL }},
    { "readahead",	"ssize_t",	{ "int",
					  "off64_t",
					  "size_t",
					  NULL }},
    { "tkill",	"int",		{ "int",
				  "int",
				  NULL }},
    { "time",	"time_t",	{ "time_t*",
				  NULL }},
    { "futex",	"int",		{ "int*",
				  "int",
				  "const struct timespec*",
				  "int*",
				  "int",
				  NULL }},
    { "sched_setaffinity",	"int",	{ "pid_t",
					  "size_t",
					  "cpu_set_t*",
					  NULL }},
    { "sched_getaffinity",	"int",	{ "pid_t",
					  "size_t",
					  "cpu_set_t*",
					  NULL }},
    { "set_thread_area",	"int",	{ "struct user_desc*",
					  NULL }},
    { "io_setup",	"int",	{ "unsigned",
				  "aio_context_t*",
				  NULL }},
    { "io_destroy",	"int",	{ "aio_context_t",
				  NULL }},
    { "io_getevents",	"int",	{ "aio_context_t",
				  "long",
				  "long",
				  "struct io_event*",
				  "struct timespec*",
				  NULL }},
    { "io_submit",	"int",	{ "aio_context_t",
				  "long",
				  "struct iocb**",
				  NULL }},
    { "io_cancel",	"int",	{ "aio_context_t",
				  "struct iocb*",
				  "struct io_event*",
				  NULL }},
    { "get_thread_area",	"int",	{ "struct user_desc*",
					  NULL }},
    { "lookup_dcookie",	"int",	{ "u64",
				  "char*",
				  "size_t",
				  NULL }},
    { "epoll_create",	"int",	{ "int",
				  NULL }},
    { "remap_file_pages",	"int",	{ "void*",
					  "size_t",
					  "int",
					  "ssize_t",
					  "int",
					  NULL }},
    { "getdents64",	"int",	{ "unsigned int",
				  "struct linux_dirent*",
				  "unsigned int",
				  NULL }},
    { "set_tid_address",	"long",	{ "int*",
					  NULL }},
    { "restart_syscall",	"long",	{ "void",
					  NULL }},
    { "semtimedop",	"int",	{ "int",
				  "struct sembuf*",
				  "unsigned",
				  "struct timespec*",
				  NULL }},
    { "fadvise64",	"int",	{ "int",
				  "off_t",
				  "off_t",
				  "int",
				  NULL }},
    { "timer_create",	"int",	{ "clockid_t",
				  "struct sigevent*",
				  "timer_t*",
				  NULL }},
    { "timer_settime",	"int",	{ "timer_t",
				  "int",
				  "const struct itimerspec*",
				  "struct itimerspec*",
				  NULL }},
    { "timer_gettime",	"int",	{ "timer_t",
				  "struct itimerspec*",
				  NULL }},
    { "timer_getoverrun",	"int",	{ "timer_t",
					  NULL }},
    { "timer_delete",	"int",	{ "timer_t",
				  NULL }},
    { "clock_settime",	"int",	{ "clockid_t",
				  "const struct timespec*",
				  NULL }},
    { "clock_gettime", "int",	{ "clockid_t",
				  "struct timespec*",
				  NULL }},
    { "clock_getres",	"int",	{ "clockid_t",
				  "struct timespec*",
				  NULL }},
    { "clock_nanosleep",	"int",	{ "clockid_t",
					  "int",
					  "const struct timespec*",
					  "struct timespec*",
					  NULL }},
    { "exit_group",	"void",	{ "int",
				  NULL }},
    { "epoll_wait",	"int",	{ "int",
				  "struct epoll_event*",
				  "int",
				  "int",
				  NULL }},
    { "epoll_ctl",	"int",	{ "int",
				  "int",
				  "int",
				  "struct epoll_event*",
				  NULL }},
    { "tgkill",	"int",		{ "int",
				  "int",
				  "int",
				  NULL }},
    { "utimes",	"int",		{ "char*",
				  "const struct timeval[2]",
				  NULL }},
    { "mbind",	"int",		{ "void*",
				  "unsigned long",
				  "int",
				  "unsigned long*",
				  "unsigned long",
				  "unsigned",
				  NULL }},
    { "set_mempolicy",	"int",	{ "int",
				  "unsigned long*",
				  "unsigned long" }},
    { NULL,	NULL,		{ NULL }}
  };