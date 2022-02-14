#include "../includes/pipex.h"

void	child_process1(t_pipex *pipex)
{
	if (dup2(pipex->file1, STDIN_FILENO) < 0)
		end_prog(strerror(errno), pipex, errno);
	if (dup2(pipex->end[1], STDOUT_FILENO) < 0)
		end_prog(strerror(errno), pipex, errno);
	close(pipex->end[0]);
	close(pipex->file1);
	execve(pipex->path1, pipex->cmd1, pipex->envp);
	end_prog(strerror(errno), pipex, errno);
}

void	child_process2(t_pipex *pipex)
{
	// if (dup2(pipex->file2, STDOUT_FILENO) < 0)
	// 	end_prog(strerror(errno), pipex, errno);

	// if (dup2(pipex->end[0], STDIN_FILENO) < 0)
	// 	end_prog(strerror(errno), pipex, errno);

	dup2(pipex->end[0], STDIN_FILENO);
	dup2(pipex->file2, STDOUT_FILENO);
	close(pipex->end[1]);
	close(pipex->file2);
	execve(pipex->path2, pipex->cmd2, pipex->envp);
	end_prog(strerror(errno), pipex, errno);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	pid_t	child1;
	pid_t	child2;
	int		status[2];

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		end_prog("Error: malloc 'pipex'\n", NULL, 1);
	if (argc == 5)
		parsing_data(pipex, argv, envp);
	else
		end_prog("Error: argc\n", pipex, 0);
	if (pipe(pipex->end) < 0)
		end_prog(strerror(errno), pipex, errno);
	child1 = fork();
	if (child1 < 0)
		end_prog(strerror(errno), pipex, errno);
	if (child1 == 0)
		child_process1(pipex);
	child2 = fork();
	if (child2 < 0)
		end_prog(strerror(errno), pipex, errno);
	if (child2 == 0)
		child_process2(pipex);
	close(pipex->end[0]);
	close(pipex->end[1]);
	close(pipex->file1);
	close(pipex->file2);
	waitpid(child1, &status[0], 0);
	waitpid(child2, &status[1], 0);
	free_pipex(pipex);
	return (0);
}
