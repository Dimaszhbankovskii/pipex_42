#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int	i;

	printf("------------------------------------------\n");
	printf("---------------   argc:  -----------------\n");
	i = 0;
	while (argv[i])
		printf("%s\n", argv[i++]);
	printf("------------------------------------------\n");
	printf("---------------   envp:  -----------------\n");
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (0);
}
