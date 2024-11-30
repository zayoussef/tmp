/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/09/29 17:12:48 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_l(char *s1, char *s2)
{
	char	*str;
	size_t	tlen;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	tlen = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(tlen + 1);
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[tlen] = '\0';
	free(s1);
	return (str);
}
