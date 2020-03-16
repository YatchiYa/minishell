
#include "minishell.h"

void	minishell(char **envv)
{
    char		*line;
	char		**env;
	int			ret;
	int			status;

	status = 1;
	while (status)
	{
		line = NULL;
		display_prompt_msg();
		signal(SIGINT, signal_handler);
		signal(SIGBREAK, signal_handler2);
		ret = get_next_line(0, &line);
		parse_line(line);
		free(line);
	}
}

int		main(int ac, char **av, char **envv)
{
	init_envv(ac, av, envv);
	system("clear");
	ft_putstr(" \033[31mWelcome\033[0m\033[32mTo\033[0m\033[33m << ");
	ft_putstr("\033[0m\033[34mMinishell\033[0m\033[35m >>\033[0m$ \n");
	minishell(envv);
	return (EXIT_SUCCESS);
}