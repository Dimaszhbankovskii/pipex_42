#include "../includes/pipex_bonus.h"

char	*find_str(char **array, char *str)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		if (!ft_strncmp(array[i], str, ft_strlen(str)))
			return (array[i]);
		i++;
	}
	return (NULL);
}

void	close_pipes(t_pipexb *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->num_pipes)
	{
		if (close(pipex->pipes[i]) < 0)
		{
			close_files(pipex);
			end_program(ERROR_CLOSE_FD, pipex, HERE_DOC_EXIST, errno);
		}
		i++;
	}
}

void	close_files(t_pipexb *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
}

void	end_program(char *mess, t_pipexb *pipex, int mode, int code)
{
	if (mode == HERE_DOC_EXIST)
		close_here_doc(pipex);
	perror(mess);
	free_pipex(pipex);
	exit (code);
}
