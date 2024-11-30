/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/10/05 23:53:27 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	check_color(char **comp, t_color_data *color_data)
{
	color_data->red = ft_atoi(comp[0]);
	color_data->green = ft_atoi(comp[1]);
	color_data->blue = ft_atoi(comp[2]);
	if (color_data->red < 0 || color_data->red > 255 || color_data->green < 0
		|| color_data->green > 255 || color_data->blue < 0
		|| color_data->blue > 255)
	{
		ft_putstr_fd("Error: Invalid color\n", 2);
		exit(1);
	}
	free(comp[0]);
	free(comp[1]);
	free(comp[2]);
	free(comp);
}

int	check_map_shape(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'Z')
			{
				// Check right and down
				if ((map[y][x + 1] && is_invalid(x + 1, y, map)) || (map[y + 1]
						&& is_invalid(x, y + 1, map)))
					return (ft_free_array(map), 1);
				// Check left and up
				else if ((x != 0 && is_invalid(x - 1, y, map)) || (y != 0
						&& is_invalid(x, y - 1, map)))
					return (ft_free_array(map), 1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

char	*make_wide_row(char *old_row, int new_width)
{
	char	*new_row;
	int		i;

	i = 0;
	new_row = malloc(sizeof(char) * (new_width + 1));
	if (!new_row)
		return (NULL);
	while (old_row[i] && i < new_width)
	{
		new_row[i] = old_row[i];
		i++;
	}
	while (i < new_width)
		new_row[i++] = ' ';
	new_row[new_width] = '\0';
	return (new_row);
}

char	**make_square_map(t_data *data, int rows, int cols)
{
	char	**big_map;
	int		i;

	i = 0;
	big_map = malloc(sizeof(char *) * (rows + 1));
	if (!big_map)
		return (NULL);
	while (i < rows)
	{
		big_map[i] = make_wide_row(data->map_org[i], cols);
		if (!big_map[i])
		{
			clean_up_map(big_map, i);
			return (NULL);
		}
		i++;
	}
	big_map[rows] = NULL;
	return (big_map);
}

int	validate_map(t_data *data)
{
	char	**map_dup;
	int		height;
	int		width;

	map_dup = NULL;
	height = count_strings(data->map_org);
	width = max_length(data->map_org);
	map_dup = duplicate_map(data, height, width);
	if (check_map_shape(map_dup))
		return (1);
	ft_free_array(map_dup);
	data->map = ft_calloc(1, sizeof(t_map));
	data->map->height = height;
	data->map->width = width;
	data->map->map = make_square_map(data, height, width);
	return (0);
}
