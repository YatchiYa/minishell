#include "minishell.h"

void		handle_pwd(char *str)
{
	char	*cwd;
	char	*buff;
	char	*parsed_cwd;

	if (!(buff = malloc(sizeof(char) * 4097)))
		return ;
	cwd = getcwd(buff, 4096);
	if (ssx(str, ">|<") == 1)
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
