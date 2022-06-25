/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _                                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: ____/__/__ __:__:__ by nuo               #+#    #+#             */
/*   Updated: ____/__/__ __:__:__ by nuo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		res;
	int		i;
	va_list	ap;

	va_start(ap, s);
	res = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] ^ 37)
		{
			res += 1;
			write(1, & s[i], 1);
		}
		else
			res += fmt(ap, s[++i]);
	}
	return (res);
}

int	len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	fmt(va_list ap, const char c)
{
	int	size;

	if (c == 'c')
		size = route_chr(va_arg(ap, int));
	if (c == 's')
		size = route_str(va_arg(ap, char *));
	if (c == 'p')
		size = route_ptr(va_arg(ap, uintptr_t));
	if (c == 'd' || c == 'i')
		size = route_dec(va_arg(ap, int));
	if (c == 'u')
		size = route_uin(va_arg(ap, unsigned int));
	if (c == 'x')
		size = route_hex(va_arg(ap, unsigned int), "0123456789abcdef");
	if (c == 'X')
		size = route_hex(va_arg(ap, unsigned int), "0123456789ABCDEF");
	if (c == '%')
		size = write(1, & c, 1);
	return (size);
}

/*

int	route_ptr(uintptr_t num)
{
	write(1, "0x", 2);
	if (!num)
		write(1, "0", 1);
	else
		print_ptr(num);
	return (count_ptr(num));
}

void	print_ptr(uintptr_t num)
{
	char	*baseline;

	baseline = "0123456789abcdef";
	if (num >= 16)
		print_ptr(num / 16);
	write(1, & baseline[num % 16], 1);
}

int	count_ptr(uintptr_t x)
{
	int	i;

	i = 3;
	if (!x)
		return (i);
	while (x >= 16)
	{
		x /= 16;
		i++;
	}
	return (i);
}

int	route_chr(int c)
{
	return (write(1, & c, 1));
}

void	print_hex(unsigned int num, char *baseline)
{
	if (num >= 16)
		print_hex(num / 16, baseline);
	write(1, &baseline[num % 16], 1);
}

int	count_hex(unsigned int x)
{
	int	i;

	i = 1;
	while (x >= 16)
	{
		x /= 16;
		i++;
	}
	return (i);
}

int	route_hex(unsigned int num, char *baseline)
{
	print_hex(num, baseline);
	return (count_hex(num));
}

char	*itoa(int num)
{
	char	*res;
	int		size;

	if (num == -2147483648)
		return (stos("-2147483648"));
	if (!num)
		return (stos("0"));
	size = count_dec(num);
	res = malloc(size + 1);
	if (num < 0)
	{
		num *= -1;
		res[0] = '-';
	}
	res[size--] = 0;
	while (num)
	{
		res[size--] = num % 10 + '0';
		num /= 10;
	}
	return (res);
}

char	*stos(char *s)
{
	char	*p;
	char	*d;
	int		size;

	size = len(s);
	d = malloc(size + 1);
	p = d;
	while (*s)
		*d++ = *s++;
	*d = 0;
	return (p);
}

int	count_dec(int num)
{
	int	i;

	i = 1;
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num >= 10)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int	route_dec(int n)
{
	char	*num;
	int		size;

	num = itoa(n);
	size = route_str(num);
	free(num);
	return (size);
}

int	route_uin(unsigned int n)
{
	char	*num;
	int		size;

	num = uitoa(n);
	size = route_str(num);
	free(num);
	return (size);
}

int	count_uin(unsigned int num)
{
	int	i;

	i = 1;
	while (num >= 10)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*uitoa(unsigned int num)
{
	char	*res;
	int		size;

	if (!num)
		return (stos("0"));
	size = count_uin(num);
	res = malloc(size + 1);
	res[size--] = 0;
	while (num)
	{
		res[size--] = num % 10 + '0';
		num /= 10;
	}
	return (res);
}

int	route_str(char *s)
{
	int	i;

	i = 6;
	if (!s)
	{
		write(1, "(null)", i);
		return (i);
	}
	i = -1;
	while (s[++i])
		write(1, & s[i], 1);
	return (i);
}

*/

/*

//DRIVE
#include "stdio.h"
#define ss printf("--\n");
int	main()
{
	int n1 = ft_printf(" %s ", "hello, world!");
	printf("\n%i\n", n1);
	ss;
	int n2 = ft_printf(" %d ", -2147483648);
	printf("\n%i\n", n2);
	ss;
	int nd = ft_printf(" %d ", -42);
	printf("\n%i\n", nd);
	ss;
	int n3 = ft_printf(" %x ", 42);
	printf("\n%i\n", n3);
	ss;
	int n4 = ft_printf(" %p ", 0);
	printf("\n%i\n", n4);
	ss;
	int n5 = ft_printf(" %p ", 123);
	printf("\n%i\n", n5);
}
*/
