/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/12 03:07:02 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int	main(int argc, char *argv[])
// {
// 	int	fd;

// 	(void) argv;
// 	if (argc == 2)
// 	{
// 		fd = file_parser(argv[1]);
// 		if (fd >= SUCC)
// 			printf("Correct!\n");
// 		else if (fd == FILE_NOT_FOUND)
// 			printf("File not found!\n");
// 		else if (fd == FILENAME_NOT_CORRECT)
// 			printf("Only file with a .cub extension allowed!\n");
// 		close(fd);
// 	}
// 	else
// 		printf("Wrong number of arguments\n./cub3d <path to a map file>\n");
// 	return (0);
// }

#define mapwid 10
#define maphei 10

int main()
{
	char map[mapwid][maphei] =
	{
		"1111111111",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1111111111"
	};
	
	t_vect start_pos;
	start_pos.x = 5;
	start_pos.y = 5;

	t_vect dir;
	dir.x = -1;
	dir.y = 0;

	t_vect plane;
	plane.x = 0;
	plane.y = 0.66;

	int x = 0;
	while (x <= mapwid)
	{
		double camera_x = 2 * x / (double) mapwid - 1;

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
			delta_dist.y = fabs(1 / raydir.x);
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
				side_dist.x += side_dist.x;
				curr_pos.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += side_dist.y;
				curr_pos.y += curr_pos.y;
				side = 1;
			}
			if (map[(int) curr_pos.y][(int) curr_pos.x] == '1')
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
		printf("WALL_DIST: %f, HEIGHT: %d, DRAW_START: %d, DRAW_END: %d\n\n", perpWall_dist, height, drawStart, drawEnd);

		x++;
	}
}

// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <memory.h>

// mlx_image_t	*g_img;

// void	hook(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
	
// 	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
// 		mlx_close_window(param);
// 	if (mlx_is_key_down(param, MLX_KEY_UP) || mlx_is_key_down(param, MLX_KEY_W))
// 		if (g_img->instances[0].y > 0)
// 			g_img->instances[0].y -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_DOWN) || mlx_is_key_down(param, MLX_KEY_S))
// 		if (g_img->instances[0].y < 590)
// 			g_img->instances[0].y += 5;
// 	if (mlx_is_key_down(param, MLX_KEY_LEFT) || mlx_is_key_down(param, MLX_KEY_A))
// 		if (g_img->instances[0].x > 0)
// 			g_img->instances[0].x -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_RIGHT) || mlx_is_key_down(param, MLX_KEY_D))
// 		if (g_img->instances[0].x < 950)
// 			g_img->instances[0].x += 5;
// }

// int	main(void)
// {
// 	mlx_t	*mlx;

// 	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
// 	if (!mlx)
// 		return (1);
// 	g_img = mlx_new_image(mlx, 128, 128);
// 	ft_memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
// 	mlx_image_to_window(mlx, g_img, 0, 0);
// 	mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (0);
// }
