NAME =				ft_ssl

SRC_FILES =			ssl/ssl.c \
					ssl/commands.c \
					base64/base64.c \
					base64/base64_padding.c \
					base64/base64_parsing.c \
					base64/base64_utils.c \
					des/des.c \
					des/des_core.c \
					des/des_keys.c \
					des/des_parsing.c \
					des/des_read.c \
					des/des_hex_utils.c \
					des/des_utils.c \
					md5/md5.c \
					md5/md5_core.c \
					md5/md5_read.c \
					md5/md5_print.c \
					md5/md5_utils.c \
					sha256/sha256.c \
					sha256/sha256_core.c \
					sha256/sha256_read.c \
					sha256/sha256_print.c \
					sha256/sha256_utils.c \
					sha512/sha512.c \
					sha512/sha512_core.c \
					sha512/sha512_read.c \
					sha512/sha512_print.c \
					sha512/sha512_utils.c


OBJ_FILES =			$(patsubst %.c,%.o,$(SRC_FILES))

SRC_DIR =			src/
OBJ_DIR =			obj/
INCLUDE_DIRS =		include libft/includes

SRC =				$(addprefix $(SRC_DIR), $(OBJ_FILES))
OBJ =				$(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT_DIR =			libft/
LIBFT =				$(LIBFT_DIR)libft.a
LIBS =				-Llibft -lft

CC =				gcc
C_FLAGS =			-Wall -Wextra -Werror
INCLUDE_FLAGS =		$(addprefix -I , $(INCLUDE_DIRS))

RED =				\033[31m
GREEN =				\033[32m
BLUE =				\033[34m
YELLOW =			\033[33m
MAGENTA =			\033[35m
GREY =				\033[37m
GREEN_LIGHT =		\033[92m
YELLOW_LIGHT =		\033[93m
YELLOW_BOLD =		\033[1;33m
YELLOW_LIGHT_BOLD =	\033[1;93m
MAGENTA_LIGHT =		\033[95m
BLINK =				\033[5m
GREEN_LIGHT_BLINK =	\033[5;92m
END_COLOUR =		\033[0m

# .SILENT:
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(YELLOW_LIGHT)$(NAME): $(YELLOW)Compiling $(NAME)...$(END_COLOUR)"
	$(CC) $(C_FLAGS) $(LIBS) $^ -o $@
	@echo "$(YELLOW_LIGHT)$(NAME): $(GREEN)Successfully compiled $(NAME)!$(END_COLOUR)"

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(LIBFT): force
	make -C $(LIBFT_DIR)

force:
	@true

clean:
	@echo "$(YELLOW_LIGHT)$(NAME): $(YELLOW)Cleaning objects...$(END_COLOUR)"
	@/bin/rm -rf $(OBJ_DIR)
	@make clean -C libft
	@echo "$(YELLOW_LIGHT)$(NAME): $(GREEN)Successfully cleaned all objects!$(END_COLOUR)"

fclean: clean
	@echo "$(YELLOW_LIGHT)$(NAME): $(YELLOW)Cleaning executable...$(END_COLOUR)"
	@/bin/rm -f $(NAME)
	@make fclean -C libft
	@echo "$(YELLOW_LIGHT)$(NAME): $(GREEN)Successfully cleaned everything!$(END_COLOUR)"

re: fclean all

.PHONY: all force clean fclean re