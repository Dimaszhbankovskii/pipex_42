#include "../includes/pipex_bonus.h"

static void	close_files(t_pipexb *pipex)
{
	if (close (pipex->infile) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
	if (close (pipex->outfile) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipexb	*pipex;

	if (argc < 5)
		end_program(ERROR_NUMBER_ARGS, NULL, 0);
	pipex = init_pipex(argc, argv, envp);
	parsing_data(pipex);
	pipex->index = 0;
	while (pipex->index < pipex->num_cmds)
	{
		child_process(pipex);
		pipex->index++;
	}
	close_pipes(pipex);
	waitpid(-1, NULL, 0);
	close_files(pipex);
	free_pipex(pipex);
	return(0);
}
