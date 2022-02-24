#include "../includes/pipex_bonus.h"

t_pipexb	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipexb	*pipex;

	pipex = (t_pipexb *)malloc(sizeof(t_pipexb));
	if (!pipex)
		end_program(ERROR_INIT_PIPEX, NULL, 0);
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->stop_word = NULL;
	pipex->cmds = NULL;
	pipex->paths = NULL;
	pipex->path_cmd = NULL;
	pipex->pipes = NULL;
	return (pipex);
}

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

void	end_program(char *mess, t_pipexb *pipex, int code)
{
	perror(mess);
	free_pipex(pipex);
	exit (code);
}
