# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 20:46:06 by codespace         #+#    #+#              #
#    Updated: 2024/12/17 02:16:41 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   minishell

CC          =   cc

FLAG        =   -g3 -Wall -Wextra -Werror -lreadline

LDFLAGS     =   

LIBFT_PATH  =   libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

C_FILES     =   main.c \
				free/free.c \
				free/free_utils.c \
				parsing/parser.c \
				parsing/parser_utils.c \
				parsing/first_parsing.c \
				parsing/handle_dollar.c \
				parsing/second_parsing.c \
				exec/parsing.c \
				exec/handle_delims.c \
				exec/pipex_one.c \
				exec/pipex_two.c \
				exec/pipex_utils_one.c \
				exec/pipex_utils_two.c \
				exec/signals.c \
				builtins/echo.c \
				builtins/cd.c \
				builtins/pwd.c \
				builtins/export.c \
				builtins/unset.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/export_lol.c \
				env/env_setup.c \
	
all:        $(NAME)

OBJS    =   $(C_FILES:.c=.o)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

$(NAME):    $(LIBFT_LIB) $(OBJS)
	$(CC) $(OBJS) $(FLAG) $(LIBFT_LIB) -o $(NAME)

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJS)

fclean:     clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_PATH)

re:         fclean all

.PHONY:     all clean fclean re