#include "raycasting.h"

int	is_Wall(t_data *data, float a, float b)
{
	int	x;
	int	y;

	x = (int)floor(a / data->size);
	y = (int)floor(b / data->size);
	if (a < 0 || a > data->width_win || b < 0 || b > data->height_win)
		return (1);
	if (data->map->map[y][x] == '0' || data->map->map[y][x] == 'E'
		||  data->map->map[y][x] == 'S' ||  data->map->map[y][x] == 'W'
		||  data->map->map[y][x] == 'N')
		return (0);
	return (1);
}

int	close_window_event(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_data(data);
	return (0);
}

// void	draw_ray(t_data *data, t_ray *ray)
// {
// 	float	x = data->player->pos_x;
// 	float	y = data->player->pos_y;
// 	float	dx = cos(ray->ray_angle);
// 	float	dy = sin(ray->ray_angle);
// 	float	max_dist = fsqrt(data, ray->wallHitX, ray->wallHitY);
// 	float	current_dist = 0;
// 	while (current_dist < max_dist)
// 	{
// 		mlx_pixel_put(data->mlx, data->mlx_win, data->mini_map *x, data->mini_map * y, 0xFFFFFF);
// 		x += dx * 0.5;
// 		y += dy * 0.5;
// 		current_dist = fsqrt(data, x, y);
// 	}
// }


void	cast_ray_vertical(t_data *data, t_ray * ray)
{
	float		x_intercept;
	float		y_intercept;
	float 		next_x;
	float 		next_y;

	x_intercept = floor(data->player->pos_x / data->size) * data->size;
	if (ray->faceright)
		x_intercept += data->size;
	y_intercept = data->player->pos_y + (x_intercept - data->player->pos_x) * tan(ray->ray_angle);
	ray->x_step = data->size;
	if (ray->faceleft)
		ray->x_step *= -1;
	ray->y_step = data->size * tan(ray->ray_angle);
	if (ray->faceup && ray->y_step > 0)
		ray->y_step *= -1;
	else if (ray->facedown && ray->y_step < 0)
		ray->y_step *= -1;
	next_x = x_intercept;
	next_y = y_intercept;
	while (next_x >= 0 && next_x <= data->width_win && next_y >= 0 && next_y <= data->height_win)
	{
		float x = next_x;
		if (ray->faceleft)
			x = x - 1;
		float y = next_y;
		if (is_Wall(data, x, y))
		{
			ray->verWallx = next_x;
			ray->verWally = next_y;
			ray->verHitContent = data->map->map[(int)floor(y / data->size)][(int)floor(x / data->size)];
			ray->foundV = true;
			break;
		}
		else
		{
			next_x += ray->x_step;
			next_y += ray->y_step;
		}
	}
}

void	cast_ray_horizontal(t_data *data, t_ray * ray)
{
	float		x_intercept;
	float		y_intercept;
	float 		next_x;
	float 		next_y;

	y_intercept = floor(data->player->pos_y / data->size) * data->size;
	if (ray->facedown)
		y_intercept += data->size;
	x_intercept = data->player->pos_x + (y_intercept - data->player->pos_y) / tan(ray->ray_angle);
	ray->x_step = data->size / tan(ray->ray_angle);
	if (ray->faceleft && ray->x_step > 0)
		ray->x_step *= -1;
	else if (ray->faceright && ray->x_step < 0)
		ray->x_step *= -1;
	ray->y_step = data->size;
	if (ray->faceup)
		ray->y_step *= -1;
	next_x = x_intercept;
	next_y = y_intercept;
	while (next_x >= 0 && next_x <= data->width_win && next_y >= 0 && next_y <= data->height_win)
	{
		float x = next_x;
		float y = next_y;
		if (ray->faceup)
			y = y - 1;
		if (is_Wall(data, x, y))
		{
			ray->horWallx = next_x;
			ray->horWally = next_y;
			ray->horHitContent = data->map->map[(int)floor(y / data->size)][(int)floor(x / data->size)];
			ray->foundH = true;
			break;
		}
		else
		{
			next_x += ray->x_step;
			next_y += ray->y_step;
		}
	}
}

void	cast_ray(t_data *data, t_ray *ray)
{
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->facedown = 1;
	else
		ray->facedown = 0;
	ray->faceup = !ray->facedown;
	if (ray->ray_angle < (M_PI_2) || ray->ray_angle > (M_PI_2 * 3))
		ray->faceright = 1;
	else
		ray->faceright = 0;
	ray->faceleft = !ray->faceright;
	cast_ray_horizontal(data, ray);
	float horHitDis = INT_MAX;
	if (ray->foundH)
		horHitDis = fsqrt(data, ray->horWallx, ray->horWally);
	cast_ray_vertical(data, ray);
	float verHitDis = INT_MAX;
	if (ray->foundV)
		verHitDis = fsqrt(data, ray->verWallx, ray->verWally);
	if (horHitDis < verHitDis)
	{
		ray->wallHitX = ray->horWallx;
		ray->wallHitY = ray->horWally;
		ray->wallHitContent = ray->horHitContent;
		ray->wallDist = horHitDis;
		ray->foundH = true;
		ray->foundV = false;
	}
	else
	{
		ray->wallHitX = ray->verWallx;
		ray->wallHitY = ray->verWally;
		ray->wallHitContent = ray->verHitContent;
		ray->wallDist = verHitDis;
		ray->foundV = true;
		ray->foundH = false;
	}
}

void	set_data_ray_to_zero(t_ray *ray)
{
	ray->x_step = 0;
	ray->y_step = 0;
	ray->facedown = 0;
	ray->faceup = 0;
	ray->faceright = 0;
	ray->faceleft = 0;
	ray->foundH = false;
	ray->foundV = false;
	ray->horWallx = 0;
	ray->horWally = 0;
	ray->verWallx = 0;
	ray->verWally = 0;
	ray->wallHitX = 0;
	ray->wallHitY = 0;
	ray->horHitContent = 0;
	ray->verHitContent = 0;
	ray->wallHitContent = 0;
	ray->wallDist = 0;
}

void	cast_rays(t_data *data)
{
	float	ray_angle;
	int		count;

	ray_angle = data->player->rotation_angle - (data->fov_angle / 2);
	count = 0;
	while (count < data->num_rays)
	{
		set_data_ray_to_zero(&data->ray[count]);
		data->ray[count].ray_angle = normalize_angle(ray_angle);
		cast_ray(data, &data->ray[count]);
		render_walls(data, &data->ray[count], count);
		ray_angle += data->fov_angle / data->num_rays;
		count++;
	}
}

