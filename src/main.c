/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/22 19:57:35 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 2)
	{
		ft_bzero(&data, sizeof(t_data));
		data.file_path = ft_strdup(argv[1]);
		init_data(&data);
		// parser(&data);
		init_val(&data);
		print_str_node(data.file_data);
		print_map(&data);
		print_player_info(&data);
		get_textures(&data);
		render_world(&data);
	}
	else
		printf("%sToo many arguments\n%s./cub3d <path to amap file>[✓]\n%s",
			RED, GREEN_BG, RESET);
	return (0);
}
