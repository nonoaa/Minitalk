/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byahn <byahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:31:32 by byahn             #+#    #+#             */
/*   Updated: 2021/08/01 17:50:14 by byahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	out;
	int		neg;

	i = 0;
	neg = 1;
	out = 0;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		out = out * 10 + (str[i] - '0');
		i++;
	}
	return (out * neg);
}

void	send_char(int pid, unsigned char c)
{
	unsigned char	counter;

	counter = 128;
	while (counter)
	{
		if (c & counter)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				write(1, "PID error.\n", 11);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				write(1, "PID error.\n", 11);
				exit(1);
			}
		}
		counter >>= 1;
		usleep(50);
	}
}

void	send_pid(int pid, int num)
{
	char	*numstr;
	int		i;

	numstr = ft_itoa(num);
	i = 0;
	while (numstr[i])
	{
		send_char(pid, numstr[i]);
		i++;
	}
	free(numstr);
}

void	success(int sig)
{
	(void)sig;
	write(1, "Server received message successfully.\n", 38);
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*msg;

	if (argc != 3)
	{
		write(1, "Parameter error.\n", 16);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	signal(SIGUSR1, success);
	while (*msg)
	{
		send_char(pid, *msg);
		msg++;
	}
	send_char(pid, '\0');
	send_pid(pid, getpid());
	send_char(pid, '\0');
	return (0);
}
