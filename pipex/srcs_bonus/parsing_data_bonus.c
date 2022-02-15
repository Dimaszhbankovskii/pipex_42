#include "../includes/pipex_bonus.h"

void	parsing_here_doc(t_pipexb *pipex)
{
	if (pipex->argv && !ft_strcmp(pipex->argv[1], "here_doc"))
	{
		if (pipex->argc > 5)
		{
			pipex->here_doc = 1;
			pipex->stop_word = pipex->argv[2];
		}
		else
			exit (1);
	}
	else
		pipex->here_doc = 0;
}

void	parsing_commands(t_pipexb *pipex)
{
	int	i;

	pipex->num_cmds = pipex->argc - 3 - pipex->here_doc;
	pipex->cmds = (char ***)malloc(pipex->num_cmds + 1);
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

static char	*find_str_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static char	**parsing_paths(t_pipexb *pipex)
{
	char	*tmp1;
	char	*tmp2;
	char	**paths;

	tmp1 = find_str_path(pipex->envp);
	if (!tmp1)
		end_program(ERROR_NO_PATHS_IN_ENVP, pipex, 0); //edit
	tmp2 = ft_strdup(tmp1 + ft_strlen("PATH="));
	if (!tmp2)
		end_program(ERROR_PARSING_PATHS, pipex, 0); //edit
	paths = ft_split(tmp2, ':');
	if (!paths)
	{
		free(tmp2);
		end_program(ERROR_PARSING_PATHS, pipex, 0); //edit
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

void	parsing_data(t_pipexb *pipex)
{
	int	i;

	parsing_here_doc(pipex);
	parsing_commands(pipex);
	pipex->paths = parsing_paths(pipex);
	pipex->path_cmd = (char **)malloc(sizeof(char *) * (pipex->num_cmds + 1));
	i = 0;
	while (i < pipex->num_cmds)
	{
		pipex->path_cmd[i] = search_paths(pipex, pipex->cmds[i]);
		i++;
	}
}
