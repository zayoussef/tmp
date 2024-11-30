#include "raycasting.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->width_win || y < 0 || y >= data->height_win)
		return ;
	dst = data->image->img_data + (y * data->image->size_line + x * (data->image->bpp
				/ 8));
	*(unsigned int *)dst = color;
}

void	color_sky(t_data *data, int i, int *j, int top)
{
	while (*j < top)
	{
		my_mlx_pixel_put(data, i, *j, data->color_sky);
		(*j)++;
	}
}

void	color_floor(t_data *data, int i, int *j)
{
	while (*j < data->height_win)
	{
		my_mlx_pixel_put(data, i, *j, data->color_floor);
		(*j)++;
	}
}

t_img	*get_texture_side(t_data *data, t_ray *ray)
{
	if (ray->foundH && ray->y_step > 0)
		return (&data->wall_texture[1]);
	else if (ray->foundH && ray->y_step < 0)
		return (&data->wall_texture[3]);
	else if (ray->foundV && ray->x_step > 0)
		return (&data->wall_texture[0]);
	else if (ray->foundV && ray->x_step < 0)
		return (&data->wall_texture[2]);
	return (NULL);
}

Uint32	get_texture_color(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->img_data + (y * texture->size_line + x
			* (texture->bpp / 8));
	return (*(Uint32 *)pixel);
}

float	get_wall_x(t_img *image, t_ray *ray)
{
	float	calculate;

	if (ray->foundV)
		calculate = (int)ray->wallHitY % image->width;
	else
		calculate = (int)(ray->wallHitX) % image->width;
	return (calculate);
}

int	wall_height(t_data *data, int i)
{
	int		wall_height;
	double	perp_distance;

	perp_distance = data->ray[i].wallDist
		* cos(data->ray[i].ray_angle - data->player->rotation_angle);
	wall_height = (int)((data->size / perp_distance) * data->distanceProjPlane);
	return (wall_height);
}

void	color_wall(t_data *data, int i, int *j, int bottom)
{
	t_img	*image;
	t_wall	wall;

	image = get_texture_side(data, &data->ray[i]);
	if (!image)
		return ;
	wall.x = get_wall_x(image, &data->ray[i]);
	wall.height = wall_height(data, i);
	while (*j < bottom)
	{
		wall.y = (*j + (wall.height / 2) - (data->height_win / 2))
					* ((double)image->width / wall.height) ;
		if (wall.y >= image->height)
			wall.y = image->height - 1;
		wall.color = get_texture_color(image, wall.x, wall.y);
		my_mlx_pixel_put(data, i, *j, wall.color);
		(*j)++;
	}
}

void	render_walls(t_data *data, t_ray *ray, int i)
{
	int 	j;
	float	height;
	float	distance;
	int		top_pixel;
	int		bottom_pixel;

	top_pixel = 0;
	height = 0;
	j = 0;
	distance = correct_fishbowl(data, ray);
	height = data->size / distance * data->distanceProjPlane;
	top_pixel = (data->height_win / 2) - ((int)height / 2);
	if (top_pixel < 0)
		top_pixel = 0;
	bottom_pixel = (data->height_win / 2) + ((int)height / 2);
	if (bottom_pixel > data->height_win)
		bottom_pixel = data->height_win;
	color_sky(data, i, &j, top_pixel);
	color_wall(data, i, &j, bottom_pixel);
	color_floor(data, i, &j);
}	