#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

# define ERROR_NUMBER_ARGS "Error: pipex takes 4 or more arguments"
# define ERROR_INIT_PIPEX "Error: malloc 'pipex'"
# define ERROR_OPEN_FILE_READ "Error: open file for reading"
# define ERROR_OPEN_FILE_WRITE "Error: open file for writing"
# define ERROR_SPLIT_CMD "Error: malloc in parsing command"
# define ERROR_NO_PATHS_IN_ENVP "Error: no PATH in envp"
# define ERROR_PARSING_PATHS "Error: malloc in parsing"
# define ERROR_SEARCH_PATH_CMD "Error: malloc in search path"
# define ERROR_NO_PATH_CMD "No path for command"
# define ERROR_PIPE "Error: create pipe"
# define ERROR_FORK "Error: create child-process"
# define ERROR_DUP2 "Error: dup2"
# define ERROR_CLOSE_FD "Error: close fd"
# define ERROR_EXECVE "Error: execve"
# define ERROR_WAIT_CHILD1 "Error: waitpid child1"
# define ERROR_WAIT_CHILD2 "Error: waitpid child2"

typedef struct s_pipexb
{
	int		argc;
	char	**argv;
	char	**envp;
	int		here_doc;
	char	*stop_word;
	int		num_cmds;
	char	***cmds;
	char	**paths;
	char	**path_cmd;
	int		num_pipe;
	int		*end;
    int     file1;
    int     file2;
    pid_t   child1;
    pid_t   child2;
}               t_pipexb;

void	    parsing_data(t_pipexb *pipex);

t_pipexb	*init_pipex(int argc, char **argv, char **envp);

void	free_pipex(t_pipex *pipex);
void	free_array(char **array);
void	end_prog(char *mess, t_pipex *pipex, int code);

size_t	ft_strlen(const char *str); //+
int		ft_strcmp(char const *str1, char const *str2); //+
int	    ft_strncmp(const char *str1, const char *str2, size_t n); //+
char	**ft_split(char const *s, char c); //+
char	*ft_strjoin(char const *s1, char const *s2); //+
char	*ft_strdup(const char *s1); //+

#endif