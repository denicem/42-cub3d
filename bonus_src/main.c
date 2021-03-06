/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 23:37:43 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
		parser(&data);
		init_val(&data);
		get_textures(&data);
		progress_bar();
		render_world(&data);
		free_data(&data);
	}
	else
		printf("%sToo many arguments\n%s./cub3d <path to a map file>[✓]\n%s",
			RED, GREEN_BG, RESET);
	return (0);
}
