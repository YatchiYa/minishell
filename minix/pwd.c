#include "minishell.h"

int			check_arg(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			return (1);
		else if (str[i] > 0 && str[i] < 127 && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void		handle_pwd(char *str)
{
	char	*cwd;
	char	*buff;
	char	*parsed_cwd;

	if (!(buff = malloc(sizeof(char) * 4097)))
		return ;
	cwd = getcwd(buff, 4096);
	if (check_arg(str) == 0)
		ft_putstr("pwd : error too many argument \n");
	else if (ssx(str, ">|<") == 1)
	{
		cwd = ft_strjoin(cwd, " ");
		str = ft_strjoin(cwd, str);
		handle_redirect(str);
	}
	else
	{
		ft_putstr(cwd);
		ft_putstr("\n");
		free(parsed_cwd);
		free(buff);
	}
}
