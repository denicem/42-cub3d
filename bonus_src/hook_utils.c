/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:34:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/07/24 22:25:08 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	turn_left(t_data *data)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = data->player->dir.x;
	old_plane_x = data->player->plane.x;
	data->player->dir.x = data->player->dir.x * cos(ROT)
		- data->player->dir.y * sin(ROT);
	data->player->dir.y = old_dir_x * sin(ROT)
		+ data->player->dir.y * cos(ROT);
	data->player->plane.x = data->player->plane.x
		* cos(ROT) - data->player->plane.y * sin(ROT);
	data->player->plane.y = old_plane_x * sin(ROT)
		+ data->player->plane.y * cos(ROT);
}

void	turn_right(t_data *data)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = data->player->dir.x;
	old_plane_x = data->player->plane.x;
	data->player->dir.x = data->player->dir.x * cos(-ROT)
		- data->player->dir.y * sin(-ROT);
	data->player->dir.y = old_dir_x * sin(-ROT)
		+ data->player->dir.y * cos(-ROT);
	data->player->plane.x = data->player->plane.x
		* cos(-ROT) - data->player->plane.y * sin(-ROT);
	data->player->plane.y = old_plane_x * sin(-ROT)
		+ data->player->plane.y * cos(-ROT);
}
