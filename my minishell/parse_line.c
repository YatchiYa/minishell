#include "minishell.h"

void		parse_line(char *line)
{
	char	**str;

	str = split_commande(line);
	
	if (strcmp(line, "") == 0)
		;
	else if (strcmp(str[0], "exit") == 0)
		exit_shell();
	else if (strcmp(str[0], "echo") == 0)
		handle_echo(str[1]);
	else if (strcmp(str[0], "pwd") == 0)
		handle_pwd();
	else
		ft_putstr("minishell : commande not found \n");
}