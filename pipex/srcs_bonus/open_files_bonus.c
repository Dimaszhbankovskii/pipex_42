#include "../includes/pipex_bonus.h"

void	open_files(t_pipexb *pipex)
{
	if (pipex->here_doc)
		open_here_doc(pipex);
	else
	{
		pipex->infile = open(pipex->argv[1], O_RDONLY);
		if (pipex->infile < 0)
			end_program(ERROR_OPEN_FILE_READ, pipex, 0);
	}
	if (pipex->here_doc)  
		pipex->outfile = open(pipex->argv[pipex->argc - 1], \
		O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		pipex->outfile = open(pipex->argv[pipex->argc - 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->outfile < 0)
		end_program(ERROR_OPEN_FILE_WRITE, pipex, 0);
}
