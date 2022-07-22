/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:00:01 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/22 18:38:33 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	jumpscare()
{
	int random_num;
	
	random_num = random() % 1000;
	if(random_num == 15)
	{
		random_num *= (random() % 26);
		if (random_num % 2)
			system("afplay textures/jumpscare1.mp3 &");
		else 
			system("afplay textures/jumpscare2.mp3 &");
	}
}

void hook(void *param)
{
	t_data *data = (t_data *) param;
	mlx_t *mlx;

	jumpscare();
	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE)) // Close Window
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W)) // Going forward
	{
		t_vect	vector;
		vector.x = data->player->pos.x + data->player->dir.x * MOV;
		vector.y = data->player->pos.y + data->player->dir.y * MOV;
		if (data->map[(int)vector.y][(int)vector.x] == '0')
		{
			data->player->pos.x = vector.x ;
			data->player->pos.y = vector.y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A)) // Going sideways left
	{
		t_vect	vector;
		vector.x = data->player->pos.x - data->player->dir.y * MOV;
		vector.y = data->player->pos.y + data->player->dir.x * MOV;
		if (data->map[(int)vector.y][(int)vector.x] == '0')
		{
			data->player->pos.x = vector.x;
			data->player->pos.y = vector.y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S)) // Going backwards
	{
		t_vect	vector;
		vector.x = data->player->pos.x - data->player->dir.x * MOV;
		vector.y = data->player->pos.y - data->player->dir.y * MOV;
		if (data->map[(int)vector.y][(int)vector.x] == '0')
		{
			
			data->player->pos.x = vector.x;
			data->player->pos.y = vector.y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D)) // Going sideways right
	{
		t_vect	vector;
		vector.x = data->player->pos.x + data->player->dir.y * MOV;
		vector.y = data->player->pos.y - data->player->dir.x * MOV;
		if (data->map[(int)vector.y][(int)vector.x] == '0')
		{
			data->player->pos.x = vector.x;
			data->player->pos.y = vector.y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_R)) // Resetting to start position
	{
		data->player->pos = data->player_start.pos;
		data->player->dir = data->player_start.dir;
		data->player->plane = data->player_start.plane;
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
			data->player->dir.y = old_dir_x * sin(-ROT) + data->player->dir.y * cos(-ROT);
			data->player->plane.x = data->player->plane.x * cos(-ROT) - data->player->plane.y * sin(-ROT);
			data->player->plane.y = old_plane_x * sin(-ROT) + data->player->plane.y * cos(-ROT);
		}
	}
	raycast(data);
}
