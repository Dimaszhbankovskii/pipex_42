#include "../includes/pipex_bonus.h"

static void	comb_dup(int fd1, int fd2, t_pipexb *pipex)
{
	if (dup2(fd1, STDIN_FILENO) < 0)
	{
		close(pipex->infile);
		close(pipex->outfile);
		end_program(ERROR_DUP2, pipex, HERE_DOC_EXIST, errno);
	}
	if (dup2(fd2, STDOUT_FILENO) < 0)
	{
		close(pipex->infile);
		close(pipex->outfile);
		end_program(ERROR_DUP2, pipex, HERE_DOC_EXIST, errno);
	}
}

void	child_process(t_pipexb *pipex)
{
	pipex->child = fork();
	if (pipex->child < 0)
		end_program(ERROR_FORK, pipex, HERE_DOC_EXIST, errno); // ++
	if (pipex->child == 0)
	{
		if (!pipex->index)
			comb_dup(pipex->infile, pipex->pipes[1], pipex);
		else if (pipex->index == pipex->num_cmds - 1)
			comb_dup(pipex->pipes[pipex->index * 2 - 2], \
			pipex->outfile, pipex);
		else
			comb_dup(pipex->pipes[pipex->index * 2 - 2], \
			pipex->pipes[pipex->index * 2 + 1], pipex);
		close_pipes(pipex);
		close_files(pipex);
		execve(pipex->path_cmd[pipex->index], \
		pipex->cmds[pipex->index], pipex->envp);
		exit (1); //edit end program
	}
}
