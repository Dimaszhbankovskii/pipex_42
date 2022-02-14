#include "../includes/pipex.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex)
	{
		free_array(pipex->cmd1);
		free_array(pipex->cmd2);
		free_array(pipex->paths);
		free(pipex->path1);
		pipex->path1 = NULL;
		free(pipex->path2);
		pipex->path2 = NULL;
		free(pipex);
		pipex = NULL;
	}
}

void	end_prog(char *mess, t_pipex *pipex, int code)
{
	perror(mess);
	free_pipex(pipex);
	exit (code);
}
