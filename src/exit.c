/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:05:35 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 18:07:44 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	exit_error(t_data *data, char *msg, int error_code)
{
	(void) data;
	printf("%sError:%s\n", RED, RESET);
	if (msg)
		printf("%s%s%s\n", RED, msg, RESET);
	// free data
	exit(error_code);
}