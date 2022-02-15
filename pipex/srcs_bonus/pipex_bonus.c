#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipexb	*pipex;

	if (argc < 5)
		end_prog(ERROR_NUMBER_ARGS, NULL, 0);
	pipex = init_pipex(argc, argv, envp);
	parsing_data(pipex);
	return(0);
}
