/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:17:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/21 18:03:41 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_vertical_line(int ray_count, int wallStart, int wallEnd, t_data *data, t_ray *ray)
{
	int	i;

	i = 0;
	insert_textures(data, ray_count, wallStart, wallEnd, ray);
	while (i < HEIGHT)
	{
		if (i < wallStart)
			mlx_put_pixel(data->img, ray_count, i, get_rgba(0, 0, 0, 255));
		// if (i >= wallStart && i <= wallEnd)
		// 	mlx_put_pixel(img, ray, i, get_rgba(255, 0, 0, 128));
		if (i > wallEnd)
			mlx_put_pixel(data->img, ray_count, i, get_rgba(0, 0, 0, 255));
		i++;
	}
}

int render_world(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Hypercub3d", true);
	if (!(data->mlx))
		return (1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	init_val(data);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free(data->player);
	return (0);
}