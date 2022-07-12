/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda_prototype.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:55:53 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/12 19:06:22 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define mapwid 640
#define maphei 480
#define mapWidth 24
#define mapHeight 24

void	raycast_dda_prototype()
{
	int worldMap[mapWidth][mapHeight]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// char map[mapwid][maphei] =
	// {
	// 	"1111111111",
	// 	"1000000001",
	// 	"1000000001",
	// 	"1000000001",
	// 	"1000000001",
	// 	"1000000001",
	// 	"1000000001",
	// 	"1000000001",
	// 	"1000000001",
	// 	"1111111111"
	// };
	
	// (void) map;
	t_vect start_pos;
	start_pos.x = 22;
	start_pos.y = 12;

	t_vect dir;
	dir.x = -1;
	dir.y = 0;

	t_vect plane;
	plane.x = 0;
	plane.y = 0.66;

	int x = 0;
	while (x < mapwid)
	{
		double camera_x = 2 * x / (double) mapWidth- 1;

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
			delta_dist.x = fabs(1 / raydir.x);
		if (raydir.y == 0)
			delta_dist.y = INFINITY;
		else
			delta_dist.y = fabs(1/raydir.y);

		double perpWall_dist;

		t_vect step;
		int hit = 0;
		int side;

		if (raydir.x < 0)
		{
			step.x = -1;
			side_dist.x = (start_pos.x - curr_pos.x) + delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (curr_pos.x + 1.0 - start_pos.x) * delta_dist.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			side_dist.y = (start_pos.y- curr_pos.y) + delta_dist.y;
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
				curr_pos.y += curr_pos.y;
				side = 1;
			}
			if (worldMap[(int) curr_pos.x][(int) curr_pos.y] >= 1)
				hit = 1;
		}
		
		if (side == 0)
			perpWall_dist = (side_dist.x  - delta_dist.x);
		else
			perpWall_dist = (side_dist.y  - delta_dist.y);
		
		int height = (int) (maphei / perpWall_dist);

		int drawStart = -height / 2 + maphei / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = height / 2 + maphei / 2;
		if (drawEnd >= maphei)
			drawEnd = maphei - 1;

		printf("CAMERA_X: %f\n", camera_x);
		printf("CURR_POS[x][y]: %d %d\n", (int) curr_pos.x, (int) curr_pos.y);
		printf("RAYDIR[x][y]: %f %f\n", raydir.x, raydir.y);
		printf("DELTA_DIST[x][y]: %f %f\n", delta_dist.x, delta_dist.y);
		printf("SIDE_DIST[x][y]: %f %f\n", side_dist.x, side_dist.y);
		printf("STEP[x][y]: %d %d\n", (int) step.x, (int) step.y);
		printf("HIT? %d, SIDE: %d\n", hit, side);
		printf("WALL_DIST: %f, HEIGHT: %d, DRAW_START: %d, DRAW_END: %d\n", perpWall_dist, height, drawStart, drawEnd);
		printf("X: %d\n\n", x);
		
		x++;
	}
}
