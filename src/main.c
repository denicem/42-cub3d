/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/09 23:14:15 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int	fd;

	(void) argv;
	if (argc == 2)
	{
		fd = file_parser(argv[1]);
		if (fd >= SUCC)
			printf("Correct!\n");
		else if (fd == FILE_NOT_FOUND)
			printf("File not found!\n");
		else if (fd == FILENAME_NOT_CORRECT)
			printf("Only file with a .cub extension allowed!\n");
		close(fd);
	}
	else
		printf("Wrong number of arguments\n./cub3d <path to a map file>\n");
	return (0);
}

// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <memory.h>
// #define WIDTH 1080
// #define HEIGHT 720

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
