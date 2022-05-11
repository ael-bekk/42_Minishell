NAME	= minishell

LIB	= libshell.a

SRCS	= srs/main.c

OBJS	= $(SRCS:.c=.o)

ICLS	= libft.hs


CFLAGS	= -Wall -Wextra -Werror

CC		= cc

RM		= rm -f

all:		$(NAME)

$(NAME):	$(LIB)
	$(CC) $(CFLAGS) $(LIB) -o $(NAME)

$(LIB):	$(OBJS)
	ar -rcs $(LIB) $(OBJS)

clean:
	$(RM) $(OBJS) $(LIB)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re