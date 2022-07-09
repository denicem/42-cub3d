/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:04:31 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/09 23:14:44 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/Libft/inc/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <fcntl.h>
# include <math.h>

# define SUCC 1
# define FAIL 0
# define FILE_NOT_FOUND -1
# define FILENAME_NOT_CORRECT -2

int	file_parser(char *filename);

#endif