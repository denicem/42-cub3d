/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:55:53 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/15 02:21:01 by dmontema         ###   ########.fr       */
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

void	raycast(t_data *data)
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
		reset_ray(&ray); //resets ray
		init_ray(&ray, data, rayCount); // initialize starting values for ray
		set_dist(&ray, data); // setting up step and side_dist for ray
		dda(&ray, map); //DDA
		set_ray_dist(&ray); // defining ray distance to wall
		set_draw_val(&ray, &height, &wallStart, &wallEnd); // defining height and draw values

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