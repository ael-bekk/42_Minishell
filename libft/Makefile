NAME	= libft.a

SRCS	= 	utils.c ft_strlen_double.c ft_str_double_join.c ft_free.c\
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_tolower.c ft_toupper.c  ft_atoi.c ft_itoa.c ft_calloc.c \
			ft_memset.c ft_bzero.c ft_memcpy.c ft_memcpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_substr.c \
			ft_strdup.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
			ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
			get_next_line.c get_next_line_utils.c ft_strcmp.c
OBJS	= $(SRCS:.c=.o)

ICLS	= libft.h

GCC	= gcc

FLGS	= -Wall -Wextra -Werror

LIB1	= ar -rcs


RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		$(LIB1) $(NAME) $(OBJS)

.c.o:
		$(GCC)   -c $<

clean:
		$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re

