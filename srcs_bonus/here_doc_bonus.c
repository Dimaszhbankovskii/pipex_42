#include "../includes/pipex_bonus.h"

void	parsing_here_doc(t_pipexb *pipex)
{
	if (pipex->argv && !ft_strcmp(pipex->argv[1], "here_doc"))
	{
		if (pipex->argc > 5)
		{
			pipex->here_doc = 1;
			pipex->stop_word = ft_strjoin(pipex->argv[2], "\n");
			if (!pipex->stop_word)
				end_program(ERROR_INIT_STOP_WORD, pipex, 0, 0);
		}
		else
			pipex->here_doc = 0;
	}
	else
		pipex->here_doc = 0;
}

void	close_here_doc(t_pipexb *pipex)
{
	char	*tmp;
	char	*path;
	char	*pathname;

	if (pipex->here_doc > 0)
	{
		tmp = find_str(pipex->envp, "PWD=");
		if (!tmp)
			end_program(ERROR_CLOSE_HERE_DOC, pipex, 0, 0);
		path = ft_strdup(tmp + ft_strlen("PWD="));
		if (!path)
			end_program(ERROR_CLOSE_HERE_DOC, pipex, 0, 0);
		pathname = ft_strjoin(path, "/tmp_here_doc");
		free_one_dim_array(path);
		if (!pathname)
			end_program(ERROR_CLOSE_HERE_DOC, pipex, 0, 0);
		if (unlink(pathname) < 0)
			end_program(ERROR_UNLINK, pipex, 0, errno);
		free_one_dim_array(pathname);
	}
}

static void	print_pattern(t_pipexb *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		write(1, &"pipe ", 5);
		i++;
	}
	write(1, &"heredoc> ", 9);
}

void	open_here_doc(t_pipexb *pipex)
{
	int		tmp;
	char	*line;

	tmp = open(NAME_HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (tmp < 0)
		end_program(ERROR_CREATE_HERE_DOC, pipex, 0, 0);
	while (1)
	{
		print_pattern(pipex);
		if (get_next_line(0, &line) <= 0)
		{
			close(tmp);
			end_program(ERROR_GET_NEXT_LINE, pipex, HERE_DOC_EXIST, 0);
		}		
		if (!ft_strcmp(line, pipex->stop_word))
			break ;
		write(tmp, line, ft_strlen(line));
		free_one_dim_array(line);
	}
	free_one_dim_array(line);
	if (close(tmp) < 0)
		end_program(ERROR_CLOSE_FD, pipex, HERE_DOC_EXIST, 0);
	pipex->infile = open(NAME_HERE_DOC, O_RDONLY);
	if (pipex->infile < 0)
		end_program(ERROR_OPEN_FILE_READ, pipex, HERE_DOC_EXIST, 0);
}
