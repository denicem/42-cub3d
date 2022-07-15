/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:19:38 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/15 02:22:08 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void	init_ray(t_ray *ray, t_data *data, int rayCount)
{
	ray->camera = 2 * rayCount / (float) WIDTH - 1;
	ray->dir.x = data->player->dir.x + data->player->plane.x * ray->camera;
	ray->dir.y = data->player->dir.y + data->player->plane.y * ray->camera;
	ray->pos = data->player->pos;
	if (ray->dir.x == 0)
		ray->delta_dist.x = INFINITY;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INFINITY;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);

}

void	set_dist(t_ray *ray, t_data *data)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (data->player->pos.x - ray->pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->pos.x + 1.0 - data->player->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (data->player->pos.y - ray->pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->pos.y + 1.0 - data->player->pos.y) * ray->delta_dist.y;
	}
}

void	dda(t_ray *ray, int map[10][10]) // TODO: use map from struct data
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->pos.y += ray->step.y;
			ray->side = 1;
		}
		if (map[(int) ray->pos.y][(int) ray->pos.x] >= 1) // TODO: change to ASCII VALUES for official map and change map
			ray->hit = 1;
	}
}

void	set_ray_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

void	set_draw_val(t_ray *ray, int *height, int *wallStart, int* wallEnd)
{
	*height = (int) (HEIGHT * 0.5 / ray->wall_dist);
	*wallStart = -(*height) / 2 + HEIGHT / 2;
	if (wallStart < 0)
		wallStart = 0;
	*wallEnd = (*height) / 2 + HEIGHT / 2;
	if (*wallEnd >= HEIGHT)
		*wallEnd = HEIGHT - 1;
}
