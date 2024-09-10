# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 20:46:06 by codespace         #+#    #+#              #
#    Updated: 2024/09/10 14:44:52 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   minishell

CC          =   cc

LIBS        =   /inc

FLAG        =   -g3 -Wall -Wextra -Werror

LDFLAGS     =   -lreadline

LIBFT_PATH  =   libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

C_FILES     =   main.c \
				free.c \

DEPS        =   $(OBJS:.o=.d)

all:        $(NAME)

#$(C_FILES)/%.o: %.c | $(C_FILES)
#	$(CC) $(FLAG) -MP -c $< -o $@

OBJS    =   $(C_FILES:.c=.o)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

$(NAME):    $(LIBFT_LIB) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBFT_LIB) -o $(NAME)

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJ_DIR) $(DEPS)

fclean:     clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_PATH)

re:         fclean all

.PHONY:     all clean fclean re