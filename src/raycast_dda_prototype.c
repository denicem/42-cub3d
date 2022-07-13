/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda_prototype.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:55:53 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/14 01:49:28 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	raycast_dda_prototype(mlx_t *mlx, mlx_image_t *img)
{
	(void) mlx;

	int map[10][10] =
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

	int rayCount = 0;
	while (rayCount < WIDTH)
	{
		float camera_x = 2 * rayCount / (float) WIDTH - 1;

		t_vect raydir;
		raydir.x = dir.x + plane.x * camera_x;
		raydir.y = dir.y + plane.y * camera_x;
		
		t_vect curr_pos;
		curr_pos = start_pos;

		t_vect side_dist;
		t_vect delta_dist;

		if (raydir.x == 0)
			delta_dist.x = INFINITY;
		else
			delta_dist.x = fabs(1.0 / raydir.x);
		if (raydir.y == 0)
			delta_dist.y = INFINITY;
		else
			delta_dist.y = fabs(1.0/raydir.y);

		float perpWall_dist;

		t_vect step;
		int hit = 0;
		int side;

		if (raydir.x < 0)
		{
			step.x = -1;
			side_dist.x = (start_pos.x - curr_pos.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (curr_pos.x + 1.0 - start_pos.x) * delta_dist.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			side_dist.y = (start_pos.y- curr_pos.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (curr_pos.y + 1.0 - start_pos.y) * delta_dist.y;
		}

		//DDA
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				curr_pos.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				curr_pos.y += step.y;
				side = 1;
			}
			if (map[(int) curr_pos.y][(int) curr_pos.x] >= 1)
				hit = 1;
		}
		if (side == 0)
			perpWall_dist = (side_dist.x  - delta_dist.x);
		else
			perpWall_dist = (side_dist.y  - delta_dist.y);
		
		int height = (int) (0.5 * HEIGHT / perpWall_dist);

		int drawStart = -height / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = height / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		// printf("sidex: %f deltax: %f\nsidey: %f deltay: %f\n\n", side_dist.x, delta_dist.x, side_dist.y, delta_dist.y);
		// printf("CAMERA_X: %f\n", camera_x);
		// printf("CURR_POS[x][y]: %d %d\n", (int) curr_pos.x, (int) curr_pos.y);
		// printf("RAYDIR[x][y]: %f %f\n", raydir.x, raydir.y);
		// printf("DELTA_DIST[x][y]: %f %f\n", delta_dist.x, delta_dist.y);
		// printf("SIDE_DIST[x][y]: %f %f\n", side_dist.x, side_dist.y);
		// printf("STEP[x][y]: %d %d\n", (int) step.x, (int) step.y);
		// printf("HIT? %d, SIDE: %d\n", hit, side);
		// printf("WALL_DIST: %f, HEIGHT: %d, DRAW_START: %d, DRAW_END: %d\n", perpWall_dist, height, drawStart, drawEnd);
		// printf("X: %d\n\n", x);
		
		draw_vertical_line(rayCount, drawStart, drawEnd, img);
		rayCount++;
	}
}
