# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 20:55:35 by ael-bekk          #+#    #+#              #
#    Updated: 2022/07/16 23:42:15 by amounadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #




RED = \033[31m
L_RED = \033[1;31m
GRN = \033[0;32m
L_GRN = \033[1;32m
RESET = \033[0m
Purple= \033[0;35m

LIBFT = libft/libft.a

NAME = minishell

GO_TO = libft

SRC = $(wildcard parsing/*.c) $(wildcard built_in/*.c) $(wildcard exec/*.c)

GFLAGS = gcc -Wextra -Wall -Werror -lreadline -L /Users/ael-bekk/.brew/opt/readline/lib -I /Users/ael-bekk/.brew/opt/readline/include

GFLAGS1 =  -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include


all : $(LIBFT) $(NAME) $(SRC)

linux : $(LIBFT) $(SRC)
	@ gcc $(SRC) $(GFLAGS1) $(LIBFT) -o $(NAME)
	@echo "\033[2K                                                             \033[A"
	@echo "$(GRN)[MINISHELL]: compiled$(RESET)"

$(NAME): $(LIBFT) $(SRC)
	@$(GFLAGS) $(LIBFT) $(SRC) -o $(NAME)
	@echo "\033[2K                                                             \033[A"
	@echo "$(GRN)[MINISHELL]: compiled$(RESET)"

$(LIBFT):
	@make -C $(GO_TO)

clean :
	@rm -rf $(NAME)

fclean : clean
	@make fclean -C $(GO_TO)
	@sleep 0.5
	@echo "$(RED)[$(L_RED)MINISHELL$(RESET)$(RED)] : removed.$(RESET)"


re: fclean all

.PHONY: all fclean clean re
