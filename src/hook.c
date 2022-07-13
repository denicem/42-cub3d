/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:00:01 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/14 00:03:07 by dmontema         ###   ########.fr       */
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
	// if (mlx_is_key_down(mlx, MLX_KEY_W))
	// {
	// 	float player_cos = (cos(deg_to_rad(player_angle)) * MOV);
	// 	float player_sin = (sin(deg_to_rad(player_angle)) * MOV);
	// 	player.x += player_cos;
	// 	player.y += player_sin;
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_A))
	// if (mlx_is_key_down(mlx, MLX_KEY_S))
	// {
	// 	float player_cos = (cos(deg_to_rad(player_angle)) * MOV);
	// 	float player_sin = (sin(deg_to_rad(player_angle)) * MOV);
	// 	player.x -= player_cos;
	// 	player.y -= player_sin;
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_D))
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		double old_dir_x = dir.x;
		double old_plane_x = plane.x;

		if (mlx_is_key_down(mlx, MLX_KEY_LEFT)) // TODO: use rotations matrix here
		{
			// player_angle -= ROT;
			// if (player_angle < 0)
			// 	player_angle = 359;
			dir.x = dir.x * cos(ROT) - dir.y * sin(ROT);
			dir.y = old_dir_x * sin(ROT) + dir.y * cos(ROT);
			plane.x = plane.x * cos(ROT) - plane.y * sin(ROT);
			plane.y = old_plane_x * sin(ROT) + plane.y * cos(ROT);
		}
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		{
			// player_angle += ROT;
			// if (player_angle >= 360)
			// 	player_angle = 0;
			dir.x = dir.x * cos(-ROT) - dir.y * sin(-ROT);
			dir.y = old_dir_x * sin(-ROT) + dir.y * cos(-ROT);
			plane.x = plane.x * cos(-ROT) - plane.y * sin(-ROT);
			plane.y = old_plane_x * sin(-ROT) + plane.y * cos(-ROT);
		}
		printf("DIR_X: %f, DIR_Y: %f\n", dir.x, dir.y);
		// printf("ANG: %f\n", player_angle);
	}
	raycast_dda_prototype(mlx, data.img);
	// raycast_prototype_3(data.img);
}