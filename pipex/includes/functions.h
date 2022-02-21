#ifndef FUNCTION_H
# define FUNCTION_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlen(const char *str);
int		ft_strcmp(char const *str1, char const *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
void	*ft_memmove(void *dst, const void *src, size_t n);

int		get_next_line(int fd, char **line);
int		free_buffer(int read_bytes, char *buffer);

#endif