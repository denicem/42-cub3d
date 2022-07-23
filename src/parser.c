/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:50:59 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 18:34:43 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	check_map_identifier(t_parser_check *check)
{
	if (!check->n_identifier || !check->e_identifier || !check->s_identifier
		|| !check->w_identifier || !check->c_identifier
		|| !check->f_identifier)
		return (false);
	return (true);
}

void	check_curr_str(t_data *data, char *str)
{
	char	**str_arr;

	str_arr = ft_split_ws(str);
	if (!str_arr)
		exit_error(data, "Malloc failed.", FAIL);
	if (ft_strlen_arr((const char **) str_arr) != 2)
		exit_error(data, "Map identifier invalid.", FAIL);
	if (ft_strlen(str_arr[0]) == 2)
		texture_identifier(data, str_arr[0], str_arr[1]);
	else if (ft_strlen(str_arr[0]) == 1)
		color_identifier(data, *str_arr[0], str_arr[1]);
	else
	{
		ft_free_str_arr(&str_arr);
		exit_error(data, "Map identifier invalid.", FAIL);
	}
	ft_free_str_arr(&str_arr);
}

void	init_parser_check(t_parser_check *check)
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
	t_str_node	*curr_node;

	init_parser_check(&data->check);
	curr_node = data->file_data;
	data->texture_paths = ft_calloc(4, sizeof(char *));
	while (!check_map_identifier(&data->check))
	{
		if (curr_node->map && !check_map_identifier(&data->check))
			exit_error(data, "Map cannot be first.", FAIL);
		check_curr_str(data, curr_node->str);
		curr_node = curr_node->next;
	}
}
