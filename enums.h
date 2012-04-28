
#include <unistd.h>
#include <fcntl.h>
#include "strace.h"

typedef struct	s_flags
{
  int		val;
  char		*str;
}		t_flags;

t_flags		access_flags[] =
  {
    {R_OK, "R_OK"},
    {W_OK, "W_OK"},
    {X_OK, "X_OK"},
    {0, NULL}
  };

t_flags		open_flags[] =
  {
    {O_APPEND, "O_APPEND"},
    {O_ASYNC, "O_ASYNC"},
    {O_CLOEXEC, "O_CLOEXEC"},
    {O_CREAT, "O_CREAT"},
    {O_DIRECT, "O_DIRECT"},
    {O_DIRECTORY, "O_DIRECTORY"},
    {O_EXCL, "O_EXCL"},
    {O_LARGEFILE, "O_LARGEFILE"},
    {O_NOATIME, "O_NOATIME"},
    {O_NOCTTY, "O_NOCTTY"},
    {O_NOFOLLOW, "O_NOFOLLOW"},
    {O_NONBLOCK, "O_NONBLOCK"},
    {O_SYNC, "O_SYNC"},
    {O_TRUNC, "O_TRUNC"},
    {0, NULL}
  };
