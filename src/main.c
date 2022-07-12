/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/12 23:45:35 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define mapwid 640
#define maphei 480

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

static void init_val()
{
	start_pos.x = 11;
	start_pos.y = 5;

	dir.x = 0;
	dir.y = 1;

	plane.x = 0;
	plane.y = 0.66;

}

int main()
{
	t_data data;

	data.mlx = mlx_init(mapwid, maphei, "raycast_dda_prototype", false);
	if (!data.mlx)
		return (1);
	data.img = mlx_new_image(data.mlx, mapwid, maphei);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	init_val();
	raycast_dda_prototype(data.mlx, data.img);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx);
	return (0);
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
