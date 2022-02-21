#include "../includes/pipex_bonus.h"

static char	**parsing_paths(t_pipexb *pipex)
{
	char	*tmp1;
	char	*tmp2;
	char	**paths;

	tmp1 = find_str(pipex->envp, "PATH=");
	if (!tmp1)
		end_program(ERROR_NO_PATHS_IN_ENVP, pipex, 0);
	tmp2 = ft_strdup(tmp1 + ft_strlen("PATH="));
	if (!tmp2)
		end_program(ERROR_PARSING_PATHS, pipex, 0);
	paths = ft_split(tmp2, ':');
	if (!paths)
	{
		free(tmp2);
		end_program(ERROR_PARSING_PATHS, pipex, 0);
	}
	free (tmp2);
	return (paths);
}

static char	*search_paths(t_pipexb *pipex, char *cmd)
{
	int		i;
	char	*tmp;
	char	*filename;

	i = 0;
	while (pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		if (!tmp)
			end_program(ERROR_SEARCH_PATH_CMD, pipex, 0);
		filename = ft_strjoin(tmp, cmd);
		if (!filename)
			end_program(ERROR_SEARCH_PATH_CMD, pipex, 0);
		free(tmp);
		if (!access(filename, 1))
			return (filename);
		i++;
		free(filename);
	}
	return (NULL);
}

void	create_paths(t_pipexb *pipex)
{
	int	i;

	pipex->paths = parsing_paths(pipex);
	pipex->path_cmd = (char **)malloc(sizeof(char *) * (pipex->num_cmds + 1));
	if (!pipex->path_cmd)
		end_program(ERROR_INIT_PATH_CMD, pipex, 0);
	i = 0;
	while (i < pipex->num_cmds)
	{
		pipex->path_cmd[i] = search_paths(pipex, pipex->cmds[i][0]);
		if (!pipex->path_cmd[i])
			end_program(ERROR_NO_PATH_CMD, pipex, 0);
		i++;
	}
}
