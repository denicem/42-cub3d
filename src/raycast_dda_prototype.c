/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda_prototype.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:55:53 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/15 00:43:29 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void reset_ray(t_ray *ray)
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

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_vertical_line(int x, int drawStart, int drawEnd, mlx_image_t *img)
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

void	raycast_dda_prototype(t_data *data)
{
	t_ray	ray;
	int		rayCount;
	int		height;
	int		wallStart;
	int		wallEnd;

	int map[10][10] = //temp
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,0,0,1,1,1,1},
		{1,0,1,0,0,0,0,1,0,1},
		{1,0,1,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	rayCount = 0;
	while (rayCount < WIDTH)
	{
		//resets ray
		reset_ray(&ray);
		// setting up starting values for a ray
		ray.camera = 2 * rayCount / (float) WIDTH - 1;
		ray.dir.x = data->player->dir.x + data->player->plane.x * ray.camera;
		ray.dir.y = data->player->dir.y + data->player->plane.y * ray.camera;
		ray.pos = data->player->pos;
		if (ray.dir.x == 0)
			ray.delta_dist.x = INFINITY;
		else
			ray.delta_dist.x = fabs(1.0 / ray.dir.x);
		if (ray.dir.y == 0)
			ray.delta_dist.y = INFINITY;
		else
			ray.delta_dist.y = fabs(1.0 / ray.dir.y);

		// setting up step and side_dist for ray
		if (ray.dir.x < 0)
		{
			ray.step.x = -1;
			ray.side_dist.x = (data->player->pos.x - ray.pos.x) * ray.delta_dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.side_dist.x = (ray.pos.x + 1.0 - data->player->pos.x) * ray.delta_dist.x;
		}
		if (ray.dir.y < 0)
		{
			ray.step.y = -1;
			ray.side_dist.y = (data->player->pos.y - ray.pos.y) * ray.delta_dist.y;
		}
		else
		{
			ray.step.y = 1;
			ray.side_dist.y = (ray.pos.y + 1.0 - data->player->pos.y) * ray.delta_dist.y;
		}

		//DDA	
		while (ray.hit == 0)
		{
			if (ray.side_dist.x < ray.side_dist.y)
			{
				ray.side_dist.x += ray.delta_dist.x;
				ray.pos.x += ray.step.x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist.y += ray.delta_dist.y;
				ray.pos.y += ray.step.y;
				ray.side = 1;
			}
			if (map[(int) ray.pos.y][(int) ray.pos.x] >= 1) //TODO: change to ASCII VALUES for official map
				ray.hit = 1;
		}

		// defining ray distance to wall
		if (ray.side == 0)
			ray.wall_dist = ray.side_dist.x - ray.delta_dist.x;
		else
			ray.wall_dist = ray.side_dist.y - ray.delta_dist.y;
		
		// defining height and draw values
		height = (int) (HEIGHT * 0.5 / ray.wall_dist);
		wallStart = -height / 2 + HEIGHT / 2;
		if (wallStart < 0)
			wallStart = 0;
		wallEnd = height / 2 + HEIGHT / 2;
		if (wallEnd >= HEIGHT)
			wallEnd = HEIGHT - 1;
		
		//draw ONE vertical line and move to next ray
		draw_vertical_line(rayCount, wallStart, wallEnd, data->img);
		rayCount++;
	}
}

// print statements for debugging purposes
// printf("OLD\n");
// printf("sidex: %f deltax: %f\nsidey: %f deltay: %f\n\n", side_dist.x, delta_dist.x, side_dist.y, delta_dist.y);
// printf("CAMERA_X: %f\n", camera_x);
// printf("CURR_POS[x][y]: %d %d\n", (int) curr_pos.x, (int) curr_pos.y);
// printf("RAYDIR[x][y]: %f %f\n", raydir.x, raydir.y);
// printf("DELTA_DIST[x][y]: %f %f\n", delta_dist.x, delta_dist.y);
// printf("SIDE_DIST[x][y]: %f %f\n", side_dist.x, side_dist.y);
// printf("STEP[x][y]: %d %d\n", (int) step.x, (int) step.y);
// printf("HIT? %d, SIDE: %d\n", hit, side);
// printf("WALL_DIST: %f, HEIGHT: %d, DRAW_START: %d, DRAW_END: %d\n", perpWall_dist, height_old, drawStart, drawEnd);
// printf("X: %d\n\n", rayCount);

// printf("\nNEW\n");
// printf("sidex: %f deltax: %f\nsidey: %f deltay: %f\n\n", ray.side_dist.x, ray.delta_dist.x, ray.side_dist.y, ray.delta_dist.y);
// printf("CAMERA_X: %f\n",ray.camera);
// printf("CURR_POS[x][y]: %d %d\n", (int) ray.pos.x, (int) ray.pos.y);
// printf("RAYDIR[x][y]: %f %f\n", ray.dir.x, ray.dir.y);
// printf("DELTA_DIST[x][y]: %f %f\n", ray.delta_dist.x, ray.delta_dist.y);
// printf("SIDE_DIST[x][y]: %f %f\n", ray.side_dist.x, ray.side_dist.y);
// printf("STEP[x][y]: %d %d\n", (int) ray.step.x, (int) ray.step.y);
// printf("HIT? %d, SIDE: %d\n", ray.hit, ray.side);
// printf("WALL_DIST: %f, HEIGHT: %d, DRAW_START: %d, DRAW_END: %d\n", ray.wall_dist, height, wallStart, wallEnd);
// printf("X: %d\n\n", rayCount);

// printf("OLD: %f %f\nNEW: %f %f\n", side_dist.x, side_dist.y, ray.side_dist.x, ray.side_dist.y);