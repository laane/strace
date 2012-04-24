#ifndef STRACE_H_
# define STRACE_H_

/*
** Prototypes
*/
void		exit_error(const char*);

void		exec_child(const char*);
void		exec_parent(int);

#endif /* !STRACE_H_ */
