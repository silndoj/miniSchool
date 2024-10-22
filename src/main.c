#include "minishell.h"

void	print_arguments(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i] != 0)
	{
		printf("%s\n", arguments[i]);
		fflush(stdout);
		i ++;
	}
}

void	mini_loop(t_mini mini)
{
	while (mini.finished == 0)
	{
		mini.argc = 0;
		mini.exitstatus = WEXITSTATUS(mini.exitcode);
		mini.line = readline("KUHN_SILVESTRI_SHELL % ");
		if (mini.line == 0)
			exit(0);
		if(ft_strncmp(mini.line, "", 1) == 0)
			continue;
		perma_history(mini.line);
		add_history(mini.line);
		mini.arguments = allocate_command(mini.line, &mini, 0);
		//print_arguments(mini.arguments);
		execute(&mini);
		unlink("temp.txt");
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_mini	mini;

	add_signalhandler(&mini);

	if (argc != 0)
		argv[1] = 0;
	init(&mini, env);
	mini_loop(mini);
	return (0);
}
