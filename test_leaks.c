#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static int	ft_strcmp(char const *str1, char const *str2)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str1) || i < ft_strlen(str2))
	{
		if (str1[i] != str2[i] || !str1[i] || !str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

static void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!src && !dst)
		return (NULL);
	if (dst < src)
	{
		s = (unsigned char *)src;
		d = (unsigned char *)dst;
		while (n--)
			*d++ = *s++;
	}
	else
	{
		s = (unsigned char *)src + n;
		d = (unsigned char *)dst + n;
		while (n--)
			*--d = *--s;
	}
	return (dst);
}


static int	free_buffer(int read_bytes, char *buffer)
{
	free(buffer);
	buffer = NULL;
	if (read_bytes < 0)
		return (-1);
	else if (read_bytes == 0)
		return (0);
	else
		return (1);
}

static size_t	ft_findline(char const *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	str_len;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_len = s1_len + s2_len;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, s1_len);
	ft_memmove(str + s1_len, s2, s2_len);
	str[str_len] = '\0';
	free (s1);
	return (str);
}

static char	*ft_make_line(char const *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(*str) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_save_str(char *str)
{
	char	*str_out;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\n' && str[i] && str)
		i++;
	if (!str[i] || !str)
	{
		free (str);
		return (NULL);
	}
	str_out = (char *)malloc(sizeof(*str) * (ft_strlen(str) - i));
	if (!str_out)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		str_out[j++] = str[i++];
	str_out[j] = '\0';
	free (str);
	return (str_out);
}

int	get_next_line(int fd, char **line)
{
	static char	*str;
	char		*buffer;
	ssize_t		read_bytes;

	if (fd < 0 || fd > 255 || BUFFER_SIZE < 1)
		return (-1);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	read_bytes = 1;
	while (!ft_findline(str) && read_bytes)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free_buffer(read_bytes, buffer));
		buffer[read_bytes] = '\0';
		str = ft_strjoin_gnl(str, buffer);
	}
	*line = ft_make_line(str);
	str = ft_save_str(str);
	return (free_buffer(read_bytes, buffer));
}

#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
		return (1);
	while (1)
	{
		if (get_next_line(0, &line) <= 0)
			exit (1);
		if (!ft_strcmp(line, "STOP\n"))
			break ;
		write(fd, line, ft_strlen(line));
		free (line);
		line = NULL;
	}
	free (line);
	line = NULL;
	printf("fd = %d\n", fd);
	// if (close(fd) == 0)
	// 	printf("Close fd tmp\n");
	// else
	// 	printf("Error: close fd tmp\n");
	// printf("fd = %d\n", fd);
	if (unlink("/home/dimasik99/school_21/ladarys/pipex_42/tmp") == 0)
		printf("Unlink tmp\n");
	else
		printf("Error: unlink tmp\n");
	if (close(fd) == 0)
		printf("Close fd tmp\n");
	else
		printf("Error: close fd tmp\n");
	printf("end\n");
	return (0);
}
