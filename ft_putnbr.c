#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	int	tmp;

	if (n < 0)
	{
		ft_putchar('-');
		tmp = n % 10;
		tmp = -tmp;
		if (n <= -10)
		{
			n /= 10;
			n = -n;
			ft_putnbr(n);
		}
		ft_putchar(tmp + '0');
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else if (n < 10)
		ft_putchar(n + '0');
}
