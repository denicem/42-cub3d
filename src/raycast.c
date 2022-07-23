/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:55:53 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 22:09:59 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// DEBUG
#include <time.h>

static void	reset_ray(t_ray *ray)
{
	ray->camera = 0;
	ray->dir.x = 0;
	ray->dir.y = 0;
	ray->pos.x = 0;
	ray->pos.y = 0;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
	ray->delta_dist.x = 0;
	ray->delta_dist.y = 0;
	ray->side = 0;
	ray->hit = 0;
	ray->wall_dist = 0;
}

void	dda(t_ray *ray, t_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos.x += ray->step.x;
			ray->side = 0;
			if (ray->dir.x > 0)
				ray->side = 1;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->pos.y += ray->step.y;
			ray->side = 2;
			if (ray->dir.y > 0)
				ray->side = 3;
		}
		if (data->map[ray->pos.y][ray->pos.x] == '1')
			ray->hit = 1;
	}
}

void	raycast(t_data *data)
{
	//t_ray	ray;
	int		raycount;
	int		height;
	int		wallstart;
	int		wallend;

	raycount = 0;
	while (raycount < WIDTH)
	{
		reset_ray(&data->ray); //resets data->ray
		init_ray(&data->ray, data, raycount); // initialize starting values for data->ray
		set_dist(&data->ray, data); // setting up step and side_dist for data->ray
		dda(&data->ray, data); //DDA
		set_ray_dist(&data->ray); // defining data.ray distance to wall
		set_draw_val(&data->ray, &height, &wallstart, &wallend); // defining height and draw values
		//draw ONE vertical line and move to next data.ray
		draw_vertical_line(raycount, wallstart, wallend, data);
		raycount++;
	}
}
