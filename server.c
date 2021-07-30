#include "minitalk.h"
#include <stdio.h>

void handler(int signo, siginfo_t *info, void *context)
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
	{
		if (end)
		{
			if (msg == 0)
			{
				kill(pid, SIGUSR1);
				end = 0;
				pid = 0;
			}
			else
				pid = pid * 10 + msg - '0';
			msg = 0;
		}
		else
		{
			write(1, &msg, 1);
			if (msg == 0)
			{
				write(1, "\n", 1);
				end = 1;
			}
			msg = 0;
		}
	}
}

int main(void)
{
	int			pid;
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
	while(1)
		pause();
	return (0);
}
