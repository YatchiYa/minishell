#include "minishell.h"

void		handle_pwd(void)
{
	char	*cwd;
	char	*buff;
	char	*parsed_cwd;

	if (!(buff = malloc(sizeof(char) * 4097)))
		return ;
	cwd = getcwd(buff, 4096);
	ft_putstr(cwd);
	ft_putstr("\n");
	free(parsed_cwd);
	free(buff);
}