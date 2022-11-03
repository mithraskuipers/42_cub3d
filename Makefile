NAME		= cub3D
OBJ			= main parsing/map_parsing parsing/checkers parsing/utils
OBJS		= $(addsuffix .o, ${OBJ})
CC			= gcc
RM			= rm -f
HEADER		= -I headers/ -I $(MLX)/include
CFLAGS		= -Wall -Wextra -Werror #-lglfw -ldl -lm"/Users/dkramer/.brew/opt/glfw/lib/"#-lglfw -ldl -lm -O3-ldl -lm -O3 #-fsanitize=address
LINKER		=  -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" 
LIBFT		= libft/libft.a
MLX			= MLX42
LIBMLX		= MLX42/libmlx42.a

all:		 libmlx ${NAME}

${LIBMLX}:
				@$(MAKE) -C $(MLX)

${LIBFT}:
				@${MAKE} bonus -C libft --no-print-directory

obj/%.o:		%.c
				$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

clean:
				@${RM} ${OBJS} 
				@$(MAKE) clean -C $(MLX)
				$(info ************  cub3D Clean)

cleanft:
				@${MAKE} clean -C libft --no-print-directory
				@${MAKE} clean -C MLX42 --no-print-directory

fclean:		clean
				@${MAKE} fclean -C libft --no-print-directory
				@${MAKE} fclean -C MLX42 --no-print-directory
				@${RM}  -f ${NAME}
				$(info ************  cub3D Removed)

re:			fclean all

run:		${NAME}
				./${NAME} examplemap.cub

${NAME}:	${OBJS} ${LIBMLX} ${LIBFT}
				@${CC} $^ $(CFLAGS) $(LINKER) -o $(NAME)
				$(info ************  cub3D Ready!)

.PHONY: all clean fclean re cleanft run libmlx libft
