/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/10/05 23:51:45 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	just_texture(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
	{
		if (line[i] == '\n')
			return (0);
		i++;
	}
	if (ft_strchr("NSWEFC", line[i]))
		return (0);
	return (1);
}

char	*extract_path(char *line)
{
	char	*path_start;
	char	*path_end;

	while (*line == ' ' || *line == '\t')
		line++;
	path_start = line;
	while (*line && *line != ' ' && *line != '\t' && *line != '\n')
		line++;
	if (*line != '\0' && *line != '\n')
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line != '\0' && *line != '\n')
		{
			ft_putstr_fd("Invalid texture format\n", 2);
			exit(1);
		}
	}
	path_end = line - 1;
	while (path_end > path_start && (*path_end == ' ' || *path_end == '\t'))
	{
		*path_end = '\0';
		path_end--;
	}
	return (ft_strdup(path_start));
}

void	store_texture_path(char *type, char *path, t_data *map)
{
	if (ft_strncmp(type, "NO", 2) == 0)
		map->texture->north = path;
	else if (ft_strncmp(type, "SO", 2) == 0)
		map->texture->south = path;
	else if (ft_strncmp(type, "WE", 2) == 0)
		map->texture->west = path;
	else if (ft_strncmp(type, "EA", 2) == 0)
		map->texture->east = path;
}

char	*validate_color_string(char *line, char *type)
{
	char	*color;

	while (*line == ' ' || *line == '\t')
		line++;
	*type = *line++;
	while (*line == ' ' || *line == '\t')
		line++;
	color = line;
	while (*line && *line != '\n')
	{
		if (!ft_isdigit(*line) && *line != ',' && *line != ' ' && *line != '\t')
		{
			ft_putstr_fd("Error: Invalid color\n", 2);
			exit(1);
		}
		line++;
	}
	while (line > color && (*(line - 1) == ' ' || *(line - 1) == '\t'))
		line--;
	*line = '\0';
	return (color);
}
