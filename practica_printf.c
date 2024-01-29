/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practica_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:34:45 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/29 14:00:25 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

void ft_putchar(char c,int *counter)
{
	write(1, &c, 1);
	(*counter)++;
}

void ft_putstr(char *str, int *counter)
{
	if (!str)
	{
		ft_putstr("(null)", counter);
		return ;
	}
	while(*str)
	{
		ft_putchar(*str, counter);
		str++;
	}
}

void ft_putnbr(int nbr, int *counter)
{
	if (nbr == -2147483648)
	{
		ft_putstr("-2147483648", counter);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar('-', counter);
		nbr = nbr * -1;
	}
	if (nbr < 10)
	{
		ft_putchar(nbr + '0', counter);
		return ;
	}
	else
	{
		ft_putnbr(nbr / 10, counter);
		ft_putnbr(nbr % 10, counter);
	}
}

void ft_nbase(unsigned long nbr, unsigned int base, int *counter, char *strbase)
{
	if (nbr < base)
	{
		ft_putchar(strbase[nbr], counter);
		return ;
	}
	else
	{
		ft_nbase(nbr / base, base, counter, strbase);
		ft_nbase(nbr % base, base, counter, strbase);
	}
}

int ft_printf(const char *str, ...)
{
	va_list arg;
	int counter = 0;
	va_start(arg, str);
	while(*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == 's')
				ft_putstr(va_arg(arg, char *), &counter);
			else if (*str == 'd')
				ft_putnbr(va_arg(arg, int), &counter);
			else if (*str == 'x')
				ft_nbase(va_arg(arg, unsigned int), 16, &counter, "0123456789abcdef");
		}
		else
			ft_putchar(*str, &counter);
		str++;
	}
	va_end(arg);
	return(counter);
}

#include <stdio.h>
int main(void)
{
	char *str_n = NULL;
	int i =	ft_printf("FT ===\n String: %s\nDigit: %d\nHexa: %x\nNull String%s\n", "TEST", 12345, 12345, str_n);
	int x =	ft_printf("RL ===\n String: %s\nDigit: %d\nHexa: %x\nNull String%s\n", "TEST", 12345, 12345, str_n);
	printf("own counter: %d, real counter: %d", i, x);
}
