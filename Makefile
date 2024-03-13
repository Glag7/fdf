NAME = fdf

COMP = clang
CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
      utils.c \
      parse_file.c \
      parsing_errors.c \
      display.c \
      place_points.c

SRC_BONUS = main_bonus.c \
	    utils_bonus.c \
	    parse_file_bonus.c \
	    parsing_errors_bonus.c \
	    display_bonus.c \
	    place_points_bonus.c \
	    loop_bonus.c \
	    mouse_bonus.c \
	    colors_bonus.c \
	    windows_bonus.c \
	    init_data_bonus.c \
	    rotate_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : libft/libft.a MacroLibX/libmlx.so $(NAME)

bonus : libft/libft.a MacroLibX/libmlx.so $(OBJ_BONUS)
	@$(COMP) $(CFLAGS) $^ libft/libft.a MacroLibX/libmlx.so -o $(NAME) -lSDL2 -lm

MacroLibX/libmlx.so :
	@make -C MacroLibX -j16

libft/libft.a :
	@make -C libft/ file print

$(NAME) : $(OBJ)
	@$(COMP) $(CFLAGS) $^ libft/libft.a MacroLibX/libmlx.so -o $@ -lSDL2 -lm

%.o : %.c
	@$(COMP) $(CFLAGS) -c $^ -o $@

cleanfdf :
	@rm -f $(OBJ) $(OBJ_BONUS)

clean :
	@rm -f $(OBJ) $(OBJ_BONUS)
	@make -C libft clean
	@make -C MacroLibX clean

fclean : clean
	@rm -f $(NAME)
	@rm -f MacroLibX/libmlx.so
	@rm -f libft/libft.a

chokbar :
	@make -C libft/ chokbar

re : fclean all

refdf : cleanfdf all

.PHONY: all fclean clean cleanfdf re refdf bonus chokbar
