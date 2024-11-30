/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/10/05 19:25:15 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	count_strings(char **comp)
{
	int	i;

	i = 0;
	while (comp[i])
		i++;
	return (i);
}

int	count(char *line, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == c)
			j++;
		i++;
	}
	return (j);
}

int	space_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '\n' || line[i] == '\0');
}

void	check_path(char *path)
{
	if (open(path, O_RDONLY) == -1 || ft_strncmp(path + (ft_strlen(path) - 4),
			".xpm", 4))
	{
		ft_putstr_fd("Error: Not valid path\n", 2);
		exit(1);
	}
}
