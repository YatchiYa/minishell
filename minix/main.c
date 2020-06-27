
#include "minishell.h"

void	test(char **stock)
{
	char	*line;
	int		ret;
	char		*buffer;

	line = NULL;
	printf("-test-\n");

	if (!(buffer = malloc(sizeof(char) * (4200 + 1)))
	|| read(0, buffer, 0) < 0)
		return ;
	ret = read(0, buffer, 4200);
	*stock = ft_strjoin(*stock, line);
	if (strcontains(*stock, '\n') == 1)
		printf("GOOD\n");
	else
	{
		printf("BADD\n");
		test(stock);
	}
}

void	minishell(char **envv)
{
    char		*line;
    char		*nline;
	char		**env;
	int			ret;
	int			status;
	char		**tab;

	status = 1;
	line = NULL;
	nline = NULL;
	ctrld = 0;
	while (status)
	{
		if (ctrld == 0)
			display_prompt_msg();
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler2);
		signal(SIGTSTP, signal_handler3);
		ret = get_next_line(0, &line);
		printf("---> ctrd = %d\n", ctrld);
		if (ft_strlenx(line) == 0 && ctrld == 1)
			exit(0);
		line = ft_substr(line, 1, ft_strlenx(line));
		tab = ft_strsplit(line, ';');
		ret = 0;
		while (tab[ret])
		{
			if (ctrld == 0 && ft_strlenx(line) > 2)
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
