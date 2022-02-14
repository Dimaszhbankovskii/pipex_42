#include "../includes/pipex.h"

static char	*find_str(char **envp)
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

static char	**parsing_paths(t_pipex *pipex)
{
	char	*tmp1;
	char	*tmp2;
	char	**paths;

	tmp1 = find_str(pipex->envp);
	if (!tmp1)
		end_prog("Error: no PATH in envp\n", pipex, 2);
	tmp2 = ft_strdup(tmp1 + ft_strlen("PATH="));
	if (!tmp2)
		end_prog("Error: malloc in parsing\n", pipex, 3);
	paths = ft_split(tmp2, ':');
	if (!paths)
	{
		free(tmp2);
		end_prog("Error: malloc in parsing\n", pipex, 3);
	}
	free (tmp2);
	return (paths);
}

static char	*search_path(t_pipex *pipex, char *cmd)
{
	int		i;
	char	*tmp;
	char	*filename;

	i = 0;
	while (pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		if (!tmp)
			end_prog("Error: malloc in search path\n", pipex, 4);
		filename = ft_strjoin(tmp, cmd);
		if (!filename)
			end_prog("Error: malloc in search path\n", pipex, 4);
		free(tmp);
		if (!access(filename, 1))
			return (filename);
		i++;
		free(filename);
	}
	return (NULL);
}

void	parsing_data(t_pipex *pipex, char **argv, char **envp)
{
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->file1 = open(pipex->argv[1], O_RDONLY);
	if (pipex->file1 < 0)
		end_prog("Error: open file1\n", pipex, 1);
	pipex->file2 = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->file2 < 0)
		end_prog("Error: open file2\n", pipex, 1);
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (!pipex->cmd1 || !pipex->cmd2)
		end_prog("Error: malloc in parsing cmd\n", pipex, 1);
	pipex->paths = parsing_paths(pipex);
	pipex->path1 = search_path(pipex, pipex->cmd1[0]);
	pipex->path2 = search_path(pipex, pipex->cmd2[0]);
	if (!pipex->path1 || !pipex->path2)
		end_prog("no path for command\n", pipex, 5);
}
