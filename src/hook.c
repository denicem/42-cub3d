/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:00:01 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/15 02:22:21 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void hook(void *param)
{
	t_data *data = (t_data *) param;
	mlx_t *mlx;

	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE)) // Close Window
		mlx_close_window(mlx);
	// TODO: Wall collision
	if (mlx_is_key_down(mlx, MLX_KEY_W)) // Going forward
	{
		data->player->pos.x += data->player->dir.x * MOV;
		data->player->pos.y += data->player->dir.y * MOV;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A)) // Going sideways left
	{
		data->player->pos.x -= data->player->dir.y * MOV;
		data->player->pos.y -= data->player->dir.x * MOV;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S)) // Going backwards
	{
		data->player->pos.x -= data->player->dir.x * MOV;
		data->player->pos.y -= data->player->dir.y * MOV;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D)) // Going sideways right
	{
		data->player->pos.x += data->player->dir.y * MOV;
		data->player->pos.y += data->player->dir.x * MOV;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_R)) // Resetting to start position
	{
		data->player->pos.x = 5;
		data->player->pos.y = 2;

		data->player->dir.x = 0;
		data->player->dir.y = 1;

		data->player->plane.x = 0.66;
		data->player->plane.y = 0;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_RIGHT)) // Rotate Left or Right
	{
		float old_dir_x = data->player->dir.x;
		float old_plane_x = data->player->plane.x;

		if (mlx_is_key_down(mlx, MLX_KEY_LEFT)) // Rotate Left
		{
			data->player->dir.x = data->player->dir.x * cos(ROT) - data->player->dir.y * sin(ROT);
			data->player->dir.y = old_dir_x * sin(ROT) + data->player->dir.y * cos(ROT);
			data->player->plane.x = data->player->plane.x * cos(ROT) - data->player->plane.y * sin(ROT);
			data->player->plane.y = old_plane_x * sin(ROT) + data->player->plane.y * cos(ROT);
		}
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT)) // Rotate Right
		{
			data->player->dir.x = data->player->dir.x * cos(-ROT) - data->player->dir.y * sin(-ROT);
			data->player->dir.y = old_dir_x * sin(-ROT) + data->player->dir.πy * cos(-ROT);
			data->player->plane.x = data->player->plane.x * cos(-ROT) - data->player->plane.y * sin(-ROT);
			data->player->plane.y = old_plane_x * sin(-ROT) + data->player->plane.y * cos(-ROT);
		}
	}
	// printf("POS_X: %f, POS_Y: %f\n", data->player->pos.x, data->player->pos.y);
	raycast(data);
}

//	NOTE:
//	if keyhook is used, (rotation) movement not smooth