#include "../includes/pipex.h"

int	main(void)
{
	int	end[2];
	pid_t	process;

	if (pipe(end) < 0)
		ft_putstr_fd("error pipe()\n", 1);
	process = fork();
	if (process < 0)
		ft_putstr_fd("error fork()\n", 1);
	if (!process)
		child_process();
	else
		parent_process();
	return (0);
}
