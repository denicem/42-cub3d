/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda_prototype.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:55:53 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/15 00:39:23 by dmontema         ###   ########.fr       */
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

	printf("RAY_HIT: %d\n", ray.hit);
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

	// printf("start_pos: %d %d\nplayer_pos: %d %d\n", (int) start_pos.x, (int) start_pos.y, (int) data->player->pos.x, (int) data->player->pos.y);

	rayCount = 0;
	while (rayCount < WIDTH)
	{
		//resets ray
		reset_ray(&ray);
		// setting up starting values for a ray
		// float camera_x = 2 * rayCount / (float) WIDTH - 1;

		ray.camera = 2 * rayCount / (float) WIDTH - 1;

		// t_vect raydir;
		// raydir.x = dir.x + plane.x * camera_x;
		// raydir.y = dir.y + plane.y * camera_x;

		ray.dir.x = data->player->dir.x + data->player->plane.x * ray.camera;
		ray.dir.y = data->player->dir.y + data->player->plane.y * ray.camera;
		
		// t_vect curr_pos;
		// curr_pos = start_pos;

		ray.pos = data->player->pos;

		// setting up delta_dist for ray
		// t_vect side_dist;
		// t_vect delta_dist;
		// if (raydir.x == 0)
		// 	delta_dist.x = INFINITY;
		// else
		// 	delta_dist.x = fabs(1.0 / raydir.x);
		// if (raydir.y == 0)
		// 	delta_dist.y = INFINITY;
		// else
		// 	delta_dist.y = fabs(1.0/raydir.y);

		if (ray.dir.x == 0)
			ray.delta_dist.x = INFINITY;
		else
			ray.delta_dist.x = fabs(1.0 / ray.dir.x);
		if (ray.dir.y == 0)
			ray.delta_dist.y = INFINITY;
		else
			ray.delta_dist.y = fabs(1.0 / ray.dir.y);

		// float perpWall_dist;

		// t_vect step;
		// int hit = 0;
		// int side;

		// setting up step and side_dist for ray
		// if (raydir.x < 0)
		// {
		// 	step.x = -1;
		// 	side_dist.x = (start_pos.x - curr_pos.x) * delta_dist.x;
		// }
		// else
		// {
		// 	step.x = 1;
		// 	side_dist.x = (curr_pos.x + 1.0 - start_pos.x) * delta_dist.x;
		// }
		// if (raydir.y < 0)
		// {
		// 	step.y = -1;
		// 	side_dist.y = (start_pos.y- curr_pos.y) * delta_dist.y;
		// }
		// else
		// {
		// 	step.y = 1;
		// 	side_dist.y = (curr_pos.y + 1.0 - start_pos.y) * delta_dist.y;
		// }

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
		// while (hit == 0)
		// {
		// 	if (side_dist.x < side_dist.y)
		// 	{
		// 		side_dist.x += delta_dist.x;
		// 		curr_pos.x += step.x;
		// 		side = 0;
		// 	}
		// 	else
		// 	{
		// 		side_dist.y += delta_dist.y;
		// 		curr_pos.y += step.y;
		// 		side = 1;
		// 	}
		// 	if (map[(int) curr_pos.y][(int) curr_pos.x] >= 1)
		// 		hit = 1;
		// }
	
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
		// if (side == 0)
		// 	perpWall_dist = (side_dist.x  - delta_dist.x);
		// else
		// 	perpWall_dist = (side_dist.y  - delta_dist.y);

		if (ray.side == 0)
			ray.wall_dist = ray.side_dist.x - ray.delta_dist.x;
		else
			ray.wall_dist = ray.side_dist.y - ray.delta_dist.y;
		
		// defining height and draw values
		// int height_old = (int) (0.5 * HEIGHT / perpWall_dist);

		height = (int) (HEIGHT * 0.5 / ray.wall_dist);

		// int drawStart = -height_old / 2 + HEIGHT / 2;
		// if (drawStart < 0)
		// 	drawStart = 0;
		// int drawEnd = height_old / 2 + HEIGHT / 2;
		// if (drawEnd >= HEIGHT)
		// 	drawEnd = HEIGHT - 1;

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