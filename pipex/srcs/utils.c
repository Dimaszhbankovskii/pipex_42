#include "../includes/pipex.h"

t_pipex	*init_pipex(void)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		end_program(ERROR_INIT_PIPEX, NULL, 0);
	pipex->argv = NULL;
	pipex->envp = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->paths = NULL;
	pipex->path1 = NULL;
	pipex->path2 = NULL;
	return (pipex);
}

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
		if (pipex->cmd1)
			free_array(pipex->cmd1);
		if (pipex->cmd2)
			free_array(pipex->cmd2);
		if (pipex->paths)
			free_array(pipex->paths);
		if (pipex->path1)
		{
			free(pipex->path1);
			pipex->path1 = NULL;
		}
		free(pipex->path2);
		pipex->path2 = NULL;
		free(pipex);
		pipex = NULL;
	}
}

void	end_program(char *mess, t_pipex *pipex, int code)
{
	perror(mess);
	free_pipex(pipex);
	exit (code);
}
