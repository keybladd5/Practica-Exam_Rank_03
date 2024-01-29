/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:49:07 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/29 13:26:06 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

void ft_putchar(char c, int *counter)
{
	write(1, &c, 1);
	(*counter)++;
}

void ft_putstr(char *str, int *counter)
{
	if (!str)
	{
		ft_putstr("(null)", counter);
		return;
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
		ft_putstr("-2147483648", counter);
	else if (nbr < 0)
	{
		ft_putchar('-', counter);
		ft_putnbr(-nbr, counter);
	}
	else if (nbr < 10)
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
		ft_putchar(strbase[nbr], counter);
	else
	{
		ft_nbase(nbr / base, base, counter, strbase);
		ft_nbase(nbr % base, base, counter, strbase);
	}
}

int ft_printf(const char *str, ...)
{
	va_list arg;
	int	counter = 0;
	int i = 0;
	va_start(arg, str);
	while(str[i])
	{
		if(str[i] == '%')
		{
			i++;
			if(str[i] == 's')
				ft_putstr(va_arg(arg, char *), &counter);
			else if (str[i] == 'x')
				ft_nbase(va_arg(arg, unsigned int), 16, &counter, "0123456789abcdef");
			else if (str[i] == 'd')
				ft_putnbr(va_arg(arg, int), &counter);
		}
		else
			ft_putchar(str[i], &counter);
		i++;
	}
	va_end(arg);
	return (counter);
}

/*#include<stdio.h>
int main(void)
{
	char *ptr = NULL;
	int i = ft_printf("test s: %s\ntest d: %d\ntest x %x\n", "hola que tal", 12783697, 555);
	int x = printf("test s: %s\ntest d: %d\ntest x %x\n", "hola que tal", 12783697, 555);
	printf("%s\\n", ptr );
	ft_printf("%s\\n", ptr);
	printf("mio:%d\noriginal: %d)\n", i, x);
}*/

