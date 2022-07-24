/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 00:09:48 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 14:51:46 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	set_dir_ew(t_data *data, char c)
{
	if (c == 'E')
	{
		data->player->dir.x = -1;
		data->player->dir.y = 0;
		data->player->plane.x = 0;
		data->player->plane.y = PLANE;
	}
	if (c == 'W')
	{
		data->player->dir.x = 1;
		data->player->dir.y = 0;
		data->player->plane.x = 0;
		data->player->plane.y = -PLANE;
	}
}

static void	set_dir_ns(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player->dir.x = 0;
		data->player->dir.y = -1;
		data->player->plane.x = -PLANE;
		data->player->plane.y = 0;
	}
	if (c == 'S')
	{
		data->player->dir.x = 0;
		data->player->dir.y = 1;
		data->player->plane.x = PLANE;
		data->player->plane.y = 0;
	}
}

static void	set_player_pos_dir(t_data *data, int x, int y, char c)
{
	data->player->pos.x = x + 0.5;
	data->player->pos.y = y + 0.5;
	set_dir_ns(data, c);
	set_dir_ew(data, c);
	data->player_start.pos = data->player->pos;
	data->player_start.dir = data->player->dir;
	data->player_start.plane = data->player->plane;
}

void	set_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (is_player_char(data->map[y][x]))
			{
				set_player_pos_dir(data, x, y, data->map[y][x]);
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
