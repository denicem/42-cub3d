/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:00:01 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 14:51:46 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	jumpscare(void)
{
	int	random_num;

	random_num = random() % 1000;
	if (random_num == 15)
	{
		random_num *= (random() % 26);
		if (random_num % 2)
			system("afplay textures/jumpscare1.mp3 &");
		else
			system("afplay textures/jumpscare2.mp3 &");
	}
}

static void	movement_up_down(t_data *data, t_vect *vector)
{
	mlx_t	*mlx;

	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		vector->x = data->player->pos.x + data->player->dir.x * MOV;
		vector->y = data->player->pos.y + data->player->dir.y * MOV;
		if (data->map[(int)vector->y][(int)vector->x] == '0')
		{
			data->player->pos.x = vector->x ;
			data->player->pos.y = vector->y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		vector->x = data->player->pos.x - data->player->dir.x * MOV;
		vector->y = data->player->pos.y - data->player->dir.y * MOV;
		if (data->map[(int)vector->y][(int)vector->x] == '0')
		{
			data->player->pos.x = vector->x;
			data->player->pos.y = vector->y;
		}
	}
}

static void	movement_left_right(t_data *data, t_vect *vector)
{
	mlx_t	*mlx;

	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		vector->x = data->player->pos.x - data->player->dir.y * MOV;
		vector->y = data->player->pos.y + data->player->dir.x * MOV;
		if (data->map[(int)vector->y][(int)vector->x] == '0')
		{
			data->player->pos.x = vector->x;
			data->player->pos.y = vector->y;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		vector->x = data->player->pos.x + data->player->dir.y * MOV;
		vector->y = data->player->pos.y - data->player->dir.x * MOV;
		if (data->map[(int)vector->y][(int)vector->x] == '0')
		{
			data->player->pos.x = vector->x;
			data->player->pos.y = vector->y;
		}
	}
}

static void	movement_rotation(t_data *data)
{
	mlx_t	*mlx;
	float	old_dir_x;
	float	old_plane_x;
	float	rot;

	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = data->player->dir.x;
		old_plane_x = data->player->plane.x;
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			rot = ROT;
		else
			rot = -ROT;
		data->player->dir.x = data->player->dir.x * cos(rot)
			- data->player->dir.y * sin(rot);
		data->player->dir.y = old_dir_x * sin(rot)
			+ data->player->dir.y * cos(rot);
		data->player->plane.x = data->player->plane.x
			* cos(rot) - data->player->plane.y * sin(rot);
		data->player->plane.y = old_plane_x * sin(rot)
			+ data->player->plane.y * cos(rot);
	}	
}

void	hook(void *param)
{
	t_data	*data;
	t_vect	vector;
	mlx_t	*mlx;

	data = (t_data *) param;
	jumpscare();
	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	movement_up_down(data, &vector);
	movement_left_right(data, &vector);
	if (mlx_is_key_down(mlx, MLX_KEY_R))
	{
		data->player->pos = data->player_start.pos;
		data->player->dir = data->player_start.dir;
		data->player->plane = data->player_start.plane;
	}
	movement_rotation(data);
	raycast(data);
}
