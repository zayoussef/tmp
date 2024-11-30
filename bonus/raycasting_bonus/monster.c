#include "raycasting_bonus.h"

void render_monster(t_data *data, int i)
{
        int monster_height = (int)(data->size / data->sprite->distance * data->distanceProjPlane) / 2;

        int start_y = (data->height_win / 2) - (monster_height / 2);
        int end_y = (data->height_win / 2) + (monster_height / 2);

		int y = start_y;
        while (y < end_y) 
		{
            my_mlx_pixel_put(data, i, y, 0xFF590030);
			y++;
		}
}


void	rendering_monster(t_data *data)
{
	int	i;

	i = 0;
	data->sprite->pos_m_x = data->map->pos_m_x;
	data->sprite->pos_m_y = data->map->pos_m_y;
	data->sprite->distance = fsqrt(data, data->sprite->pos_m_x, data->sprite->pos_m_y);
	while (i < data->num_rays)
	{
		if (data->ray[i].wallHitContent == 'M')
		{
			render_monster(data, i);
		}
		i++;
	}
}
