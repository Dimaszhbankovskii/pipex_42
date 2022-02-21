#include "../includes/pipex_bonus.h"

void	free_one_dim_array(char *array)
{
	if (array)
	{
		free (array);
		array = NULL;
	}
}

void	free_two_dim_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		free_one_dim_array(array[i++]);
	free(array);
	array = NULL;
}

void	free_three_dim_array(char ***array)
{
	int	i;

	i = 0;
	while (array && array[i])
		free_two_dim_array(array[i++]);
	free (array);
	array = NULL;
}

void	free_pipex(t_pipexb *pipex)
{
	if (pipex)
	{
		free_one_dim_array(pipex->stop_word);
		free_three_dim_array(pipex->cmds);
		free_two_dim_array(pipex->paths);
		free_two_dim_array(pipex->path_cmd);
		free(pipex->end);
		pipex->end = NULL;
		free (pipex);
		pipex = NULL;
	}
}
