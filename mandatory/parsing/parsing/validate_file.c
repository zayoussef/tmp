/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/11/24 00:42:10 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	copy_map(char *line, t_data *data)
{
	if (line)
	{
		data->tmp = read_map_content(line, data);
		data->map_org = ft_split(data->tmp, '\n');
		free(data->tmp);
	}
	else
	{
		ft_putstr_fd("Error: missing map\n", 2);
		close(data->fd);
		exit(1);
	}
}

void copy_info(t_data *data)
{
    char *line;
	char *temp;

    data->fd = open(data->file_name, O_RDONLY);
    data->tmp = ft_calloc(1, sizeof(char));
    while (1)
    {
        line = get_next_line(data->fd);
        if (!line || just_texture(line))
            break;
        if (!space_line(line))
        {
            temp = ft_strjoin(data->tmp, line);
            free(data->tmp);
            data->tmp = temp;
        }
        free(line);
    }
    data->txture = ft_split(data->tmp, '\n');
    free(data->tmp);
    copy_map(line, data);
}

void	check_save_texture(t_data *data)
{
	int	i;

	i = 0;
	while (data->txture[i])
	{
		check_texture(data->txture[i], data);
		i++;
	}
	if (data->erros != 0 || data->elements != 6)
	{
		ft_putstr_fd("Error: Wrong entries [check_save_texture]\n", 2);
		exit(1);
	}
}

void	parse_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map_org[i])
	{
		if (valid_character(data->map_org[i]))
		{
			ft_putstr_fd("Error: Invalid characters\n", 2);
			exit(1);
		}
		check_player(data->map_org[i], data, i);
		i++;
	}
	if (data->player->count_player != 1 || validate_map(data))
	{
		ft_putstr_fd("Error: Invalid map\n", 2);
		exit(1);
	}
	printf("-------------------- VALID MAP --------------------\n");
}

void	validate_config(int ac, char **av, t_data *data)
{
	check_args(ac, av, data);
	check_empty_file(data);
	copy_info(data);
	check_save_texture(data);
	if (data->elements == 6)
		parse_map(data);
	close(data->fd);
}
