/* ************************************************************************** */
/*                                                                            */
/*                                                        ...      :::::::    */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    ... ...         :::     */
/*   By: nuo <marvin@42.fr>                         ...  ...       :::        */
/*                                                ...........   :::           */
/*   Created: ____/__/__ __:__:__ by nuo               ...    :::             */
/*   Updated: 2022/06/22 15:44:54 by nuxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*	
 *	g_flag
 *
 * 	[ _&_  ___  ___ ] is a boolean result flag on successful transmission
 *	
 *	[ ___  _&_  ___ ] is an iterator through 8 bits of a char
 *	
 *	[ ___  ___  _&_ ] stores the client PID received by server via siginfo
 *
*/

int	g_flag[3];

void	setter(struct sigaction *sa, siginfo_t *sinfo, int pid_client);
void	handler(int signum, siginfo_t *sig, void *ucontext);
void	prompt(int e);

/*
 * 3 steps:
 *
 * 	1. init the sigaction struct :
 * 	
 * 		sa_flags	: flags are optional, which can be set to NULL
 * 		sa_mask		: add the signals we want to block in a sigset
 * 		handler		: to handle each signal
 *
 * 	2. sigaddset() 
 * 		- add the signals we want to handle
 *
 * 	3. sigaction()
 * 		- define a system call, ie. what to do upon receiving a signal
 *
 *	4. SA_SIGINFO
 *		- set siginfo in order to know sender's id
 *
 * 	5. receive AMD handle signals ( SIGUSR1 / SIGUSR2 )
 * 		- into an infinite loop
 * 		- handle signals
 * 			- decipher and print out the secret
 * 		- once finished handling -> set flag to TRUE
 * 		- once the flag is TRUE -> send feedback to client, set flag to FALSE
 * 		- once feedback received -> client sends next char in 8bit num
 * 		- cycle resumes
*/

int	main(void)
{
	struct sigaction	sa;
	siginfo_t			siginfo;
	int					pid_server;
	int					pid_client;

	setter(&sa, &siginfo, pid_client);
	pid_server = getpid();
	g_flag[1] = FALSE;
	ft_printf("Server PID: %d \nListening... \n", pid_server);
	while (TRUE)
	{
		while (!g_flag[0])
			if (g_flag[0])
				break ;
		pid_client = g_flag[2];
		g_flag[0] = !g_flag[0];
		kill(pid_client, SIGUSR1);
	}
}

void	setter(struct sigaction *sa, siginfo_t *sinfo, int pid_client)
{
	sa->sa_sigaction = handler;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
	if (errno)
	{
		prompt(errno);
	}
}

void	handler(int sigtype, siginfo_t *sinfo, void *ucontext)
{
	static unsigned char	c;
	int						max;
	int						pid_client;

	if (sigtype == SIGUSR1)
	{
		c |= (1 << g_flag[1]);
	}
	max = 8;
	++(g_flag[1]);
	if (g_flag[1] == max)
	{
		g_flag[1] -= max;
		ft_putchar(c);
		c = '\0';
	}
	pid_client = sinfo->si_pid;
	g_flag[2] = pid_client;
	g_flag[0] = TRUE;
	(void) ucontext;
}

void	prompt(int err)
{
	ft_printf("error: %d \n", err);
	exit(0);
}
