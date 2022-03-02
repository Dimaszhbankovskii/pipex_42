#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "functions.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# include <stdio.h>
# include <string.h>

# define NAME_HERE_DOC "tmp_here_doc"
# define HERE_DOC_EXIST 1

# define ERROR_NUMBER_ARGS "Error: pipex takes 4 or more arguments"
# define ERROR_INIT_PIPEX "Error: malloc 'pipex'"
# define ERROR_INIT_STOP_WORD "Error: malloc 'stop word'"
# define ERROR_PARSING_CMDS "Error: malloc in parsing commands"
# define ERROR_NO_PATHS_IN_ENVP "Error: no PATH in envp"
# define ERROR_PARSING_PATHS "Error: malloc in parsing"
# define ERROR_INIT_PATH_CMD "Error malloc in init paths of commands"
# define ERROR_SEARCH_PATH_CMD "Error: malloc in search path"
# define ERROR_NO_PATH_CMD "No path for command"
# define ERROR_CREATE_HERE_DOC "Error: create here_doc"
# define ERROR_GET_NEXT_LINE "Error: get next line"
# define ERROR_CLOSE_HERE_DOC "Error: close here_doc"
# define ERROR_UNLINK "Error: unlink"
# define ERROR_CLOSE_FD "Error: close fd"
# define ERROR_OPEN_FILE_READ "Error: open file for reading"
# define ERROR_OPEN_FILE_WRITE "Error: open file for writing"
# define ERROR_PIPE "Error: create pipe"
# define ERROR_FORK "Error: create child-process"
# define ERROR_DUP2 "Error: dup2"
# define ERROR_EXECVE "Error: execve"
# define ERROR_WAIT_CHILD "Error: waitpid child"

typedef struct s_pipexb
{
	int		argc;
	char	**argv;
	char	**envp;
	int		here_doc;
	char	*stop_word;
	int		infile;
	int		outfile;
	int		num_cmds;
	char	***cmds;
	char	**paths;
	char	**path_cmd;
	int		num_pipes;
	int		*pipes;
	int		index;
	pid_t	child;
}				t_pipexb;

void	parsing_data(t_pipexb *pipex);
void	parsing_here_doc(t_pipexb *pipex);
void	create_paths(t_pipexb *pipex);
void	open_files(t_pipexb *pipex);
void	open_here_doc(t_pipexb *pipex);
void	close_here_doc(t_pipexb *pipex);

void	close_pipes(t_pipexb *pipex);
void	child_process(t_pipexb *pipex);

void	end_program(char *mess, t_pipexb *pipex, int mode, int code);
char	*find_str(char **array, char *str);
void	close_files(t_pipexb *pipex);

void	free_pipex(t_pipexb *pipex);
void	free_one_dim_array(char *array);
void	free_two_dim_array(char **array);
void	free_three_dim_array(char ***array);

#endif