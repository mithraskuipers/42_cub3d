NAME		= 	cub3D
OBJ			=	srcs/main \
				srcs/drawBackground \
				srcs/init/initGame \
				srcs/init/initDDA \
				srcs/hooksKeyboard \
				srcs/frameCallback \
				srcs/walking \
				srcs/rotating \
				srcs/debug/debug \
				srcs/parsing/parsing \
				srcs/parsing/parsingColors \
				srcs/raycaster/raycast \
				srcs/raycaster/raycastComp \
				srcs/raycaster/raycastWalls \
				srcs/utils

OBJS		= $(addsuffix .o, ${OBJ})
CC			= gcc
RM			= rm -f
HEADER		= -I headers/ -I $(MLX)/include
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
LINKER		=  -lglfw -lm -L "/Users/$(USER)/.brew/opt/glfw/lib/" 

LIBFT		= ./libs/libft/libft.a
MLX			= ./libs/MLX42
LIBMLX		= ./libs/MLX42/libmlx42.a

all:		 libmlx ${NAME}

${LIBMLX}:
				@$(MAKE) -C $(MLX)

${LIBFT}:
				@${MAKE} -C ./libs/libft --no-print-directory

obj/%.o:		%.c
				$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

clean:
				@${RM} ${OBJS} 
				@$(MAKE) clean -C $(MLX)
				$(info ************  $(NAME) Clean)

cleanft:
				#@${MAKE} clean -C ./libs/libft --no-print-directory
				#@${MAKE} clean -C ./libs/MLX42 --no-print-directory

fclean:		clean
				#@${MAKE} fclean -C ./libs/libft --no-print-directory
				#@${MAKE} fclean -C ./libs/MLX42 --no-print-directory
				@${RM}  -f ${NAME}
				$(info ************  $(NAME) Removed)

re:			fclean all

${NAME}:	${OBJS} ${LIBMLX} ${LIBFT}
				@${CC} $^ $(CFLAGS) $(LINKER) -o $(NAME)
				$(info ************  $(NAME) Ready!)

.PHONY: all clean fclean re cleanft libmlx libft