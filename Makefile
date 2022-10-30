NAME		= cub3D
OBJ			= main parsing/map_parsing parsing/checkers
OBJS		= $(addsuffix .o, ${OBJ})
CC			= gcc
RM			= rm -f
HEADER		= -I headers/
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
LIBFT		= libft/libft.a

all:		${NAME}

obj/%.o:		%.c
				$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

clean:
				@${RM} ${OBJS} \
				$(info ************  cub3D Clean)

cleanft:
				@${MAKE} clean -C libft --no-print-directory

fclean:		clean
				@${MAKE} fclean -C libft --no-print-directory
				@${RM} ${NAME}
				$(info ************  cub3D Removed)

re:			fclean all

${NAME}:	${OBJS}
				@${MAKE} bonus -C libft --no-print-directory
				@${CC} $(OBJS) $(LIBFT) $(CFLAGS) -o $@
				$(info ************  cub3D Ready!)

.PHONY: all clean fclean re cleanft
