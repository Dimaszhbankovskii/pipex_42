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

void	open_here_doc(t_pipexb *pipex)
{
	int		tmp;
	char	*line;

	tmp = open("tmp_here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (tmp < 0)
		exit (1); //edit
	while (get_next_line(0, &line) >= 0)
	{
		if (!line )
	}
}
