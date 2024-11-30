/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/10/05 23:54:13 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_color_data	*parse_color(char *color)
{
	char			**comp;
	t_color_data	*color_data;

	color_data = ft_calloc(1, sizeof(t_color_data));
	if (!color_data)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}
	if (count(color, ',') != 2)
	{
		ft_putstr_fd("Error: Invalid color format\n", 2);
		exit(1);
	}
	comp = ft_split(color, ',');
	if (!comp || count_strings(comp) != 3)
	{
		ft_putstr_fd("Error: Invalid color format\n", 2);
		exit(1);
	}
	check_color(comp, color_data);
	return (color_data);
}

void	store_color(char *line, t_data *map)
{
	char	type;
	char	*color;

	color = validate_color_string(line, &type);
	if (count(color, ',') != 2)
	{
		ft_putstr_fd("Error: Invalid color format \n", 2);
		exit(1);
	}
	if (type == 'F')
		map->floor = parse_color(color);
	else if (type == 'C')
		map->ceiling = parse_color(color);
	map->elements++;
}

void	store_texture(char *line, t_data *map)
{
	char	*type;
	char	*path;

	type = line;
	while (*line == ' ' || *line == '\t')
		line++;
	line += 2;
	path = extract_path(line);
	// check_path(path)
	// check if file is empty, if line[0] == '\0'
	store_texture_path(type, path, map);
	map->elements++;
}

int	check_identifier(char *line, char *tmp)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(line + i, tmp, ft_strlen(tmp)))
	{
		i += ft_strlen(tmp);
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i])
			return (1);
		else
		{
			ft_putstr_fd("Error: Wrong entries\n", 2);
			exit(1);
		}
	}
	return (0);
}

void	check_texture(char *line, t_data *map)
{
	if (check_identifier(line, "NO "))
		store_texture((line), map);
	else if (check_identifier(line, "SO "))
		store_texture((line), map);
	else if (check_identifier(line, "WE "))
		store_texture((line), map);
	else if (check_identifier(line, "EA "))
		store_texture((line), map);
	else if (check_identifier(line, "F "))
		store_color((line), map);
	else if (check_identifier(line, "C "))
		store_color((line), map);
	else
		map->erros += 1;
}
