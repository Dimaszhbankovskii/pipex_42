#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipexb	*pipex;

	if (argc < 5)
		end_program(ERROR_NUMBER_ARGS, NULL, 0);
	pipex = init_pipex(argc, argv, envp);
	parsing_data(pipex);
	while (pipex->index < pipex->num_cmds)
	{
		child_process(pipex);
		pipex->index++;
	}
	close_pipes(pipex);
	waitpid(-1, NULL, 0);
	close(pipex->infile);
	close(pipex->outfile);
	return(0);
}
