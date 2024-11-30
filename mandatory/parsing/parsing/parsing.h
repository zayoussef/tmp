/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:57:47 by yozainan          #+#    #+#             */
/*   Updated: 2024/10/05 23:53:40 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

typedef unsigned int Uint32;

typedef struct s_color_data
{
	int				red;
	int				green;
	int				blue;
}					t_color_data;

typedef struct s_texture_data
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
}					t_texture_data;

typedef struct s_map
{
	int		height;
	int		width;
	char	**map;
}			t_map;

typedef struct s_img
{
	void	*img;
	char	*img_data;
	int     bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_wall
{
	float		y;
	float		x;
	int		color;
	float		height;
	int		colonne;
}			t_wall;

typedef struct s_player
{
	float		pos_x;
	float		pos_y;
	char		direction;
	int			radius;
	int			turn_Direction;
	int			walk_Direction;
	float		rotation_angle;
	float		move_speed;
	float		rotation_speed;
	int			count_player;
}	t_player;

typedef	struct s_ray
{
	int		index;
	float	lenght;
	float	ray_angle;
	float	x_step;
	float	y_step;
	float	horWallx;
	float	horWally;
	float	verWallx;
	float	verWally;
	bool	foundH;
	bool	foundV;
	int		facedown;
	int		faceup;
	int		faceleft;
	int		faceright;
	float	wallHitX;
	float	wallHitY;
	char	verHitContent;
	char	horHitContent;
	char	wallHitContent;
	float	wallDist;
}	t_ray;

typedef struct s_data
{	
	void			*mlx;
	void			*mlx_win;
	char			**map_org;
	char			**txture;
	char			*file_name;
	char			*tmp;
	int				elements;
	int				fd;
	int				erros;
	float			size;
	long			num_rays;				
	float			width_wall;
	float			distanceProjPlane;
	float			fov_angle;
	float			height_win;
	float			width_win;
	int				color_sky;
	int				color_floor;
	t_color_data	*floor;
	t_color_data	*ceiling;
	t_texture_data	*texture;	
	t_ray			*ray;
	t_map			*map;
	t_player		*player;
	t_img			wall_texture[4];
	t_img			*image;
}					t_data;


/*******  parsing *********/
void				validate_config(int ac, char **av, t_data *map);
char				*validate_color_string(char *line, char *type);
void				check_args(int ac, char **av, t_data *map);
void				check_color(char **comp, t_color_data *color_data);
void				check_empty_file(t_data *map);
void				copy_info(t_data *map);
int					just_texture(char *line);
int					space_line(char *line);
void				copy_map(char *line, t_data *map);
char				*read_map_content(char *line, t_data *map);
void				check_save_texture(t_data *map);
void				check_texture(char *line, t_data *map);
int					check_identifier(char *line, char *tmp);
void				store_texture(char *line, t_data *map);
char				*extract_path(char *line);
void				store_texture_path(char *type, char *path, t_data *map);
void				parse_map(t_data *map);
int					valid_character(char *line);
int					check_player(char *line, t_data *map, int i);
int					validate_map(t_data *map);
int					count(char *line, char c);
int					count_strings(char **map);
int					max_length(char **map);
char				**duplicate_map(t_data *map, int height, int width);
int					check_map_shape(char **map);
int					is_invalid(int x, int y, char **map);
void				ft_free_array(char **str);
char				**make_square_map(t_data *data, int rows, int cols);
void				clean_up_map(char **map, int rows);
char				*make_wide_row(char *line, int cols);
void				parsing(int ac, char **av, t_data *data);

#endif