#include "minishell.h"

char	*get_env_var(char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_envv[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(g_envv[i], tmp))
		{
			free(tmp);
			return (ft_strchr(g_envv[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}