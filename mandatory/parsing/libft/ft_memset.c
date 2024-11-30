/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:11:13 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/11 06:51:32 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)str)[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*p;
	char	*d;

	p = (char *)dest;
	d = (char *)src;
	i = 0;
	if (d == NULL && p == NULL)
		return (NULL);
	if (dest == src)
		return ((void *)src);
	while (i < n)
	{
		p[i] = d[i];
		i++;
	}
	return (p);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (size && nmemb >= SIZE_MAX / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem != NULL)
		ft_bzero(mem, nmemb * size);
	return (mem);
}
