#include "../includes/pipex.h"

static void	child_process1(t_pipex *pipex)
{
	if (dup2(pipex->file1, STDIN_FILENO) < 0)
		end_program(ERROR_DUP2, pipex, errno);
	if (dup2(pipex->end[1], STDOUT_FILENO) < 0)
		end_program(ERROR_DUP2, pipex, errno);
	if (close(pipex->end[0]) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
	if (close(pipex->file1) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
	execve(pipex->path1, pipex->cmd1, pipex->envp);
	end_program(ERROR_EXECVE, pipex, errno);
}

static void	child_process2(t_pipex *pipex)
{
	if (dup2(pipex->end[0], STDIN_FILENO) < 0)
		end_program(ERROR_DUP2, pipex, errno);
	if (dup2(pipex->file2, STDOUT_FILENO) < 0)
		end_program(ERROR_DUP2, pipex, errno);
	if (close(pipex->end[1]) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
	if (close(pipex->file2) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
	execve(pipex->path2, pipex->cmd2, pipex->envp);
	end_program(ERROR_EXECVE, pipex, errno);
}

static void	clode_all_fd(t_pipex *pipex)
{
	if (close(pipex->end[0]) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
	if (close(pipex->end[1]) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
	if (close(pipex->file1) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
	if (close(pipex->file2) < 0)
		end_program(ERROR_CLOSE_FD, pipex, errno);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		end_program(ERROR_NUMBER_ARGS, NULL, 0);
	pipex = init_pipex();
	parsing_data(pipex, argv, envp);
	if (pipe(pipex->end) < 0)
		end_program(ERROR_PIPE, pipex, errno);
	pipex->child1 = fork();
	if (pipex->child1 < 0)
		end_program(ERROR_FORK, pipex, errno);
	if (pipex->child1 == 0)
		child_process1(pipex);
	pipex->child2 = fork();
	if (pipex->child2 < 0)
		end_program(ERROR_FORK, pipex, errno);
	if (pipex->child2 == 0)
		child_process2(pipex);
	clode_all_fd(pipex);
	if (waitpid(pipex->child1, NULL, 0) < 0)
		end_program(ERROR_WAIT_CHILD1, pipex, errno);
	if (waitpid(pipex->child2, NULL, 0) < 0)
		end_program(ERROR_WAIT_CHILD1, pipex, errno);
	free_pipex(pipex);
	return (0);
}
