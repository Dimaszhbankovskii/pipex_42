#include "../includes/pipex_bonus.h"

static void	parsing_commands(t_pipexb *pipex)
{
	int	i;

	pipex->num_cmds = pipex->argc - 3 - pipex->here_doc;
	pipex->cmds = (char ***)malloc(sizeof(char **) * (pipex->num_cmds + 1));
	if (!pipex->cmds)
		end_program(ERROR_PARSING_CMDS, pipex, 0, 0);
	i = 0;
	while (i < pipex->num_cmds)
	{
		pipex->cmds[i] = ft_split(pipex->argv[2 + pipex->here_doc + i], ' ');
		if (!pipex->cmds[i])
			end_program(ERROR_PARSING_CMDS, pipex, 0, 0);
		i++;
	}
	pipex->cmds[i] = NULL;
}

static void	create_pipes(t_pipexb *pipex)
{
	int	i;

	pipex->num_pipes = 2 * (pipex->num_cmds - 1);
	pipex->pipes = (int *)malloc(sizeof(int) * pipex->num_pipes);
	if (!pipex->pipes)
	{
		close_files(pipex);
		end_program(ERROR_PIPE, pipex, HERE_DOC_EXIST, 0);
	}
	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		if (pipe(pipex->pipes + i * 2) < 0)
		{
			close_files(pipex);
			end_program(ERROR_PIPE, pipex, HERE_DOC_EXIST, errno);
		}
		i++;
	}
}

void	parsing_data(t_pipexb *pipex)
{
	parsing_here_doc(pipex);
	parsing_commands(pipex);
	create_paths(pipex);
	open_files(pipex);
	create_pipes(pipex);
}
