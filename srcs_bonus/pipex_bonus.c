#include "../includes/pipex_bonus.h"

static t_pipexb	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipexb	*pipex;

	pipex = (t_pipexb *)malloc(sizeof(t_pipexb));
	if (!pipex)
		end_program(ERROR_INIT_PIPEX, NULL, 0, 0);
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

int	main(int argc, char **argv, char **envp)
{
	t_pipexb	*pipex;

	if (argc < 5)
		end_program(ERROR_NUMBER_ARGS, NULL, 0, 0);
	pipex = init_pipex(argc, argv, envp);
	parsing_data(pipex);
	pipex->index = 0;
	while (pipex->index < pipex->num_cmds)
	{
		child_process(pipex);
		pipex->index++;
	}
	close_pipes(pipex);
	if (waitpid(-1, NULL, 0) < 0)
		end_program(ERROR_WAIT_CHILD, pipex, HERE_DOC_EXIST, errno);
	close_files(pipex);
	close_here_doc(pipex);
	free_pipex(pipex);
	return (0);
}
