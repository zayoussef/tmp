/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/10/05 19:51:13 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clean_up_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}

int	max_length(char **map)
{
	int	max;
	int	i;
	int	length;

	max = 0;
	i = 0;
	while (map[i])
	{
		length = ft_strlen(map[i]);
		if (max < length)
			max = length;
		i++;
	}
	return (max);
}

int	is_invalid(int x, int y, char **map)
{
	if (map[y][x] != 'Z' && map[y][x] != '1')
		return (1);
	return (0);
}
