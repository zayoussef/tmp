#include "raycasting.h"

void	destroy_images(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx, data->wall_texture[i].img);
		i++;
	}
}

void	free_data(t_data *data)
{
	ft_free_array(data->map->map);
	free(data->player);
	free(data->map);
	free(data->ray);
	if (data->image->img)
		mlx_destroy_image(data->mlx, data->image->img);
	destroy_images(data);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->texture);
	free(data->image);
	free(data);
	exit (0);
}

void	init_images_wall_texture(t_data *data)
{
	char	*texture[4];
	int		i;

	i = 0;
	texture[0] = data->texture->east;
	texture[1] = data->texture->north;
	texture[2] = data->texture->west;
	texture[3] = data->texture->south;
	while (i < 4)
	{
		data->wall_texture[i].img = mlx_xpm_file_to_image(data->mlx, texture[i],
			&data->wall_texture[i].width, &data->wall_texture[i].height);
		if (!data->wall_texture[i].img)
			ft_error(1);
		data->wall_texture[i].img_data = mlx_get_data_addr(data->wall_texture[i].img,
				&data->wall_texture[i].bpp, &data->wall_texture[i].size_line, &data->wall_texture[i].endian);
		if (!data->wall_texture[i].img_data)
			ft_error(1);
		i++;
	}
	free(data->texture->east);
	free(data->texture->north);
	free(data->texture->south);
	free(data->texture->west);
}

void	init_data_player(t_data *data)
{
	data->player->pos_x *= data->size;
	data->player->pos_y *= data->size;
	data->player->move_speed = 2.5;
	data->player->turn_Direction = 0;
	data->player->walk_Direction = 0;
	data->player->radius = 6;
	if (data->player->direction == 'S')
		data->player->rotation_angle = M_PI_2;
	else if (data->player->direction == 'N')
		data->player->rotation_angle = 3 * M_PI_2;
	else if (data->player->direction == 'E')
		data->player->rotation_angle = 2 * M_PI;
	else if (data->player->direction == 'W')
		data->player->rotation_angle = M_PI;
	data->player->rotation_speed = 2 * (M_PI / 180);
}

void init_variables(t_data *data)
{
	data->fov_angle = 66 * (M_PI / 180);
	data->size = 32;
	if (data->size < 1)
		ft_error(2);
	data->width_wall = 1;
	data->color_floor = get_value_color(data->floor);
	data->color_sky = get_value_color(data->ceiling);
	free(data->floor);
	free(data->ceiling);
}

void	init_mlx_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error(1);
	data->mlx_win = mlx_new_window(data->mlx, data->width_win, data->height_win, "cub3d");
	if (!data->mlx_win)
		ft_error(1);
	data->image->img = mlx_new_image(data->mlx, data->width_win, data->height_win);
	if (!data->image->img)
		ft_error(1);
	data->image->img_data = mlx_get_data_addr(data->image->img, &data->image->bpp, &data->image->size_line, &data->image->endian);
	if (!data->image->img_data)
		ft_error(1);
	init_images_wall_texture(data);
}

void	init_data(t_data *data)
{
	init_variables(data);
	data->height_win =  data->map->height * data->size;
	data->width_win = data->map->width * data->size;
	data->distanceProjPlane = (data->width_win / 2) / tan(data->fov_angle / 2);
	data->num_rays = data->width_win > data->height_win ? data->width_win : data->height_win;
	data->ray = (t_ray *)malloc(sizeof(t_ray) * data->num_rays);
	data->image = (t_img *)malloc(sizeof(t_img));
	if (!data->ray || !data->image)
		ft_error(0);
	init_mlx_data(data);
	init_data_player(data);
}