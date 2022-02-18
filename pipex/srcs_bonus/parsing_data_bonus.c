#include "../includes/pipex_bonus.h"

static void	parsing_commands(t_pipexb *pipex)
{
	int	i;

	pipex->num_cmds = pipex->argc - 3 - pipex->here_doc;
	pipex->cmds = (char ***)malloc(sizeof(char **) * (pipex->num_cmds + 1));
	if (!pipex->cmds)
		exit (1);
	i = 0;
	while (i < pipex->num_cmds)
	{
		pipex->cmds[i] = ft_split(pipex->argv[2 + pipex->here_doc + i], ' ');
		if (!pipex->cmds[i])
			exit (1);
		i++;
	}
	pipex->cmds[i] = NULL;
}

void	parsing_data(t_pipexb *pipex)
{
	parsing_here_doc(pipex);
	parsing_commands(pipex);
	create_paths(pipex);
	open_files(pipex);
}
