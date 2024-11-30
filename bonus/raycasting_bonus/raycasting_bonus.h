#ifndef RAYCASTING_BONUS_H
#define RAYCASTING_BONUS_H

#include "../parsing_bonus/parsing_bonus/parsing_bonus.h"
#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364
# define W 119
# define A 97
# define S 115
# define D 100
# define M_PI 3.14159265358979323846
# define M_PI_2	1.57079632679489661923

void	draw_map_2d(t_data *data);
void	draw_player(t_data *data);
void	cast_rays(t_data *data);
void	draw_rays(t_data *data);
int	    close_window_event(void *param);
int	    is_Wall(t_data *data, float a, float b);
void	init_data(t_data *data);
float	fsqrt(t_data *data, float x, float y);
void	render_walls(t_data *data, t_ray *ray, int i);
void	free_data(t_data *data);
int	    simulate_time(void);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put_mini(t_data *data, int x, int y, int color);
void	ft_error(int i);
float	normalize_angle(float angle);
void	rendering_monster(t_data *data);
void    clear_image(t_data *data, t_img *img);
float	correct_fishbowl(t_data *data, t_ray *ray);
int	    get_value_color(t_color_data *data);
#endif