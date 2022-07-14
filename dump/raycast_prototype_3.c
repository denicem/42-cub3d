/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_prototype_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 21:07:22 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/13 23:45:01 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	draw_vertical_line(int x, int drawStart, int drawEnd, mlx_image_t *img)
{
	int	i;

	i = 0;
	// insert_textures(x, drawStart, drawEnd);
	while (i < HEIGHT)
	{
		if (i < drawStart)
			mlx_put_pixel(img, x, i, get_rgba(0, 0, 0, 255));
		if (i >= drawStart && i <= drawEnd)
			mlx_put_pixel(img, x, i, get_rgba(255, 0, 0, 255));
		if (i > drawEnd)
			mlx_put_pixel(img, x, i, get_rgba(255, 255, 255, 255));
		i++;
	}
}

float get_dist(t_vect a, t_vect b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

float deg_to_rad(float degree)
{
	return (degree * PI / 180);
}

float inc_angle()
{
	return (FOV / WIDTH);
}

void 	raycast_prototype_3(mlx_image_t *img)
{
	int map[10][10] =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,0,0,0,0,0,1},
		{1,0,1,0,0,0,1,0,0,1},
		{1,0,1,0,0,0,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1},
	};
	int	prec = 64;

	float ray_ang = player_angle - (FOV / 2);
	int rayCount;
	t_vect ray;
	int wall = 0;
	float dist;
	int height;
	int drawStart;
	int drawEnd;

	rayCount = 0;
	while (rayCount < WIDTH)
	{
		wall = 0;
		ray = player;
		float ray_cos = cos(deg_to_rad(ray_ang) / prec);
		float ray_sin = sin(deg_to_rad(ray_ang) / prec);
		
		while (wall == 0)
		{
			ray.x += ray_cos;
			ray.y += ray_sin;
			// printf("RAY X: %f, RAY Y: %f\n", floor(ray.x), floor(ray.y));
			wall = map[(int) floor(ray.y)][(int) floor(ray.x)];
		}
		dist = get_dist(ray, player);
		// printf("RAYCOUNT: %d - DISTANCE: %f\n", rayCount, dist);
		dist *= cos(deg_to_rad(ray_ang - player_angle));
		// printf("RAYCOUNT: %d - DISTANCE: %f\n", rayCount, dist);

		height = (int) ((HEIGHT * 0.5) / dist);
		drawStart = -height / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = height / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		// printf("HEIGHT: %d\n", height);
		// printf("DRAW_START: %d, DRAW_END: %d\n", drawStart, drawEnd);
		draw_vertical_line(rayCount, drawStart, drawEnd, img);

		ray_ang += inc_angle();
		rayCount++;
	}
}
