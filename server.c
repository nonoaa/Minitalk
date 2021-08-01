/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byahn <byahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:32:25 by byahn             #+#    #+#             */
/*   Updated: 2021/08/01 17:32:26 by byahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	write_msg(char *msg, int *end, int *pid)
{
	if (*end)
	{
		if (*msg == 0)
		{
			kill(*pid, SIGUSR1);
			*end = 0;
			*pid = 0;
		}
		else
			*pid = *pid * 10 + *msg - '0';
		*msg = 0;
	}
	else
	{
		write(1, msg, 1);
		if (*msg == 0)
		{
			write(1, "\n", 1);
			*end = 1;
		}
		*msg = 0;
	}
}

void	handler(int signo, siginfo_t *info, void *context)
{
	static char	msg;
	static int	counter;
	static int	end;
	static int	pid;

	(void)info;
	(void)context;
	if (--counter == -1)
		counter = 7;
	if (signo == SIGUSR1)
		msg |= (1 << counter);
	else if (signo == SIGUSR2)
		msg &= ~(1 << counter);
	if (counter == 0)
		write_msg(&msg, &end, &pid);
}

int	main(void)
{
	struct sigaction	sigact;

	sigact.sa_sigaction = handler;
	sigact.sa_flags = SA_SIGINFO;
	write(1, "pid:", 4);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	if (sigaction(SIGUSR1, &sigact, NULL) != 0)
	{
		write(1, "Sigaction error.", 16);
		exit(1);
	}
	if (sigaction(SIGUSR2, &sigact, NULL) != 0)
	{
		write(1, "Sigaction error.", 16);
		exit(1);
	}
	while (1)
		;
	return (0);
}
