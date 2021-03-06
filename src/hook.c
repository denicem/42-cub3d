/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:00:01 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 22:33:09 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	movement_rotation(t_data *data)
{
	mlx_t	*mlx;
	float	old_dir_x;
	float	old_plane_x;

	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = data->player->dir.x;
		old_plane_x = data->player->plane.x;
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			turn_left(data);
		else
			turn_right(data);
	}
}

void	mouse_rotate(t_data *data)
{
	int			x;
	int			y;
	static int	old_x;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (x <= WIDTH && x >= 0 && y <= HEIGHT && y >= 0)
	{
		if (x < old_x)
			turn_left(data);
		else if (x > old_x)
			turn_right(data);
	}
	old_x = x;
}

void	hook(void *param)
{
	t_data	*data;
	t_vect	vector;
	mlx_t	*mlx;

	data = (t_data *) param;
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
