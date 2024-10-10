NAME        := Cub3D
CFLAGS      := -Wextra -Wall -Werror
CFLAGS      :=
LIBMLX      := ./libs/MLX42
LIBMLX_REPO := https://github.com/codam-coding-college/MLX42.git

HEADERS     := -I ./include -I $(LIBMLX)/include
HEADERS_BONUS := -I ./include -I $(LIBMLX)/include
LIB_MLX        := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIB_FT      := libs/libft/libft.a
SRCS        := $(shell find ./srcs -iname "*.c")
SRCS_BONUS  := $(shell find ./srcs_bonus -iname "*.c")
OBJS_PATH   := ./objs
OBJS_PATH_BONUS := ./objs_bonus
OBJS        := $(patsubst %.c,$(OBJS_PATH)/%.o,$(notdir $(SRCS)))
OBJS_BONUS  := $(patsubst %.c,$(OBJS_PATH_BONUS)/%.o,$(notdir $(SRCS_BONUS)))

all: LIBFT libmlx $(OBJS_PATH) $(OBJS) $(NAME)

LIBFT:
	@$(MAKE) -C libs/libft

$(LIBMLX):
	@git clone $(LIBMLX_REPO) $(LIBMLX)

libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJS_PATH)/%.o: ./srcs/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIB_MLX) $(LIB_FT) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS_PATH)
	@rm -rf $(OBJS_PATH_BONUS)
	@rm -rf $(LIBMLX)
	@$(MAKE) -C libs/libft clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME)_bonus
	@$(MAKE) -C libs/libft fclean

re: clean all

bonus: LIBFT libmlx $(OBJS_PATH_BONUS) $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIB_MLX) $(LIB_FT) $(HEADERS_BONUS) -o $(NAME)_bonus

$(OBJS_PATH_BONUS)/%.o: ./srcs_bonus/%.c | $(OBJS_PATH_BONUS)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS_BONUS) && printf "Compiling Bonus: $(notdir $<)\n"

$(OBJS_PATH_BONUS):
	@mkdir -p $(OBJS_PATH_BONUS)

.PHONY: all, clean, fclean, re, libmlx, bonus
