#include "../includes/pipex_bonus.h"

void	close_pipes(t_pipexb *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->num_pipe)
	{
		close(pipex->end[i]);
		i++;
	}
}

static void	comb_dup(int fd1, int fd2)
{
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
}

void	child_process(t_pipexb *pipex)
{
	pipex->child = fork();
	if (pipex->child < 0)
		end_program(ERROR_FORK, pipex, errno);
	if (!pipex->child)
	{
		printf("----->  child %d  <-----\n", pipex->index);
		if (!pipex->index)
		{
			printf("cmd = %s\n", pipex->path_cmd[pipex->index]);
			comb_dup(pipex->infile, pipex->end[1]);
		}
		else if (pipex->index == pipex->num_cmds - 1)
		{
			printf("cmd = %s\n", pipex->path_cmd[pipex->index]);
			comb_dup(pipex->end[2 * pipex->index - 2], pipex->outfile);
		}
		else
		{
			printf("cmd = %s\n", pipex->path_cmd[pipex->index]);
			comb_dup(pipex->end[2 * pipex->index - 2], \
			pipex->end[2 * pipex->index + 1]);
		}
		close_pipes(pipex);
		// printf("cmd with flags = %s\n", pipex->path_cmd[pipex->index]);
		execve(pipex->path_cmd[pipex->index], \
		pipex->cmds[pipex->index], pipex->envp);
		printf("error\n"); //edit
		exit (1); //edit
	}
}
