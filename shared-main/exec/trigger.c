#include <stdio.h>

void	ft_wait(int pid[], int nb)
{
	int	status;
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (waitpid(pid[i], &status, 0) == -1)
			printf("wait failed\n");
	}
	exit(WEXITSTATUS(status));
}

int	count_cmd(t_parse *line)
{
	int	i;

	i = 0;
	while (line)
	{
		if (line->type == TOKEN_PIPE)
		{
			line = line->next;
			continue;
		}
		i++;
		line = line->next;
	}
	return (i);
}

int	**init_pipes(int nb)
{
	int	**root;
	int	i;

	root = malloc(sizeof(int *) * nb);
	i = -1;
	while (++i < nb)
		root[i] = malloc(sizeof(int) * 2);
	i = -1;
	while (++i < nb)
	{
		if (pipe(root[i]) == -1)
			perror("pipe");
	}
	return (root);
}

void	exec_line(t_parse *line, int **pipelines, int branch_nb, char **env)
{
	int	pid[branch_nb];
	int	nb;

	nb = -1;
	while (nb < branch_nb)
	{
		if (!line)
			break;
		if (line->type == TOKEN_PIPE)
		}
			line = line->next;
			continue;
		}
		nb++;
		if (line->prev)
			dup2(pipeline[nb - 1][0], 0);
		if (line->next)
			dup2(pipeline[nb][1], 1);
		pid[nb] = fork();
		if (pid[nb] == -1)
		{
			printf("fork failed\n");
			exit(EXIT_FAILURE);
		}
		if (!pid[nb])
			execute((t_cmd *)line->cmd, env)
		line = line->next;
	}
	ft_wait(pid, branch_nb);
}

void	launch(t_parse *line, char **env)
{
	int	pid;
	int	status;
	int	branch_nb;
	int	**pipelines;

	branch_nb = count_cmd(line);
	pipelines = init_pipes(branch_nb - 1);
	pid = fork();
	if (pid == -1)
	{
		printf("launch failed\n");
		return ;
	}
	if (!pid)
		exec_line(line, pipelines, branch_nb, env);
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == EXIT_RETVAL)
				exit(EXIT_SUCCESS);
		}
	}
}
