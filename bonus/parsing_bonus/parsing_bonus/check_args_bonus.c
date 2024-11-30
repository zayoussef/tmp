/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/11/23 18:12:03 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	check_args(int ac, char **av, t_data *data)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error : Invalid number of args\n", 2);
		ft_putstr_fd("\tUsage: ./cub3d <map.cub>\n", 2);
		exit(1);
	}
	else if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".cub", 4))
	{
		ft_putstr_fd("Error : Invalid file name\n", 2);
		exit(1);
	}
	data->fd = open(av[1], O_RDONLY | O_DIRECTORY);
	if (data->fd > 0)
	{
		ft_putstr_fd("Error : It's a directory\n", 2);
		close(data->fd);
		exit(1);
	}
	data->fd = open(av[1], O_RDONLY);
	if (data->fd < 0)
	{
		ft_putstr_fd("Error : File does not exist\n", 2);
		exit(1);
	}
	data->file_name = ft_strdup(av[1]);
}

void	check_empty_file(t_data *data)
{
	char	*line;
	int		non_empty_lines;
	char	*str;

	non_empty_lines = 0;
	line = get_next_line(data->fd);
	while (line != NULL)
	{
		str = line;
		while (*str == ' ' || *str == '\t')
			str++;
		if (*str != '\0' && *str != '\n')
		{
			non_empty_lines++;
			free(line);
			break ;
		}
		free(line);
	}
	close(data->fd);
	if (non_empty_lines == 0)
	{
		ft_putstr_fd("Error: File is empty or contains only whitespace\n", 2);
		exit(1);
	}
}
