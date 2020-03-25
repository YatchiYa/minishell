#include "minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		display_prompt_msg();
		signal(SIGINT, signal_handler);
	}
}

void	signal_handler2(int signo)
{
	printf(" debug signal [%d]\n", signo);
}
