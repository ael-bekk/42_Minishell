# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 20:55:35 by ael-bekk          #+#    #+#              #
#    Updated: 2022/05/30 21:09:29 by ael-bekk         ###   ########.fr        #
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

SRC = parsing/*  built_in/*.c exec/*

GFLAGS = gcc -Wextra -Wall -Werror -lreadline -L /Users/ael-bekk/.brew/opt/readline/lib -I /Users/ael-bekk/.brew/opt/readline/include

all : $(LIBFT) $(NAME) $(SRC)

$(NAME): $(LIBFT) $(SRC)
	@$(GFLAGS) $(LIBFT) $(SRC) -o $(NAME)
	@echo "\033[2K                                                             \033[A"
	@echo "$(GRN)[libft]: compiled$(RESET)"

$(LIBFT):
	@make -C $(GO_TO)

clean :
	@rm -rf $(NAME)

fclean : clean
	@make fclean -C $(GO_TO)
	@sleep 0.5
	@echo "$(RED)[$(L_RED)libft$(RESET)$(RED)] : removed.$(RESET)"


re: fclean all

.PHONY: all fclean clean re
