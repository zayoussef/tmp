/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:11:13 by yozainan          #+#    #+#             */
/*   Updated: 2024/09/29 22:18:34 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_digit(long n)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		count++;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		i;
	char	*str;

	nbr = n;
	i = ft_len_digit(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nbr == 0)
		str[0] = 48;
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		str[i--] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (str);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sg;
	int	rs;

	i = 0;
	sg = 1;
	rs = 0;
	while (str[i] && str[i] <= 32)
		i++;
	if (str[i] == '-')
	{
		sg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rs = rs * 10 + (str[i] - 48);
		i++;
	}
	return (rs * sg);
}
