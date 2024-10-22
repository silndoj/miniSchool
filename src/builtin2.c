#include "minishell.h"

void	execvecall_for_everythingelse(t_mini *mini)
{
	char	*path;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		path = find_path(mini->envp, mini->arguments[0]);
		execve(path, mini->arguments, mini->envp);
	}
	waitpid(pid, &mini->exitcode, 0);
}

void	unset(t_mini *mini)
{
	int		j;
	char	*string;
	int		i;

	i = 0;
	if (mini->argc < 2)
		return ;
	while (++ i < mini->argc)
	{
		j = check_envp(mini, mini->arguments[i]);
		string = ft_strjoin(mini->arguments[i], "=");
		if (j == 0)
			return ;
		else
			realloc_smaller_2d(mini, string);
	}
}
