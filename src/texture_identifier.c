/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_identifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:00:12 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 20:12:00 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	check_texture_identifier(t_parser_check *check, char *dir)
{
	if (!ft_strcmp(dir, "EA") && !check->e_identifier)
	{
		check->e_identifier = true;
		return (true);
	}
	else if (!ft_strcmp(dir, "WE") && !check->w_identifier)
	{
		check->w_identifier = true;
		return (true);
	}
	else if (!ft_strcmp(dir, "NO") && !check->n_identifier)
	{
		check->n_identifier = true;
		return (true);
	}
	else if (!ft_strcmp(dir, "SO") && !check->s_identifier)
	{
		check->s_identifier = true;
		return (true);
	}
	return (false);
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
		exit_error(data, "Texture path could not be found.", FAILURE);
	directions = get_directions();
	if (!directions)
		exit_error(data, "Malloc failed.", FAILURE);
	i = 0;
	while (i < 4 && directions[i])
	{
		if (!ft_strcmp(directions[i], dir))
		{
			ft_free_str_arr(&directions);
			if (!check_texture_identifier(&data->check, dir))
				exit_error(data, "Double texture identifier.", FAILURE);
			data->texture_paths[i] = ft_strdup(path);
			return ;
		}
		i++;
	}
	ft_free_str_arr(&directions);
	exit_error(data, "Map identifier wrong.", FAILURE);
}
