/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:44:32 by tkeil             #+#    #+#             */
/*   Updated: 2024/10/31 18:07:19 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_atoi(char *s)
{
	size_t	i;
	int		p;
	int		z;

	i = 0;
	p = 1;
	z = 0;
	while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			p = -p;
		i++;
	}
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		z = z * 10 + (s[i] - '0');
		i++;
	}
	return (z * p);
}

size_t	ft_len(int z)
{
	size_t	i;

	i = 0;
	if (z == 0)
		return (1);
	if (z < 0)
	{
		i++;
		z = -z;
	}
	while (z)
	{
		i++;
		z /= 10;
	}
	return (i);
}

char	*ft_itoa(int z)
{
	size_t	len;
	char	*s;
	int		k;

	k = 0;
	len = ft_len(z);
	s = (char *) malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (z < 0)
	{
		s[0] = '-';
		z = -z;
		k = 1;
	}
	s[len] = '\0';
	while (len - k > 0)
	{
		s[len - 1] = z % 10 + '0';
		z /= 10;
		len--;
	}
	return (s);
}

int	ft_isprime(int z)
{
	int	i;

	if (z < 2)
		return (0);
	i = z - 1;
	while (i > 1)
	{
		if (z % i == 0)
			return (0);
		i--;
	}
	return (1);
}

int	ft_nextprime(int z)
{
	if (z < 2)
		return (2);
	if (ft_isprime(z))
		return (z);
	else
		return (ft_nextprime(++z));
}

void	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
}

int	ft_getprime(int z, int prime)
{
	int	pr;

	pr = prime;
	if (z % pr == 0)
		return (pr);
	while (1)
	{
		pr = ft_nextprime(++pr);
		if (z % pr == 0)
			return (pr);
	}
}

int	main(int argc, char **argv)
{
	int		z;
	char	*s;
	int		prime;

	if (argc != 2)
		return (write(1, "\n", 1), 1);
	z = ft_atoi(argv[1]);
	if (ft_isprime(z))
		return (s = ft_itoa(z), ft_putstr(s), write(1, "\n", 1), free(s), 0);
	prime = 2;
	while (z > 1)
	{
		prime = ft_getprime(z, prime);
		s = ft_itoa(prime);
		if (!s)
			return (1);
		ft_putstr(s);
		z /= prime;
		if (z > 1)
			write(1, "*", 1);
	}
	return (free(s), write(1, "\n", 1), 0);
}
