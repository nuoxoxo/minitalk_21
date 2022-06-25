/* ************************************************************************** */
/*                                                                            */
/*                                                        ...      :::::::    */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    ... ...         :::     */
/*   By: nuo <marvin@42.fr>                         ...  ...       :::        */
/*                                                ...........   :::           */
/*   Created: ____/__/__ __:__:__ by nuo               ...    :::             */
/*   Updated: 2022/06/22 16:27:41 by nuxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		setter(struct sigaction *a, siginfo_t *i, int pid);
void	sender(int pid, unsigned char c, int *byt);
void	handler(int sigtype);
void	prompt(int num);

int	g_flag = FALSE;

int	main(int c, char **v)
{
	struct sigaction	sa;
	siginfo_t			siginfo;
	int					i;
	int					byt;
	int					pid_server;

	if (c != 3)
	{
		prompt(0);
	}
	pid_server = ft_atoi(v[1]);
	if (pid_server <= 64 || !setter(&sa, &siginfo, pid_server))
	{
		prompt(1);
	}
	i = 0;
	byt = -8;
	while (v[2][i] != '\0')
		sender(pid_server, v[2][i++], &byt);
	sender(pid_server, v[2][i], &byt);
	ft_printf("Server received: %d bit, %d bytes\n", byt, byt / 8);
	ft_printf("Client pid: %d\n", getpid());
	return (0);
}

int	setter(struct sigaction *sa, siginfo_t *sinfo, int pid_server)
{
	sa->sa_handler = handler;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR1, sa, NULL);
	if (kill(pid_server, 0) && errno == 3)
	{
		return (FALSE);
	}
	return (TRUE);
}

void	handler(int sigtype)
{
	(void) sigtype;
	g_flag = TRUE;
}

void	sender(int pid_server, unsigned char c, int *byt)
{
	int	bpos;
	int	ret;

	bpos = -1;
	while (++bpos < 8)
	{
		if (c & (1 << bpos))
			ret = kill(pid_server, SIGUSR1);
		else
			ret = kill(pid_server, SIGUSR2);
		if (ret < 0)
		{
			if (errno)
			{
				ft_printf("error: %d \n", errno);
			}
			exit(0);
		}
		while (!g_flag)
			if (g_flag)
				break ;
		g_flag = !g_flag;
		++(*byt);
	}
}

void	prompt(int n)
{
	int	i;

	i = 42;
	if (!n)
	{
		write(1, "usage: ./client [server_pid] [message]   \n", i);
	}
	if (n == 1)
	{
		write(1, "invalid pid.                             \n", i);
	}
	exit (0);
}
