#include "raycasting_bonus.h"

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
	free(data->sprite);
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

// void	init_images_sprites(t_data *data)
// {
// 	int		width;
// 	int		heigh;
// 	char	*texture[10];
// 	int		i;

// 	i = 0;
// 	texture[0] = "textures/sprites/wizard_idle_1.xpm";
// 	texture[1] = "textures/sprites/wizard_idle_2.xpm";
// 	texture[2] = "textures/sprites/wizard_idle_3.xpm";
// 	texture[3] = "textures/sprites/wizard_idle_4.xpm";
// 	texture[4] = "textures/sprites/wizard_idle_5.xpm";
// 	texture[5] = "textures/sprites/wizard_idle_6.xpm";
// 	texture[6] = "textures/sprites/wizard_idle_7.xpm";
// 	texture[7] = "textures/sprites/wizard_idle_8.xpm";
// 	texture[8] = "textures/sprites/wizard_idle_9.xpm";
// 	texture[9] = "textures/sprites/wizard_idle_10.xpm";
// 	while (i < 10)
// 	{
// 		data->wall_texture_t[i].img = mlx_xpm_file_to_image(cub3d->mlx, textures[i],
// 			&cub3d->wall_texture_t[i].width, &cub3d->wall_texture_t[i].height);
// 		if (!data->img->imag)
// 			ft_error(1);
// 		cub3d->wall_texture_t[i].addr = mlx_get_data_addr(cub3d->wall_texture_t[i].img,
// 				&cub3d->wall_texture_t[i].bits_per_pixel, &cub3d->wall_texture_t[i].line_length,
// 				&cub3d->wall_texture_t[i].endian);
// 		if (!cub3d->wall_texture_t[i].addr)
// 			ft_error(1);
// 		i++;
// 	}
// }

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
	data->sprite = (t_sprite *)malloc(sizeof(t_sprite));
	data->sprite->pos_m_x = 0;
	data->sprite->pos_m_y = 0;
	data->sprite->distance = 0;
	data->sprite->angle = 0;
}

void init_variables(t_data *data)
{
	data->last_mouse_x = -1;
	data->last_mouse_y = -1;
	data->fov_angle = 60 * (M_PI / 180);
	data->size = 32;
	data->mini_map = 0.25;
	if (data->size < 1 || data->mini_map <= 0)
		ft_error(2);
	data->width_wall = 1;
	data->map->pos_m_x = -1;
	data->map->pos_m_y = -1;
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
	// init_images_sprites(data);
}

void	init_data(t_data *data)
{
	init_variables(data);
	data->height_win =  data->map->height * data->size;
	data->width_win = data->map->width * data->size;
	data->height_mini =  data->height_win * data->mini_map;
	data->width_mini = data->width_win * data->mini_map;
	data->distanceProjPlane = (data->width_win / 2) / tan(data->fov_angle / 2);
	data->num_rays = data->width_win > data->height_win ? data->width_win : data->height_win;
	data->ray = (t_ray *)malloc(sizeof(t_ray) * data->num_rays);
	data->image = (t_img *)malloc(sizeof(t_img));
	if (!data->ray || !data->image)
		ft_error(0);
	init_mlx_data(data);
	init_data_player(data);
}