/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/11/24 00:41:28 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_map(t_data *data)
{
	data->elements = 0;
	data->erros = 0;
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		ft_putstr_fd("Memory allocation failed\n", 2);
	data->texture = ft_calloc(1, sizeof(t_texture_data));
	if (!data->texture)
		ft_putstr_fd("Memory allocation failed\n", 2);
	data->fd = 0;
	data->texture->north = ft_calloc(1, sizeof(char *));
	data->texture->south = ft_calloc(1, sizeof(char *));
	data->texture->west = ft_calloc(1, sizeof(char *));
	data->texture->east = ft_calloc(1, sizeof(char *));
	data->floor = ft_calloc(1, sizeof(char *));
	data->ceiling = ft_calloc(1, sizeof(char *));
}

// void	print_data(t_data *data)
// {
// 	int	s;

// 	printf("======================================\n");
// 	if (data == NULL)
// 	{
// 		printf("data data is NULL\n");
// 		return ;
// 	}
// 	// File information
// 	printf("File Name: %s\n", data->file_name ? data->file_name : "NULL");
// 	printf("File Descriptor: %d\n", data->fd);
// 	// Texture information
// 	printf("----------- Textures ------------ \n");
// 	if (data->texture)
// 	{
// 		printf("  North: %s\n",
// 			data->texture->north ? data->texture->north : "NULL");
// 		printf("  South: %s\n",
// 			data->texture->south ? data->texture->south : "NULL");
// 		printf("  West: %s\n",
// 			data->texture->west ? data->texture->west : "NULL");
// 		printf("  East: %s\n",
// 			data->texture->east ? data->texture->east : "NULL");
// 	}
// 	else
// 		printf("  Textures: NULL\n");
// 	// Color information
// 	printf("----------- Colors ---------- :\n");
// 	if (data->floor)
// 		printf("  Floor: R=%d, G=%d, B=%d\n", data->floor->red,
// 			data->floor->green, data->floor->blue);
// 	else
// 		printf("  Floor: NULL\n");
// 	if (data->ceiling)
// 		printf("  Ceiling: R=%d, G=%d, B=%d\n", data->ceiling->red,
// 			data->ceiling->green, data->ceiling->blue);
// 	else
// 		printf("  Ceiling: NULL\n");
// 	// Player information
// 	// printf("-------------- Player --------------\n");
// 	// if (data->player)
// 	// {
// 	// 	printf("  Position: (Row : %d, col : %d)\n", data->player->pos_y,
// 	// 		data->player->pos_x);
// 	// 	printf("  Direction: %c\n", data->player->direction);
// 	// 	printf("  Count: %d\n", data->player->count_player);
// 	// }
// 	// else
// 	// 	printf("  Player: NULL\n");
// 	// map information
// 	printf("----------- Map -----------:\n");
// 	printf("  Elements Count: %d\n", data->elements);
// 	if (data->map)
// 	{
// 		for (int i = 0; data->map->map[i]; i++)
// 			printf(" Row %d: %s\n", i, data->map->map[i]);
// 	}
// 	else
// 		printf("  Map: NULL\n");
// 	printf("\n================== raycasting_data ================\n");
// 	s = 0;
// 	while (data->map->map[s])
// 	{
// 		printf("%s\n", data->map->map[s]);
// 		s++;
// 	}
// 	printf("=================== end map =========================\n");
// 	printf("height = %d\n", data->map->height);
// 	printf("width = %d\n", data->map->width);
// 	printf("=====================================================\n");
// } 

void free_tols(t_data *data)
{
    if (data->file_name) 
	{
        free(data->file_name);
        data->file_name = NULL;
    }
    if (data->map_org)
	{
        ft_free_array(data->map_org);
        data->map_org = NULL;
    }
	if (data->txture)
	{
		ft_free_array(data->txture);
		data->txture = NULL;
	}
}

void	parsing(int ac, char **av, t_data *data)
{
	init_map(data);
	validate_config(ac, av, data);
	free_tols(data);
	// print_data(data);
}