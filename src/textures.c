/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:16:09 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/07/23 23:48:13 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static double	find_wall_x(t_data *data, t_ray *ray)
{
	double	wall_x;

	if (ray->side <= 1)
		wall_x = data->player->pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = data->player->pos.x + ray->wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	find_texture_x(t_data *data, mlx_texture_t *texture, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(find_wall_x(data, ray) * (double) texture->width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

int	get_textures(t_data *data)
{
	int	i;

	i = 0;
	(void) data;
	data->png[0] = *mlx_load_png(data->texture_paths[0]);
	data->png[1] = *mlx_load_png(data->texture_paths[1]);
	data->png[2] = *mlx_load_png(data->texture_paths[2]);
	data->png[3] = *mlx_load_png(data->texture_paths[3]);
	// if (!(data->png[0]) || !(data->png[1]) || !(data->png[2]) || !(data->png[3]))
	// 	exit_error(data, "Loading PNG files failed.", FAIL);
	return (1);
}

void	insert_textures(t_data *data, int x, int draw_start, int draw_end, t_ray *ray)
{
	mlx_texture_t	*texture;
	int				tex_x;
	int				tex_y;
	double			step;
	double			texture_pos;

	texture = &data->png[ray->side];
	tex_x = find_texture_x(data, texture, ray);
	step = (1.0 * texture->height) / (draw_end - draw_start);
	texture_pos = (draw_start - HEIGHT / 2 + (draw_end - draw_start) / 2)
		* step;
	while (draw_start < draw_end)
	{
		tex_y = (int)(texture_pos) & (texture->height - 1);
		texture_pos += step;
		if (draw_start >= 0 && draw_start <= HEIGHT)
		{
			// mlx_put_pixel(data->img, x, draw_start, *(uint32_t *)&texture->pixels[(tex_y * texture->height + tex_x) * 4]);
			ft_memcpy(&data->img->pixels[(draw_start
					* data->img->width + x) * 4],
				&texture->pixels[(tex_y * texture->height + tex_x) * 4], 4);
		}
		draw_start++;
	}
}
