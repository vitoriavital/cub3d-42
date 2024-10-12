CC = cc
CFLAGS = -Wall -Wextra -Werror

CFILES = ft_isascii.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c ft_strrchr.c \
		 ft_atoi.c ft_isdigit.c ft_memmove.c ft_split.c ft_strlcpy.c \
		 ft_strtrim.c ft_bzero.c ft_isprint.c ft_memset.c ft_strchr.c \
		 ft_strlen.c ft_substr.c ft_calloc.c ft_itoa.c ft_putchar_fd.c \
		 ft_strdup.c ft_strmapi.c ft_tolower.c ft_isalnum.c ft_memchr.c \
		 ft_putendl_fd.c ft_striteri.c ft_strncmp.c ft_toupper.c ft_isalpha.c \
		 ft_memcmp.c ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c get_next_line.c \
		 get_next_line_utils.c \

CFILES_B = ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c \
		  ft_lstadd_front_bonus.c  ft_lstdelone_bonus.c  ft_lstlast_bonus.c  ft_lstnew_bonus.c

OFILES = $(CFILES:.c=.o)
OFILES_B = $(CFILES_B:.c=.o)
HFILE = libft.h
NAME = libft.a

$(NAME): $(OFILES)
	ar rcs $@ $^

all: $(NAME)

%.o: %.c $(HFILE)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES) $(OFILES_B)

fclean:clean
	rm -f $(NAME)

re: fclean all

bonus: $(OFILES_B)
	ar rcs $(NAME) $^

.PHONY: all clean fclean re bonus
