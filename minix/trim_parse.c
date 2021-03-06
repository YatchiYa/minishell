#include "minishell.h"

char			*trim_quote(char *str, int *ret, int *xet)
{
	int		i;
	char	*dest;

    i = -1;
    dest = malloc_sortie(ft_strlenx(str));
    while (str[++i])
        dest[i] = str[i];
    dest[i] = '\0';
    i = -1;
	*ret = 0;
	*xet = 0;
    while (dest[++i])
	{
		if (dest[i] == '\"' && *xet == 0)
			*ret++;
		else if (dest[i] == '\'' && *ret == 0)
			*xet++;
	}
	return (dest);
}