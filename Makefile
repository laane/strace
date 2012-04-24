
NAME=		strace

SRC=		main.c \
		error.c \
		child.c \
		parent.c

OBJ=		$(SRC:.c=.o)

CFLAGS+=	-W -Wall -ansi -pedantic $(DEFINES)

DEFINES=	-D _BSD_SOURCE -D _XOPEN_SOURCE

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all