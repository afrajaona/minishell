#ifndef	EXEC_H
#define EXEC_H

#include <stdio.h>
#include "libft.h"
#include "../fact/parse.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define TOKEN_COMMAND			1
#define TOKEN_ARGUMENT			2
#define TOKEN_PIPE				3
#define TOKEN_HEREDOC			4
#define TOKEN_APPEND			5
#define TOKEN_INPUT_REDIR		6
#define TOKEN_OUTPUT_REDIR		7
#define TOKEN_FILE				8
#define TOKEN_LIMITER			9
#define TOKEN_GENERAL			10
#define TOKEN_VARIABLE			11

#define SINGLE_QUOTE			'\''
#define DOUBLE_QUOTE			'\"'

void	error_msg(char *target, char *message, int path_on);
void	ft_redir(t_redir *redir);
void	free_tab(char **s);
void	init(t_cmd	*cmd, char *value);

#endif
