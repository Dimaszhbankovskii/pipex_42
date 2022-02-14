#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

typedef struct s_pipex
{
	int		end[2];
    char    **argv;
    char    **envp;
    int     file1;
    int     file2;
    char    **cmd1;
    char    **cmd2;
	char	**paths;
    char    *path1;
    char    *path2;
}               t_pipex;

void	parsing_data(t_pipex *pipex, char **argv, char **envp);

void	free_pipex(t_pipex *pipex);
void	free_array(char **array);
void	end_prog(char *mess, t_pipex *pipex, int code);

#endif