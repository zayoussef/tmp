#include "raycasting.h"

float	fsqrt(t_data *data, float x, float y)
{
	float x1;
	float y1;

	x1 = data->player->pos_x;
	y1 = data->player->pos_y;
	return (sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)));
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	ft_error(int i)
{
	write(2, "Error\n", 6);
	if (i == 0)
		write(2, "Malloc: Allocation failed\n", 26);
	else if (i == 1)
		write(2, "Mlx error\n", 10);
	else if (i == 2)
		write(2, "value of data not acceptebale\n", 30);
	exit(1);
}

int	simulate_time(void)
{
	static double	time;
	static double	oldTime;
	double			deltaTime;

	deltaTime = 0;
	time += 0.1;
	deltaTime = time - oldTime;
	if (deltaTime >= 0.1)
	{	
		oldTime = time;
		return (1);
	}
	return (0);
}

float	correct_fishbowl(t_data *data, t_ray *ray)
{
	float	correct_dist;

	correct_dist = 0;
	correct_dist = ray->wallDist * cos(data->player->rotation_angle - ray->ray_angle);
	if (correct_dist < 0.1f)
		correct_dist = 0.1f;
	return (correct_dist);
}

int	get_value_color(t_color_data *data)
{
	int	x;

	x = (data->red << 16) | (data->green << 8) | data->blue;
	return (x);
}

