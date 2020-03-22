
#include "minishell.h"

void	minishell(char **envv)
{
    char		*line;
	char		**env;
	int			ret;
	int			status;
	char		**tab;

	status = 1;
	while (status)
	{
		line = NULL;
		display_prompt_msg();
		signal(SIGINT, signal_handler);
		ret = get_next_line(0, &line);
		if (strcmp(line, "^d") == 0 || strcmp(line, "^D") == 0)
			exit_shell();
		tab = ft_strsplit(line, ';');
		ret = 0;
		while (tab[ret])
		{
			parse_line(tab[ret]);
			ret++;
		}
		free(line);
	}
}

int		main(int ac, char **av, char **envv)
{
	init_envv(ac, av, envv);
	system("clear");
	ft_putstr(" \033[31mWelcome\033[0m\033[32mTo\033[0m\033[33m << ");
	ft_putstr("\033[0m\033[34mMinishell\033[0m\033[35m >>\033[0m \n");
	// for now 
	set_env_var("OLDPWD", " ");
	minishell(envv);
	return (EXIT_SUCCESS);
}