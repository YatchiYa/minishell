#include "minishell.h"

void	extendx(char *str, char c)
{
	int		i;
	char	*line;

	i = 0;
	while (str[ft_strlenx(str) - 1] != c && calc_c(str, c) % 2 != 0)
	{
		line = NULL;
		ft_putstr("quote > ");
		get_next_line(0, &line);
		str = ft_strjoin(str, "\\n");
		str = ft_strjoin(str, line);
	}
    ft_putstr("Minishell : commande not found");   
    ft_putstr(str);
    ft_putstr("\n");
}

void		trim_parse_ex(char *dest, char *str)
{
	char	**tab;
	
	tab = split_commande(dest);
	if (((tab[0][0] == '"' || tab[0][0] == '\'') && (tab[0][1] == ' ' || tab[0][1] == '\0'))
		|| ((tab[0][ft_strlenx(tab[0])] == '"' || tab[0][ft_strlenx(tab[0])] == '\'') && (tab[0][ft_strlenx(tab[0]) - 1] == ' ' || tab[0][ft_strlenx(tab[0]) - 1] == '\0')))
	{
		ft_putstr("command error :");   
		ft_putstr(tab[0]);
	}
	else
	{
		tab[0] = ft_substr(tab[0], 1, ft_strlenx(tab[0]) - 2);
		tab[0] = ft_strjoin(tab[0], " ");
		str = ft_strjoin(tab[0], tab[1]);
		parse_line(str);
	}
}

void		trim_parse(char *str)
{
    char	*dest;
    int		ret;
	int		xet;
	
	dest = trim_quote(str, &ret, &xet);
	if (ret % 2 != 0 && ret != 0)
		extendx(dest, '\"');
	else if (xet % 2 != 0 && xet != 0)
		extendx(dest, '\'');
	else
		trim_parse_ex(dest, str);    
}

void		parse_line(char *line)
{
	char	**str;
	
	while (*line == ' ')
		line++;
	str = split_commande(line);
	if (strcmp(line, "") == 0)
		;
	else if (strcmp(line, "clear") == 0)
		system("clear");
	else if (line[0] == '"' || line[0] == '\'')
		trim_parse(line);
	else if (line[0] == '$')
	{
		ft_putstr(parse_dollar(line));
		strcmp(parse_dollar(line), " ") != 0 ? ft_putstr(": commande not valid \n") :  ft_putstr("\n");
	}
	else if (strcmp(str[0], "touch") == 0 || strcmp(str[0], "/bin/touch") == 0)
		handle_touch(str[1]);
	else if (strcmp(str[0], "rm") == 0 || strcmp(str[0], "/bin/rm") == 0)
		handle_rm(str[1]);
	else if (strcmp(str[0], "exit") == 0 || strcmp(str[0], "/bin/exit") == 0)
		exit_shell();
	else if (strcmp(str[0], "echo") == 0 || strcmp(str[0], "/bin/echo") == 0)
		handle_echo(str[1]);
	else if (strcmp(str[0], "pwd") == 0 || strcmp(str[0], "/bin/pwd") == 0)
		handle_pwd(str[1]);
	else if (strcmp(str[0], "cd") == 0 || strcmp(str[0], "/bin/cd") == 0)
		handle_cd(str[1]);
	else if (strcmp(str[0], "env") == 0 || strcmp(str[0], "/bin/env") == 0)
		handle_env(str[0], str[1]);
	else if (strcmp(str[0], "export") == 0 || strcmp(str[0], "/bin/export") == 0)
		handle_export(str[1]);
	else if (strcmp(str[0], "unset") == 0 || strcmp(str[0], "/bin/unset") == 0)
		handle_unset(str[1]);
	else
		ft_putstr("minishell => commande not found \n");
}
