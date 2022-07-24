/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:38:38 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 19:19:48 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <string.h>
#include <stdio.h>

static int	check_ext(char *filename)
{
	int		res;
	char	*file_ext;

	res = FILENAME_NOT_CORRECT;
	if (ft_strlen(filename) < 4)
		return (res);
	file_ext = ft_substr(filename, ft_strlen(filename) - 4, 4);
	if (!ft_strcmp(file_ext, ".cub"))
		res = SUCCESS;
	free(file_ext);
	return (res);
}

int	file_parser(char *filename)
{
	if (check_ext(filename) == FILENAME_NOT_CORRECT)
		return (FILENAME_NOT_CORRECT);
	return (open(filename, O_RDONLY));
}
