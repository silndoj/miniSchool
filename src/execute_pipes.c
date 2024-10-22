#include "minishell.h"

void	exec(char *cmd, t_mini *mini)
{
	char	**args;
	char	*path;

	args = allocate_command(cmd, mini, 0);
	path = find_path(mini->envp, args[0]);
	if (path == 0)
		exit(127);
	execve(path, args, mini->envp);
	exit(127);
}

void execute_command(t_mini *mini, int *i, int fdin, int fdout)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		if(ft_strncmp(mini->arguments[*i + 1 + mini->store], "|", 1) == 0 && mini->store != 4)
		{
			ft_putstr_fd(mini->arguments[*i], 2);
			redirect(mini->arguments[*i], mini);
			exit(0);
		}
		else
		{
			exec(mini->arguments[*i], mini);
		}
	}
	waitpid(pid, &mini->exitcode, 0);
	if(fdin != 0)
		close(fdin);
	if(fdout != 1)
		close(fdout);
}

void	execute_pipes(t_mini *mini, int i)
{

	int fdout;
	int fdin;

	while (mini->arguments[i] != 0)
	{
		if (ft_strncmp(mini->arguments[i], "|", 2) == 0
			|| ft_strncmp(mini->arguments[i], "&&", 3) == 0)
			i ++;
		fdout = 1;
		fdin = 0;
		fdin = input_stuff(mini, &i);
		fdout = output_stuff(mini, i);
		execute_command(mini, &i, fdin , fdout);
		i += 1 + mini->store;
		mini->store = 0;
	}
}

void	redirect(char *cmd, t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if(pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec(cmd, mini);
	}
}
