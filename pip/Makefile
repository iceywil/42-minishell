# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wscherre <wscherre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 18:40:46 by wscherre          #+#    #+#              #
#    Updated: 2024/04/24 15:35:59 by wscherre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    =   srcs/pipex.c \
			srcs/pipex_utils.c \
			srcs/free_all.c \
			srcs/open_files.c \
			srcs/parsing.c \
			srcs/pipes.c \

BSRCS	=	bonus/pipex_bonus.c \
			bonus/pipex_utils_bonus.c \
			bonus/free_all_bonus.c \
			bonus/here_doc_bonus.c \
			bonus/open_files_bonus.c \
			bonus/parsing_bonus.c \
			bonus/pipes_bonus.c \

OBJS    =   $(SRCS:.c=.o)
BOBJS	=	$(BSRCS:.c=.o)

DEPS 	= 	$(SRCS:.c=.d)
BDEPS	=	$(BSRCS:.c=.d)

CC  	=   cc

RM 		=  	rm -f

CFLAGS  =   -Wall -Wextra -Werror -I. -MMD

NAME    =   pipex
BONUS	=	pipex_bonus

LIBFT 	= 	libft/libft.a

all: $(NAME)

bonus: $(BONUS)

-include ${DEPS} ${BDEPS}

${LIBFT}:
	make -C libft

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} $(OBJS) $(LIBFT) $(MLX_EX) -o $(NAME) -lm 

${BONUS}: ${LIBFT} ${BOBJS}
	${CC} ${CFLAGS} $(BOBJS) $(LIBFT) $(MLX_EX) -o $(BONUS) -lm 

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS) $(BOBJS)
	$(RM) $(DEPS) $(BDEPS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re