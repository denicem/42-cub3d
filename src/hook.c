/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:00:01 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/13 00:03:34 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void hook(void *param)
{
	t_data data = *((t_data *) param);
	mlx_t *mlx;

	mlx = data.mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		start_pos.x += dir.x * MOV;
	}
	// if (mlx_is_key_down(mlx, MLX_KEY_A))
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		start_pos.y += dir.y * MOV;
	// if (mlx_is_key_down(mlx, MLX_KEY_D))
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		double old_dir_x = dir.x;
		double old_plane_x = plane.x;

		if (mlx_is_key_down(mlx, MLX_KEY_LEFT)) // TODO: use rotations matrix here
		{
			dir.x = dir.x * cos(ROT) - dir.y * sin(ROT);
			dir.y = old_dir_x * sin(ROT) + dir.y * cos(ROT);
			plane.x = plane.x * cos(ROT) - plane.y * sin(ROT);
			plane.y = old_plane_x * sin(ROT) + plane.y * cos(ROT);
		}
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		{
			dir.x = dir.x * cos(-ROT) - dir.y * sin(-ROT);
			dir.y = old_dir_x * sin(-ROT) + dir.y * cos(-ROT);
			plane.x = plane.x * cos(-ROT) - plane.y * sin(-ROT);
			plane.y = old_plane_x * sin(-ROT) + plane.y * cos(-ROT);
		}
		printf("DIR_X: %f, DIR_Y: %f\n", dir.x, dir.y);
		raycast_dda_prototype(mlx, data.img);
	}
}