/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/11/24 00:45:09 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

char *read_map_content(char *line, t_data *data)
{
    char *content;
    char *temp;

    content = ft_calloc(1, sizeof(char));
    temp = ft_strjoin(content, line);
    free(content);
    content = temp;
    free(line);
    while (1)
    {
        line = get_next_line(data->fd);
        if (!line)
            break;
        temp = ft_strjoin(content, line);
        free(content);
        content = temp;
        free(line);
    }
    return (content);
}

int	valid_character(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strrch_finder("01NSEW 	", line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_player(char *line, t_data *data, int y)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (ft_strrch_finder("NSEW", line[x]))
		{
			if (data->player->count_player > 0)
			{
				ft_putstr_fd("Error: There is more player\n", 2);
				exit(1);
			}
			data->player->pos_x = x;
			data->player->pos_y = y;
			data->player->count_player++;
			data->player->direction = line[x];
		}
		x++;
	}
	return (0);
}

char	*create_border_line(int width)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char) * (width + 3));
	i = 0;
	while (i < width + 2)
	{
		new_line[i] = 'Z';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	**duplicate_map(t_data *data, int height, int width)
{
	char	**map_dup;
	int		i;
	int		j;

	map_dup = malloc(sizeof(char *) * (height + 3));
	map_dup[0] = create_border_line(width);
	i = 1;
	while (i < height + 1)
	{
		map_dup[i] = malloc(sizeof(char) * (width + 3));
		j = 0;
		while (j < width + 2)
		{
			if (j && j <= (int)ft_strlen(data->map_org[i - 1])
				&& ft_strchr("10NSWE", data->map_org[i - 1][j - 1]))
				map_dup[i][j] = data->map_org[i - 1][j - 1];
			else
				map_dup[i][j] = 'Z';
			j++;
		}
		map_dup[i][j] = '\0';
		i++;
	}
	map_dup[i] = create_border_line(width);
	return (map_dup[i + 1] = NULL, map_dup);
}
