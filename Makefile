NAME = 			cub3d
COMP =			gcc
FLAGS_COMP =	-Wall -Wextra -Werror
FLAGS_LEAKS =	-g3 -fsanitize=address


# COLOR CONFIG
GREEN =			\033[92m
NOCOLOR =		\033[m

# DIRECTORY NAMES
DIR_SRC =		srcs
DIR_INC =		includes
DIR_OBJ =		obj
DIR_LIB_FT =	./libs/libft
DIR_LIB_MLX =	./libs/MLX42

# SOURCE NAMES
NAMES_SRCS =	main.c \
				checkers.c \
				map_parsing.c \
				utils.c \
				error.c

# HEADER NAMES
NAMES_HDRS =	parsing.h

# OBJECT NAMES
NAMES_OBJS =	$(NAMES_SRCS:.c=.o)

FULL_OBJS =		$(addprefix $(DIR_OBJ)/,$(NAMES_OBJS))
FULL_HDRS =		$(addprefix $(DIR_INC)/,$(NAMES_HDRS))

NAME_LIB_FT =	libft.a
NAME_LIB_MLX =	libmlx42.a

LINKER		=  -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" 


INC_LIB_FT =	$(DIR_LIB_FT) $(DIR_LIB_FT)/$(NAME_LIB_FT)
INC_LIB_MLX =	$(DIR_LIB_MLX)/$(NAME_LIB_MLX)
INC_HDRS =		-I $(DIR_INC)
INC_LIBS =		-L $(INC_LIB_FT) $(INC_LIB_MLX) 

all: lib_ft $(NAME)

$(NAME): lib_ft lib_mlx $(FULL_OBJS)
	@$(COMP) -g $(INC_HDRS) $(FULL_OBJS) $(INC_LIBS) $(LINKER) -o $(NAME)
	@echo "$(GREEN)[cub3d] - Compiled cub3d!$(NOCOLOR)"

lib_ft:
	@make -sC $(DIR_LIB_FT)

lib_mlx:
	@make -sC $(DIR_LIB_MLX)

leaks: $(FULL_OBJS) lib_ft lib_mlx
	@echo "$(GREEN)[cub3d] - Compiled with $(FLAGS_LEAKS).$(NOCOLOR)"
	@$(COMP) $(FLAGS_LEAKS) $(INC_HDRS) $(FULL_OBJS) $(INC_LIBS) -o $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(FULL_HDRS)
	@mkdir -p $(DIR_OBJ) 
	@$(COMP) -g $(FLAGS_COMP) $(INC_HDRS) -o $@ -c $<

clean:
	@rm -rf $(DIR_OBJ)
	@make clean -C $(DIR_LIB_FT)
	@make clean -C $(DIR_LIB_MLX)
	@echo "$(GREEN)[cub3d] - Running clean.$(NOCOLOR)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(DIR_LIB_FT)
	@make fclean -C $(DIR_LIB_MLX)
	@echo "$(GREEN)[cub3d] - Running fclean.$(NOCOLOR)"

re : fclean all

.PHONY: all clean fclean re leaks lib_ft

make_obj_dirs:
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(DIR_OBJ)/parsing
	@mkdir -p $(DIR_OBJ)/tools
