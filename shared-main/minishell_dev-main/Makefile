NAME = minishell
CC = cc
RM = rm
CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I$(INC_DIR) -I$(LIBFT)
LFLAGS = -L$(LIBFT) -lft -lreadline

OBJ_DIR = ./bin/
INC_DIR = ./include/
SRC_DIR = ./src/

LIBFT = ./libft/

INCS =	lexer.h \
		token.h \
		exec.h \
		expand.h \
		parse.h \
		utils.h \
		builtin.h \
		minishell.h \
		debug.h

SRCS =	minishell.c \
		builtin/ft_exec_builtin.c \
		builtin/ft_builtin_utils.c \
		exec/ft_create_pipes.c \
		exec/ft_exec_cmd.c \
		exec/ft_exec_line.c \
		exec/ft_exec_utils.c \
		exec/ft_find_exec.c \
		exec/ft_find_exec_utils.c \
		exec/ft_get_exec_value.c \
		exec/ft_wait_cmds.c \
		expand/ft_expand.c \
		expand/ft_expand_quotes.c \
		expand/ft_expand_split.c \
		expand/ft_expand_token.c \
		expand/ft_expand_utils.c \
		expand/ft_expand_variable.c \
		expand/ft_expand_variable_utils.c \
		expand/ft_get_expand_arg.c \
		expand/ft_get_expand.c \
		expand/ft_get_expand_cmd.c \
		expand/ft_get_expand_file.c \
		expand/ft_get_expand_limiter.c \
		expand/ft_join_expand.c \
		expand/ft_split_var.c \
		expand/ft_trim_quotes.c \
		lexer/ft_lexer.c \
		lexer/ft_lexer_utils.c \
		parse/ft_add_cmd_node.c \
		parse/ft_add_node_utils.c \
		parse/ft_add_pipe_node.c \
		parse/ft_add_redir_value.c \
		parse/ft_add_redir_value_utils.c \
		parse/ft_check_parse.c \
		parse/ft_get_arg_utils.c \
		parse/ft_get_arg_value.c \
		parse/ft_get_cmd_value.c \
		parse/ft_get_parse.c \
		parse/ft_get_redir_value.c \
		parse/ft_get_redir_value_utils.c \
		parse/ft_parse.c \
		parse/ft_parse_utils.c \
		signal/ft_signal.c \
		token/ft_token.c \
		token/ft_token_flag.c \
		token/ft_token_utils.c \
		utils/ft_data.c \
		utils/ft_list_utils.c \
		utils/ft_redir_to_tty.c \
		utils/ft_tab_dup.c \
		utils/ft_to_str_utils.c \
		utils/ft_to_tab.c \
		debug/ft_print_expand.c \
		debug/ft_print_parse.c \
		debug/ft_print_utils.c \
		debug/ft_print_list.c \
		debug/ft_print_token.c \
		debug/ft_readline.c

OBJS = $(SRCS:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRCS))
INC = $(addprefix $(INC_DIR), $(INCS))
OBJ = $(addprefix $(OBJ_DIR), $(OBJS))

$(NAME): $(OBJ_DIR) $(OBJ) $(INC)
	$(MAKE) -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

$(OBJ_DIR)%o: $(SRC_DIR)%c $(INC)
	$(CC) -c $(IFLAGS) -o $@ $< $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)lexer/ $(OBJ_DIR)token/ $(OBJ_DIR)expand/ \
	$(OBJ_DIR)parse/ $(OBJ_DIR)exec/ $(OBJ_DIR)utils/ $(OBJ_DIR)builtin/ \
	$(OBJ_DIR)signal/ \
	$(OBJ_DIR)debug/

all: $(NAME)

clean:
	$(MAKE) -C $(LIBFT) clean
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	$(RM) -f $(NAME)

re: clean all

.PHONY: all clean fclean re
