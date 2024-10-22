#include "minishell.h"

char	**realloc_2dchar(char **src, char *string, int i)
{
	char	**result;
	int		size;

	while (src[i] != 0)
		i ++;
	size = i;
	result = ft_calloc((size + 2), sizeof(char *));
	i = -1;
	while (++ i < size)
		result[i] = ft_strdup(src[i]);
	result[i] = ft_strdup(string);
	result[i + 1] = 0;
	return (result);
}