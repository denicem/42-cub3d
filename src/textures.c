/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:16:09 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/07/19 23:31:43 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_texture_x(t_data *info, mlx_texture_t *texture)
{
	int	tex_x;
	t_ray ray;

	tex_x = (int)(find_wall_x(info) * (double)texture->width);
	if ((info->side == 0 && info->raycast.dir.x > 0)
		|| (info->side == 1 && info->raycast.dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	insert_textures(t_gen_info *info, int x, int draw_start, int draw_end)
{
	mlx_texture_t	*texture;
	int				tex_x;
	int				tex_y;
	double			step;
	double			texture_pos;

	texture = &info->xpm[info->side]->texture;
	tex_x = find_texture_x(info, texture);
	step = (1.0 * texture->height) / (draw_end - draw_start);
	texture_pos = (draw_start - SCREEN_H / 2 + (draw_end - draw_start) / 2)
		* step;
	while (draw_start < draw_end)
	{
		tex_y = (int)(texture_pos) & (texture->height - 1);
		texture_pos += step;
		if (draw_start >= 0 && draw_start <= SCREEN_H)
		{
			ft_memcpy(&info->m_img->pixels[(draw_start
					* info->m_img->width + x) * 4],
				&texture->pixels[(tex_y * texture->height + tex_x) * 4], 4);
		}
		draw_start++;
	}
}
