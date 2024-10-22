#include "minishell.h"

int	check_for_limiter(char *limiter, char *line)
{
	int		line_length;
	char	*parsed_line;

	line_length = ft_strlen(line);
	if (line[0] == '"' && line[line_length] == '"')
	{
		parsed_line = ft_substr(line, 1, line_length - 2);
		line = parsed_line;
	}
	if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
		return (0);
	return (1);
}

int	create_here_doc(char *limiter, int fdin, char *command)
{
	char	buffer[2];

	buffer[1] = 0;
	while (1)
	{
		read(0, buffer, 1);
		command = ft_strjoin(command, buffer);
		if (ft_strncmp(buffer, "\n", 1) == 0)
		{
			if (check_for_limiter(limiter, command) == 0)
			{
				command = 0;
				break ;
			}
			else
			{
				write(fdin, command, ft_strlen(command));
				command = 0;
			}
		}
	}
	close(fdin);
	return (open("temp.txt", O_RDONLY, 0666));
}

int	input_stuff(t_mini *mini, int *i)
{
	int		fdin;

	if (ft_strncmp(mini->arguments[*i + 1], "<<", 3) == 0)
	{
		fdin = open("here_doc.txt", O_CREAT | O_WRONLY | O_TRUNC, 06444);
		fdin = create_here_doc(mini->arguments[*i + 1], fdin, NULL);
		mini->store = 2;
	}
	else if (ft_strncmp(mini->arguments[*i + 1], "<", 2) == 0)
	{
		fdin = open(mini->arguments[*i + 2], O_RDONLY, 06444);
		mini->store = 2;
	}
	else if (ft_strncmp(mini->arguments[*i], "<<", 3) == 0 ||
		ft_strncmp(mini->arguments[*i], "<", 2) == 0)
		*i += 3;
	return fdin;
}