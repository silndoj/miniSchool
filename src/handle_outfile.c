#include "minishell.h"

int	output_stuff(t_mini *mini, int i)
{
	int	fdout;

	if (ft_strncmp(mini->arguments[i + 1 + mini->store], ">", 2) == 0)
	{
		fdout = openfile(mini->arguments[i + 2 + mini->store], 1, 0);
		mini->store += 2;
		return fdout;
	}
	else if (ft_strncmp(mini->arguments[i + 1 + mini->store], ">>", 3) == 0)
	{
		fdout = openfile(mini->arguments[i + 2 + mini->store], 1, 1);
		mini->store += 2;
		return fdout;	
	}
	return 1;
}