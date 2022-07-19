/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:17:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/18 18:39:01 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_vertical_line(int ray, int wallStart, int wallEnd, mlx_image_t *img)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		if (i < wallStart)
			mlx_put_pixel(img, ray, i, get_rgba(0, 0, 0, 255));
		if (i >= wallStart && i <= wallEnd)
			mlx_put_pixel(img, ray, i, get_rgba(255, 0, 0, 255));
		if (i > wallEnd)
			mlx_put_pixel(img, ray, i, get_rgba(255, 255, 255, 255));
		i++;
	}
}
