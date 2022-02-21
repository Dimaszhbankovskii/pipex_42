#include "../includes/pipex_bonus.h"

static void	parsing_commands(t_pipexb *pipex)
{
	int	i;

	pipex->num_cmds = pipex->argc - 3 - pipex->here_doc;
	pipex->cmds = (char ***)malloc(sizeof(char **) * (pipex->num_cmds + 1));
	if (!pipex->cmds)
		end_program(ERROR_PARSING_CMDS, pipex, 0);
	i = 0;
	while (i < pipex->num_cmds)
	{
		pipex->cmds[i] = ft_split(pipex->argv[2 + pipex->here_doc + i], ' ');
		if (!pipex->cmds[i])
			end_program(ERROR_PARSING_CMDS, pipex, 0);
		i++;
	}
	pipex->cmds[i] = NULL;
}

static void	create_pipes(t_pipexb *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->num_pipe)
	{
		if (pipe(pipex->end + 2 * i) < 0)
			exit (1);
		i++;
	}
}

void	parsing_data(t_pipexb *pipex)
{
	parsing_here_doc(pipex);
	parsing_commands(pipex);
	create_paths(pipex);
	open_files(pipex);
	pipex->num_pipe = pipex->num_cmds - 1;
	pipex->end = (int *)malloc(sizeof(int) * pipex->num_pipe * 2);
	if (!pipex->end)
		exit (1); //edit
	create_pipes(pipex);
	pipex->index = 0;
}
