#include "raycasting_bonus.h"

void	clear_image(t_data *data, t_img *img)
{
    int	x;
	int	y;
	int	pixel;
	char	*dst;

	y = 0;
	pixel = 0;
	dst = NULL;
    while (y < data->height_win)
    {
		x = 0;
        while (x < data->width_win)
        {
            pixel = y * img->size_line + x * (img->bpp / 8);
            dst = img->img_data + pixel;
            *(unsigned int *)dst = 0xFFFFFFFF;
			x++;
        }
		y++;
    }
}

int	in_range(t_map *map, int x, int y)
{
	if (x < map->width && (x + 1) < map->width && (x - 1) < map->width
		&& y < map->height && (y + 1) < map->height && (y - 1) < map->height)
		return (1);
	return (0);
}

int	is_available(t_map *map, int x, int y)
{
	if (map->map[y][x] == '0' && map->map[y][x + 1] == '0' && map->map[y][x - 1] == '0'
		&& map->map[y + 1][x] == '0' && map->map[y + 1][x - 1] == '0' && map->map[y + 1][x + 1] == '0'
		&& map->map[y - 1][x] == '0' && map->map[y - 1][x - 1] == '0' && map->map[y - 1][x + 1] == '0')
		return (1);
	return (0);
}

void	choose_position(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (in_range(map, x, y))
			{
				if (is_available(map, x, y))
				{
					map->pos_m_x = x;
					map->pos_m_y = y;
					break ;
				}
			}
			x++;
		}
		y++;
	}
}

int	attitude(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	clear_image(data, data->image);
	cast_rays(data);
	draw_map_2d(data);
    draw_player(data);
	// animate_monster(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image->img, 0, 0);
	mlx_do_sync(data->mlx);
	return (0);
}

int	my_key_hook(int keycode, void *param)
{
	t_data	*data;
	float	movestep;
	float	new_position_x;
	float	new_position_y;

	data = (t_data *)param;
	new_position_x = 0;
	new_position_y = 0;
	if (keycode == ESC)
		free_data(data);
	else if (keycode == RIGHT || keycode == D)
	{
		data->player->turn_Direction = +1;
		data->player->rotation_angle += data->player->rotation_speed * data->player->turn_Direction;
	}
	else if (keycode == LEFT || keycode == A)
	{
		data->player->turn_Direction = -1;
		data->player->rotation_angle += data->player->rotation_speed * data->player->turn_Direction;
	}
	else if (keycode == UP || keycode == W)
	{
		data->player->walk_Direction = +1;
		movestep = data->player->walk_Direction * data->player->move_speed;
		new_position_x = data->player->pos_x + cos(data->player->rotation_angle) * movestep;
		new_position_y = data->player->pos_y + sin(data->player->rotation_angle) * movestep;
		if (!is_Wall(data, new_position_x, new_position_y))
		{
			data->player->pos_y = new_position_y;
			data->player->pos_x = new_position_x;
		}
	}
	else if (keycode == DOWN || keycode == S)
	{
		data->player->walk_Direction = -1;
		movestep = data->player->walk_Direction * data->player->move_speed;
		new_position_x = data->player->pos_x + cos(data->player->rotation_angle) * movestep;
		new_position_y = data->player->pos_y + sin(data->player->rotation_angle) * movestep;
		if (!is_Wall(data, new_position_x, new_position_y))
		{
			data->player->pos_y = new_position_y;
			data->player->pos_x = new_position_x;
		}
	}
	return (0);
}

void init_mouse_position(int x, int y, t_data *data)
{
	if (data->last_mouse_x == -1)
		data->last_mouse_x = x;
	if (data->last_mouse_y == -1)
		data->last_mouse_y = y;
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	float	new_position_x;
	float	new_position_y;

	new_position_x = 0;
	new_position_y = 0;
	if (data->last_mouse_x == -1 || data->last_mouse_y == -1)
		init_mouse_position(x, y, data);
	if (x > data->last_mouse_x)
		data->player->rotation_angle += data->player->rotation_speed;
	else if (x < data->last_mouse_x)
		data->player->rotation_angle -= data->player->rotation_speed;
	data->player->rotation_angle = normalize_angle(data->player->rotation_angle);
	if (y > data->last_mouse_y)
	{
		new_position_x = data->player->pos_x - cos(data->player->rotation_angle) * 0.5;
		new_position_y = data->player->pos_y - sin(data->player->rotation_angle) * 0.5;
		if (!is_Wall(data, new_position_x, new_position_y))
		{
			data->player->pos_x = new_position_x;
			data->player->pos_y = new_position_y;
		}
	}
	else if (y < data->last_mouse_y)
	{
		new_position_x = data->player->pos_x + cos(data->player->rotation_angle) * 0.5;
		new_position_y = data->player->pos_y + sin(data->player->rotation_angle) * 0.5;
		if (!is_Wall(data, new_position_x, new_position_y))
		{
			data->player->pos_x = new_position_x;
			data->player->pos_y = new_position_y;
		}
	}
	data->last_mouse_x = x;
	data->last_mouse_y = y;
	return (0);
}

void	modify_map(t_map *map)
{
	int	x;
	int	y;

	x = map->pos_m_x;
	y = map->pos_m_y;
	if (x == -1 && y == -1)
		return ;
	map->map[y][x] = 'M';
}

int	main(int ac, char **av)
{
	t_data	*data;

	if(ac != 2)
		return (0);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_error(0);
	parsing(ac, av, data);
	init_data(data);
	// choose_position(data->map);
	// modify_map(data->map);
	mlx_hook(data->mlx_win, 2, 1L >> 0, my_key_hook, data);
	mlx_hook(data->mlx_win, 17, 1L >> 0, close_window_event, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, handle_mouse_move, data);
	mlx_loop_hook(data->mlx, attitude, data);
	mlx_loop(data->mlx);
	return (0);
}
