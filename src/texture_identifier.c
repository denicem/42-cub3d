/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_identifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:00:12 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 18:33:01 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_texture_identifier(t_parser_check *check, char *dir)
{
	if (!ft_strcmp(dir, "EA"))
		check->e_identifier = true;
	if (!ft_strcmp(dir, "WE"))
		check->w_identifier = true;
	if (!ft_strcmp(dir, "NO"))
		check->n_identifier = true;
	if (!ft_strcmp(dir, "SO"))
		check->s_identifier = true;
}

static char	**get_directions(void)
{
	char	**dir;

	dir = ft_calloc_str_arr(5);
	if (!dir)
		return (NULL);
	dir[0] = ft_strdup("EA");
	dir[1] = ft_strdup("WE");
	dir[2] = ft_strdup("NO");
	dir[3] = ft_strdup("SO");
	return (dir);
}

void	texture_identifier(t_data *data, char *dir, char *path)
{
	int		i;
	char	**directions;

	if (open(path, O_RDONLY) == FILE_NOT_FOUND)
		exit_error(data, "Texture path could not be found.", FAIL);
	directions = get_directions();
	if (!directions)
		exit_error(data, "Malloc failed.", FAIL);
	i = 0;
	while (i < 4 && directions[i])
	{
		if (!ft_strcmp(directions[i], dir))
		{
			data->texture_paths[i] = ft_strdup(path);
			check_texture_identifier(&data->check, dir);
			ft_free_str_arr(&directions);
			return ;
		}
		i++;
	}
	ft_free_str_arr(&directions);
	exit_error(data, "Map identifier wrong.", FAIL);
}
