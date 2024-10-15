NAME = libft.a
CC = cc
AR = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

INCS = libft.h

SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_call_func.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isempty.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_print_arg.c \
		ft_print_char.c \
		ft_printf.c \
		ft_print_int.c \
		ft_print_lhex.c \
		ft_print_percent.c \
		ft_print_ptr.c \
		ft_print_str.c \
		ft_print_uhex.c \
		ft_print_uint.c \
		ft_print_utils.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_select_func.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c

SRCS_DIR = ./
INCS_DIR = ./

SRC = $(addprefix $(SRCS_DIR), $(SRCS))
INC = $(addprefix $(INCS_DIR), $(INCS))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(AR) $(NAME) $(OBJ)

%.o: %.c $(INC)
	$(CC) -c -I $(INCS_DIR) -o $@ $< $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean