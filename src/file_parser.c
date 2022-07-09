/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:38:38 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/09 23:13:21 by dmontema         ###   ########.fr       */
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
	if (!strcmp(file_ext, ".cub")) //TODO: write own version of strcmp and add it to Libft!
		res = SUCC;
	free(file_ext);
	return (res);
}

int	file_parser(char *filename)
{
	if (check_ext(filename) == FILENAME_NOT_CORRECT)
		return (FILENAME_NOT_CORRECT);
	return (open(filename, O_RDONLY));
}
