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
		i++;
	}
	return (ret);
}

void	extend(char *str, char c)
{
	int		i;
	char	*line;
	int		back;

	i = 0;
	back = 0;
	while (str[ft_strlenx(str) - 1] != c && calc_c(str, c) % 2 != 0)
	{
		line = NULL;
		ft_putstr("quote > ");
		get_next_line(0, &line);
		str = ft_strjoin(str, "\n");
		str = ft_strjoin(str, line);
	}
	while (str[i])
	{
		i = 0;
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			back = 1;
			i += 2;
		}
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				if (str[i] == '$')
				{
					ft_putstr(parse_dollar(&str[i]));
					while (str[i] != ' ' && str[i] && str[i] != '\0')
						i++;
					i--;
				}
				else
					write(1, &str[i], 1);
			}
			i++;
		}
		if (back == 1)
			;
		else
    		ft_putstr("\n");   
	}       
    ft_putstr("\n");   
}

void    handle_echo(char *str)
{
    	int		i;
    	char	*dest;
    	int		ret;
	int		xet;
	int		back;

    	i = -1;
    	dest = malloc_sortie(ft_strlenx(str));
    	while (str[++i])
        	dest[i] = str[i];
    	dest[i] = '\0';
    	i = -1;
	ret = 0;
	xet = 0;
	back = 0;
    	while (dest[++i])
	{
		if (dest[i] == '"' && xet == 0)
			ret++;
		else if (dest[i] == '\'' && ret == 0)
			xet++;
	}
	if (ret % 2 != 0 && ret != 0)
		extend(dest, '\"');
	else if (xet % 2 != 0 && xet != 0)
		extend(dest, '\'');
	else if ((ssx(dest, ">|<") == 1) && (search_delim(dest, '"', ret) == 1))
		handle_redirect(dest);
	else
	{
		i = 0;
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			back = 1;
			i += 2;
		}
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				if (str[i] == '$')
				{
					ft_putstr(parse_dollar(&str[i]));
					while (str[i] != ' ' && str[i] && str[i] != '\0')
						i++;
					i--;
				}
				else
					write(1, &str[i], 1);
			}
			i++;
		}
		if (back == 1)
			;
		else
    		ft_putstr("\n");   
	}
}
