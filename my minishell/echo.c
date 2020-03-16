#include "minishell.h"

char    *malloc_sortie(int len)
{
    char    *str;

    if (!(str = malloc(sizeof(char) * (len + 1))))
        return (NULL);
    return (str);
}

int		calc_c(char *str, char c)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c)
			ret++;
	}
	return (ret);
}

void	extend(char *str, char c)
{
	int		i;
	char	*line;

	i = 0;
	while (str[ft_strlenx(str) - 1] != c && calc_c(str, c) % 2 != 0)
	{
		line = NULL;
		ft_putstr("quote > ");
		get_next_line(0, &line);
		str = ft_strjoin(str, line);
	}
}

void    handle_echo(char *str)
{
    int		i;
    char	*dest;
    int		ret;
	int		xet;

    i = -1;
    dest = malloc_sortie(ft_strlenx(str));
    while (str[++i])
        dest[i] = str[i];
    dest[i] = '\0';
    i = -1;
	ret = 0;
	xet = 0;
    while (dest[++i])
	{
		if (dest[i] == '\"' && xet == 0)
			ret++;
		else if (dest[i] == '\'' && ret == 0)
			xet++;
	}
	printf("%d, %d", ret, xet);
	if (ret % 2 != 0 && ret != 0)
		extend(dest, '\"');
	else if (xet % 2 != 0 && xet != 0)
		extend(dest, '\'');
	else
	{
		i = 1;
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
				write(1, &str[i], 1);
			i++;
		}       
    	ft_putstr("\n");   
	}     
}