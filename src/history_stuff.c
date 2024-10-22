#include "minishell.h"

void	read_perma_history(void)
{
	int fd;
	char buffer[2];
	char *line;

	line = 0;
	fd = open("tools/history.txt", O_RDONLY);
	buffer[1] = 0;
	while(read(fd, buffer, 1) > 0)
	{
		if (buffer[0] == '\n')
		{
			add_history(line);
			line = 0;
		}
		else
		line = ft_strjoin(line, buffer);
	}
}

void	perma_history(char *cmdline)
{
	int		fd;
	char	*line;

	fd = open("tools/history.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	line = ft_strjoin(cmdline, "\n");
	write(fd, line, ft_strlen(line));
	close(fd);
}
