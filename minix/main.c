
#include "minishell.h"

void	signal_handler_main()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler2);
	signal(SIGTSTP, signal_handler3);
}

void	exec_command(char *line)
{
	int		ret;
	char	**tab;

	ret = 0;
	line = ft_substr(line, 0, ft_strlenx(line) - 1);
	tab = ft_strsplit(line, ';');
	ret = 0;
	while (tab[ret])
	{
		parse_line(tab[ret]);
		ret++;
	}
}

void	minishell(char **envv)
{
    char		*line;
	char		*buff;
	int			ret;
	char		**tab;
	char		*first_char;

	buff = NULL;
	line = strdup(" ");
	while (1)
	{
		if (ctrld == 0)
			display_prompt_msg();
		signal_handler_main();
		ret = get_next_line(0, &buff);
		line = ft_strjoin(line, buff);
		line = ft_substr(line, 1, ft_strlenx(line));
		if (ctrld == 1)
			first_char = ft_substr(line, 0, 1);
		if (ft_strlenx(line) == 0 && ctrld == 1)
			exit(0);
		if (line[ft_strlenx(line) - 1] != '\n')
		{
			free(buff);
			if (ctrld == 1)
				line = ft_strjoin(first_char, line);
			ctrld = 1;
			line = strdup(line);
		}
		else
		{
			exec_command(line);
			ctrld = 0;
			free(buff);
			free(line);
			line = strdup(" ");
		}
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
