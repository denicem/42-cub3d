/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:17:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 16:10:07 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_vertical_line(int ray_count, int wallStart,
						int wallEnd, t_data *data)
{
	int	i;

	i = 0;
	insert_textures(data, ray_count, wallStart, wallEnd);
	while (i < HEIGHT)
	{
		if (i < wallStart)
			mlx_put_pixel(data->img, ray_count, i, get_rgba(data, 1, 255));
		if (i > wallEnd)
			mlx_put_pixel(data->img, ray_count, i, get_rgba(data, 0, 180));
		i++;
	}
}

int	render_world(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Hypercub3d", false);
	if (!(data->mlx))
		return (1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	system("afplay textures/lurking.mp3 &");
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_delete_texture(data->png[0]);
	mlx_delete_texture(data->png[1]);
	mlx_delete_texture(data->png[2]);
	mlx_delete_texture(data->png[3]);
	mlx_terminate(data->mlx);
	system("pkill afplay");
	return (0);
}
