#ifndef STRACE_H_
# define STRACE_H_

/*
** Defines
*/
#ifndef NULL
# define NULL	(void*)0
#endif


/*
** Prototypes
*/
void		exit_error(const char*);

void		exec_child(char*);
void		exec_parent(int, char **);

#endif /* !STRACE_H_ */
