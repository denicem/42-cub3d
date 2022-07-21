/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:16:09 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/07/21 17:53:28 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


static double	find_wall_x(t_data *data, t_ray *ray)
{
	double	wall_x;


	if (data->side == 0 || data->side == 1)
		wall_x = data->player->pos.x + ray->wall_dist * ray->pos.y;
	else
		wall_x = data->player->pos.x +ray->wall_dist * ray->pos.x;
	wall_x -= floor((wall_x));
	return (wall_x);
}

static int	find_texture_x(t_data *data, mlx_texture_t *texture, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(find_wall_x(data, ray) * (double)texture->width);
	if ((data->side == 0 && ray->dir.x > 0)
		|| (data->side == 1 && ray->dir.x < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

int	get_textures(t_data *data)
{
	int	i;

	i = 0;
	data->png[0] = *mlx_load_png(data->n_texture);
	data->png[1] = *mlx_load_png(data->s_texture);
	data->png[2] = *mlx_load_png(data->w_texture);
	data->png[3] = *mlx_load_png(data->e_texture);
/* 	if (!data->png[0] || !data->png[1] || !data->png[2] || !data->png[3])
	{
		error_free_exit("ERROR\ntexture path", data, INFO_MAP);
	} */
	// data->m_wall = mlx_load_png("./minimap/img/dungeon.png");
	// data->player_img = mlx_load_png("./minimap/img/person.png");
	// data->back_g = mlx_load_png("./minimap/img/playground.png");
	return (1);
}

void	insert_textures(t_data *data, int x, int draw_start, int draw_end, t_ray *ray)
{
	mlx_texture_t	*texture;
	int				tex_x;
	int				tex_y;
	double			step;
	double			texture_pos;

	texture = &data->png[data->side];
	tex_x = find_texture_x(data, texture, ray);
	step = (1.0 * texture->height) / (draw_end - draw_start);
	texture_pos = (draw_start - HEIGHT/ 2 + (draw_end - draw_start) / 2)
		* step;
	while (draw_start < draw_end)
	{
		tex_y = (int)(texture_pos) & (texture->height - 1);
		texture_pos += step;
		if (draw_start >= 0 && draw_start <= HEIGHT)
		{
			ft_memcpy(&data->img->pixels[(draw_start
					* data->img->width + x) * 4],
				&texture->pixels[(tex_y * texture->height + tex_x) * 4], 4);
		}
		draw_start++;
	}
}
