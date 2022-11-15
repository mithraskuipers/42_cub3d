NAME		= cub3D
OBJ			= srcs/main srcs/debug/misc srcs/free/misc srcs/parsing/checkers srcs/parsing/parsing srcs/parsing/utils srcs/tools/error srcs/parsing/variables
OBJS		= $(addsuffix .o, ${OBJ})
CC			= gcc
RM			= rm -f
HEADER		= -I headers/ -I $(MLX)/include
CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address
LINKER		=  -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" 
LIBFT		= ./libs/libft/libft.a
MLX			= ./libs/MLX42
LIBMLX		= ./libs/MLX42/libmlx42.a

all:		 libmlx ${NAME}

${LIBMLX}:
				@$(MAKE) -C $(MLX)

${LIBFT}:
				@${MAKE} bonus -C ./libs/libft --no-print-directory

obj/%.o:		%.c
				$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

clean:
				@${RM} ${OBJS} 
				@$(MAKE) clean -C $(MLX)
				$(info ************  cub3D Clean)

cleanft:
				@${MAKE} clean -C ./libs/libft --no-print-directory
				@${MAKE} clean -C ./libs/MLX42 --no-print-directory

fclean:		clean
				@${MAKE} fclean -C ./libs/libft --no-print-directory
				@${MAKE} fclean -C ./libs/MLX42 --no-print-directory
				@${RM}  -f ${NAME}
				$(info ************  cub3D Removed)

re:			fclean all

run:		${NAME}
				./${NAME} examplemap.cub

${NAME}:	${OBJS} ${LIBMLX} ${LIBFT}
				@${CC} $^ $(CFLAGS) $(LINKER) -o $(NAME)
				$(info ************  cub3D Ready!)

.PHONY: all clean fclean re cleanft run libmlx libft
