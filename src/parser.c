/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:50:59 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 14:09:41 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool check_map_identifier(t_parser_check *check)
{
	if (!check->n_identifier || !check->e_identifier || !check->s_identifier
		|| !check->w_identifier || !check->c_identifier
		|| !check->f_identifier)
		return (false);
	return (true);
}

void	texture_identifier(t_data *data, char *dir, char *path)
{
	int		i;
	char	*directions[4];

	// check if path exists
	if (open(path, O_RDONLY) == FILE_NOT_FOUND)
		exit(FAIL); //fail
	directions[0] = "EA";
	directions[1] = "WE";
	directions[2] = "NO";
	directions[3] = "SO";
	i = 0;
	while (i < 4 && directions[i])
	{
		if (!ft_strncmp(directions[i], dir, 2))
		{
			data->texture_paths[i] = ft_strdup(path);
			return ;
		}
		i++;
	}
	exit(FAIL);
}

void color_identifier(t_data *data, char c, char *c_code)
{
	char **rgb;

	// check syntax of color codes? (only digits and comma ',')
	rgb = ft_split(c_code, ',');
	// check if rgb is more than three elements and if number exceeds 255
	if (c == 'C')
	{
		data->c_colour.red = ft_atoi(rgb[0]);
		data->c_colour.green = ft_atoi(rgb[1]);
		data->c_colour.blue = ft_atoi(rgb[2]);
	}
	else if (c == 'F')
	{
		data->f_colour.red = ft_atoi(rgb[0]);
		data->f_colour.green = ft_atoi(rgb[1]);
		data->f_colour.blue = ft_atoi(rgb[2]);
	}
	else
		// ERROR invalid map identifier
		exit(FAIL);
	free(rgb);
}

void	check_curr_str(t_data *data, char *str)
{
	char **str_arr;

	str_arr = ft_split_ws(str); // TODO: implement split for just whitespaces
	if (ft_strlen_arr((const char **) str_arr) != 2)
		return ; // FAIL invalid map identifiers
	if (ft_strlen(str_arr[0]) == 2)
		texture_identifier(data, str_arr[0], str_arr[1]);
	else if (ft_strlen(str_arr[0]) == 1)
		color_identifier(data, *str_arr[0], str_arr[1]);
	else
		exit(FAIL);
	free(str_arr);
}

void init_parser_check(t_parser_check *check)
{
	check->n_identifier = false;
	check->s_identifier = false;
	check->e_identifier = false;
	check->w_identifier = false;
	check->c_identifier = false;
	check->f_identifier = false;
}

void	parser(t_data *data)
{
	t_parser_check	check;
	t_str_node		*curr_node;

	(void) data;
	init_parser_check(&check);
	curr_node = data->file_data;
	data->texture_paths = ft_calloc(4, sizeof(char *));
	// while (!check_map_identifier(&check))
	while (!curr_node->map)
	{
		if (curr_node->map && !check_map_identifier(&check))
			exit(FAIL); // FAIL!! no map before the map_identifiers
		check_curr_str(data, curr_node->str);
		curr_node = curr_node->next;
	}
}
