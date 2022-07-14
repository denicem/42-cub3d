/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:00:01 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/14 02:52:18 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void hook(void *param)
{
	t_data data = *((t_data *) param);
	mlx_t *mlx;

	mlx = data.mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE)) // Close Window
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W)) // Going forward
	{
		start_pos.x += dir.x * MOV;
		start_pos.y += dir.y * MOV;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A)) // Going sideways left
	{
		start_pos.x -= dir.y * MOV;
		start_pos.y -= dir.x * MOV;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S)) // Going backwards
	{
		start_pos.x -= dir.x * MOV;
		start_pos.y -= dir.y * MOV;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D)) // Going sideways right
	{
		start_pos.x += dir.y * MOV;
		start_pos.y += dir.x * MOV;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_R)) // Resetting to start position
	{
		start_pos.x = 5;
		start_pos.y = 2;

		dir.x = 0;
		dir.y = 1;

		plane.x = 0.66;
		plane.y = 0;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_RIGHT)) // Rotate Left or Right
	{
		double old_dir_x = dir.x;
		double old_plane_x = plane.x;

		if (mlx_is_key_down(mlx, MLX_KEY_LEFT)) // Rotate Left
		{
			dir.x = dir.x * cos(ROT) - dir.y * sin(ROT);
			dir.y = old_dir_x * sin(ROT) + dir.y * cos(ROT);
			plane.x = plane.x * cos(ROT) - plane.y * sin(ROT);
			plane.y = old_plane_x * sin(ROT) + plane.y * cos(ROT);
		}
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT)) // Rotate Right
		{
			dir.x = dir.x * cos(-ROT) - dir.y * sin(-ROT);
			dir.y = old_dir_x * sin(-ROT) + dir.y * cos(-ROT);
			plane.x = plane.x * cos(-ROT) - plane.y * sin(-ROT);
			plane.y = old_plane_x * sin(-ROT) + plane.y * cos(-ROT);
		}
		// printf("DIR_X: %f, DIR_Y: %f\n", dir.x, dir.y);
	}
	raycast_dda_prototype(mlx, data.img);
}

//	NOTE:
//	if keyhook is used, (rotation) movement not smooth